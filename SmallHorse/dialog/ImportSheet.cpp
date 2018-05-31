// ImportSheet.cpp : implementation file
//

#include "stdafx.h"
#include "..\SmallHorse.h"
#include "ImportSheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CImportSheet

IMPLEMENT_DYNAMIC(CImportSheet, CPropertySheet)

CImportSheet::CImportSheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
	m_psh.dwFlags|=PSH_WIZARDHASFINISH|PSH_PROPSHEETPAGE;
	AddPage(&m_FilePage);
	AddPage(&m_ListPage);
	SetWizardMode();
	m_bFromFile = TRUE;
}

CImportSheet::CImportSheet(LPCTSTR pszFullPath,CRecordset* pSet,int nImportType)
:CPropertySheet(_T("导入数据"), NULL, 0),m_FilePage(this),m_ListPage(this)
{
	m_psh.dwFlags|=PSH_WIZARDHASFINISH|PSH_PROPSHEETPAGE;
	AddPage(&m_FilePage);
	AddPage(&m_ListPage);
	SetWizardMode();
	m_bLoadOK = FALSE;
	m_FilePage.m_strFile = pszFullPath;
	if(nImportType == IMPORT_TYPE_RECORD)
	{
		m_pListSet = (CListSet*)pSet;
	}
	else
	{
		m_pSubCountSet = (CSubCountSet*)pSet;
	}
	m_nImportType = nImportType;
	m_bFromFile=TRUE;
}
CImportSheet::CImportSheet(CRecordset* pSet)
	:CPropertySheet(_T("粘贴记录"), NULL, 0),m_ListPage(this)
{
	m_psh.dwFlags|=PSH_WIZARDHASFINISH|PSH_PROPSHEETPAGE;
	AddPage(&m_ListPage);
	SetWizardMode();
	m_bLoadOK = FALSE;
	m_nImportType = IMPORT_TYPE_RECORD;
	m_pListSet = (CListSet*)pSet;

	m_bFromFile=FALSE;
}

CImportSheet::~CImportSheet()
{
}


BEGIN_MESSAGE_MAP(CImportSheet, CPropertySheet)
	//{{AFX_MSG_MAP(CImportSheet)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImportSheet message handlers

BOOL CImportSheet::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	if(wParam == 0x3024 && (GetActivePage() == &m_FilePage))
	{
		m_FilePage.UpdateData();
		if(!SetNewFile(m_FilePage.m_strFile))
		{
			AfxMessageBox(_T("必须是合法的CSV文件才可以!"));
			return TRUE;
		}
	}
	if(wParam == 0x3025)//完成
	{
		if(!m_ListPage.SaveDataToDataLib())
		{
			return TRUE;
		}
	}
	return CPropertySheet::OnCommand(wParam, lParam);
}

BOOL CImportSheet::SetNewFile(const CString &strfile)
{
	if(strfile!=m_strFile)
	{
		if(m_loader.Load(strfile))
		{
			m_ListPage.ReFill();
			m_strFile = strfile;
			m_bLoadOK = TRUE;
		}
		else 
		{
			m_bLoadOK = FALSE;
		}
	}
	return m_bLoadOK;
}


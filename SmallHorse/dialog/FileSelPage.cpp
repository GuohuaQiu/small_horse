// FileSelPage.cpp : implementation file
//

#include "stdafx.h"
#include "..\SmallHorse.h"
#include "FileSelPage.h"
#include "importsheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileSelPage property page

IMPLEMENT_DYNCREATE(CFileSelPage, CPropertyPage)

CFileSelPage::CFileSelPage() : CPropertyPage(CFileSelPage::IDD)
{
	//{{AFX_DATA_INIT(CFileSelPage)
	m_strFile = _T("");
	//}}AFX_DATA_INIT
}

CFileSelPage::CFileSelPage(CImportSheet* pParent) : CPropertyPage(CFileSelPage::IDD)
{
    m_pParent = pParent;
}

CFileSelPage::~CFileSelPage()
{
}

void CFileSelPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFileSelPage)
	DDX_Text(pDX, IDC_EDIT_FILE, m_strFile);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFileSelPage, CPropertyPage)
	//{{AFX_MSG_MAP(CFileSelPage)
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDC_SELECTFILE, OnSelectfile)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFileSelPage message handlers

BOOL CFileSelPage::OnSetActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	m_pParent->SetWizardButtons(PSWIZB_DISABLEDFINISH    | PSWIZB_NEXT);
	
	return CPropertyPage::OnSetActive();
}

BOOL CFileSelPage::OnKillActive() 
{
	TRACE("CFileSelPage::OnKillActive()\n");
	return CPropertyPage::OnKillActive();
}

BOOL CFileSelPage::PreTranslateMessage(MSG* pMsg) 
{
	
	return CPropertyPage::PreTranslateMessage(pMsg);
}


void CFileSelPage::OnDropFiles(HDROP hDropInfo)
{
    // 被拖拽的文件的文件名
    TCHAR szFileName[MAX_PATH + 1];
    // 得到被拖拽的文件名
    DragQueryFile(hDropInfo, 0, szFileName, MAX_PATH);
    // 把文件名显示出来
	m_pParent->SetWindowText(szFileName);
	m_strFile = szFileName;
	UpdateData(FALSE);
}

void CFileSelPage::OnSelectfile() 
{
    static TCHAR BASED_CODE szFilter[] = _T("CSV Files (*.csv)|*.csv|All Files (*.*)|*.*||");
	CFileDialog dlg(TRUE,NULL,NULL,0,szFilter,this);
	if(dlg.DoModal()==IDOK)
	{
		m_strFile = dlg.GetPathName();
		UpdateData(FALSE);
	}
	
}

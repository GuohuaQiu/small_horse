// QuerySheet.cpp : implementation file
//

#include "stdafx.h"
#include "..\SmallHorse.h"
#include "QuerySheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CQuerySheet

IMPLEMENT_DYNAMIC(CQuerySheet, CPropertySheet)

CQuerySheet::CQuerySheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
	m_psh.dwFlags|=PSH_WIZARDHASFINISH|PSH_PROPSHEETPAGE;
	AddPage(&m_pgName);
	AddPage(&m_pgDate);
	AddPage(&m_pgType);
    AddPage(&m_pgComment);
	SetWizardMode();

	
}

CQuerySheet::CQuerySheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	AddPage(&m_pgName);
	AddPage(&m_pgDate);
	AddPage(&m_pgType);
    AddPage(&m_pgComment);
    SetWizardMode();
}

CQuerySheet::~CQuerySheet()
{
}


BEGIN_MESSAGE_MAP(CQuerySheet, CPropertySheet)
	//{{AFX_MSG_MAP(CQuerySheet)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CQuerySheet message handlers

void CQuerySheet::AddStringToList(const CString &str, CListBox &list)
{
	int n=list.GetCount();
	if(LB_ERR!=list.FindStringExact(0,str) )
		return;
	list.AddString(str);
}

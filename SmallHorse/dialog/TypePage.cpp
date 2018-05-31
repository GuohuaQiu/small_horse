// TypePage.cpp : implementation file
//

#include "stdafx.h"
#include "..\SmallHorse.h"
#include "TypePage.h"
#include "querysheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTypePage property page

IMPLEMENT_DYNCREATE(CTypePage, CPropertyPage)

CTypePage::CTypePage() : CPropertyPage(CTypePage::IDD)
{
	//{{AFX_DATA_INIT(CTypePage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CTypePage::~CTypePage()
{
	m_psp.dwFlags |= PSP_HASHELP;
	
}

void CTypePage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTypePage)
	DDX_Control(pDX, IDC_LIST_TARGET_TYPE, m_listTarget);
	DDX_Control(pDX, IDC_LIST_SRC_TYPE, m_listSrc);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTypePage, CPropertyPage)
	//{{AFX_MSG_MAP(CTypePage)
	ON_LBN_DBLCLK(IDC_LIST_SRC_TYPE, OnDblclkListSrcType)
	ON_LBN_DBLCLK(IDC_LIST_TARGET_TYPE, OnDblclkListTargetType)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTypePage message handlers

BOOL CTypePage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	for(int i=0;i<256;i++)
	{
		if(_tcslen(theApp.m_cType[i])>0)
		{
			m_listSrc.AddString(theApp.m_cType[i]);
		}
	}
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CTypePage::OnDblclkListSrcType() 
{
	int n=m_listSrc.GetCurSel();
	CString strName;
	m_listSrc.GetText(n,strName);
	CQuerySheet::AddStringToList(strName,m_listTarget);
	
}

void CTypePage::OnDblclkListTargetType() 
{
	int n=m_listTarget.GetCurSel();
	m_listTarget.DeleteString(n);
}

BOOL CTypePage::OnApply() 
{
	AfxMessageBox("ok");
	return CPropertyPage::OnApply();
}

LRESULT CTypePage::OnWizardNext() 
{
	CQuerySheet* psheet = (CQuerySheet*) GetParent();   
	int nCount=m_listTarget.GetCount();
	for(int i=0;i<nCount;i++)
	{
		CString strItem;
		m_listTarget.GetText(i,strItem);
		psheet->m_pTypeList->AddTail(strItem);
	}
	return CPropertyPage::OnWizardNext();
}

BOOL CTypePage::OnSetActive() 
{
	CQuerySheet* psheet = (CQuerySheet*) GetParent();   
    psheet->SetWizardButtons(PSWIZB_BACK|PSWIZB_NEXT);
    return CPropertyPage::OnSetActive();
}

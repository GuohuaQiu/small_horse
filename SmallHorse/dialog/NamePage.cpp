// NamePage.cpp : implementation file
//

#include "stdafx.h"
#include "..\SmallHorse.h"
#include "NamePage.h"
#include "querysheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNamePage property page

IMPLEMENT_DYNCREATE(CNamePage, CPropertyPage)

CNamePage::CNamePage() : CPropertyPage(CNamePage::IDD)
{
	//{{AFX_DATA_INIT(CNamePage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CNamePage::~CNamePage()
{
}

void CNamePage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNamePage)
	DDX_Control(pDX, IDC_LIST_TARGET_NAME, m_listTarget);
	DDX_Control(pDX, IDC_LIST_SRC_NAME, m_listSrc);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNamePage, CPropertyPage)
	//{{AFX_MSG_MAP(CNamePage)
	ON_LBN_DBLCLK(IDC_LIST_SRC_NAME, OnDblclkListSrcName)
	ON_LBN_DBLCLK(IDC_LIST_TARGET_NAME, OnDblclkListTargetName)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNamePage message handlers

BOOL CNamePage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	m_pIDSet->m_strFilter="";
	m_pIDSet->Requery();
    if(!m_pIDSet->IsBOF())
    {
        m_pIDSet->MoveFirst();
    }
    m_pIDSet->MoveFirst();
	while(!m_pIDSet->IsEOF())
	{
		CQuerySheet::AddStringToList(m_pIDSet->m_name,m_listSrc);
		m_pIDSet->MoveNext();
	}
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CNamePage::OnDblclkListSrcName() 
{
	int n=m_listSrc.GetCurSel();
	CString strName;
	m_listSrc.GetText(n,strName);
	CQuerySheet::AddStringToList(strName,m_listTarget);
	// TODO: Add your control notification handler code here
	
}

void CNamePage::OnDblclkListTargetName() 
{
	int n=m_listTarget.GetCurSel();
	m_listTarget.DeleteString(n);
}

BOOL CNamePage::OnWizardFinish() 
{
	
	return CPropertyPage::OnWizardFinish();
}

LRESULT CNamePage::OnWizardNext() 
{
	CQuerySheet* psheet=(CQuerySheet*)GetParent();
    psheet->m_pNameList->RemoveAll();
	int nCount=m_listTarget.GetCount();
	for(int i=0;i<nCount;i++)
	{
		CString strItem;
		m_listTarget.GetText(i,strItem);
		psheet->m_pNameList->AddTail(strItem);
	}
	
	return CPropertyPage::OnWizardNext();
}

BOOL CNamePage::OnSetActive() 
{
    CQuerySheet* psheet = (CQuerySheet*) GetParent();   
    psheet->SetWizardButtons(PSWIZB_NEXT);
	
	return CPropertyPage::OnSetActive();
}

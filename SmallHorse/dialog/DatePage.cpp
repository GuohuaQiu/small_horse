// DatePage.cpp : implementation file
//

#include "stdafx.h"
#include "..\SmallHorse.h"
#include "DatePage.h"
#include "querysheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDatePage property page

IMPLEMENT_DYNCREATE(CDatePage, CPropertyPage)

CDatePage::CDatePage() : CPropertyPage(CDatePage::IDD)
{
    m_bAllTime = TRUE;
    //{{AFX_DATA_INIT(CDatePage)
	m_BeginTime = COleDateTime::GetCurrentTime();
	m_EndTime = COleDateTime::GetCurrentTime();
	//}}AFX_DATA_INIT
}

CDatePage::~CDatePage()
{
}

void CDatePage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDatePage)
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_DateCtrlBegin);
    DDX_Control(pDX, IDC_DATETIMEPICKER2, m_DateCtrlEnd);
	DDX_Check(pDX, IDC_CHECK_ALLDATE, m_bAllTime);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_BeginTime);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER2, m_EndTime);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDatePage, CPropertyPage)
	//{{AFX_MSG_MAP(CDatePage)
	ON_BN_CLICKED(IDC_CHECK_ALLDATE, OnCheckAlldate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDatePage message handlers

BOOL CDatePage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
    m_DateCtrlBegin.EnableWindow(!m_bAllTime);
    m_DateCtrlEnd.EnableWindow(!m_bAllTime);
    
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}



void CDatePage::OnCheckAlldate() 
{
    UpdateData();
    m_DateCtrlBegin.EnableWindow(!m_bAllTime);
    m_DateCtrlEnd.EnableWindow(!m_bAllTime);
}



BOOL CDatePage::OnSetActive() 
{
    CQuerySheet* psheet = (CQuerySheet*) GetParent();   
    psheet->SetWizardButtons(PSWIZB_BACK|PSWIZB_NEXT);
	
	return CPropertyPage::OnSetActive();
}

LRESULT CDatePage::OnWizardNext() 
{
    UpdateData();
    
    CQuerySheet* psheet=(CQuerySheet*)GetParent();
    psheet->m_bUseTime=!m_bAllTime;
    psheet->m_beginTime=m_BeginTime;
    psheet->m_endTime=m_EndTime;
    
	return CPropertyPage::OnWizardNext();
}

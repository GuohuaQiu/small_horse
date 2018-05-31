// CloseSubCountDlg.cpp : implementation file
//

#include "stdafx.h"
#include "..\SmallHorse.h"
#include "CloseSubCountDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCloseSubCountDlg dialog


CCloseSubCountDlg::CCloseSubCountDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCloseSubCountDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCloseSubCountDlg)
	m_closeDate = COleDateTime::GetCurrentTime();
	m_bSavetoDefault = FALSE;
	//}}AFX_DATA_INIT
}


void CCloseSubCountDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCloseSubCountDlg)
    DDX_Control(pDX, IDC_DATETIMEPICKER, m_wndDateTimePicker);
	DDX_Check(pDX, IDC_CHECK_SAVETO_DEFAULT, m_bSavetoDefault);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCloseSubCountDlg, CDialog)
	//{{AFX_MSG_MAP(CCloseSubCountDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCloseSubCountDlg message handlers

void CCloseSubCountDlg::OnOK() 
{
    m_closeDate = m_wndDateTimePicker.GetDate();
    UpdateData();


    EndDialog(IDOK);
}

BOOL CCloseSubCountDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	const UINT stateMask = 
		CBCGPDateTimeCtrl::DTM_SPIN |
		CBCGPDateTimeCtrl::DTM_DROPCALENDAR | 
		CBCGPDateTimeCtrl::DTM_DATE |
		CBCGPDateTimeCtrl::DTM_TIME24H |
		CBCGPDateTimeCtrl::DTM_CHECKBOX |
		CBCGPDateTimeCtrl::DTM_TIME | 
		CBCGPDateTimeCtrl::DTM_TIME24HBYLOCALE;
    m_wndDateTimePicker.SetState (CBCGPDateTimeCtrl::DTM_SPIN |CBCGPDateTimeCtrl::DTM_DROPCALENDAR |CBCGPDateTimeCtrl::DTM_DATE, stateMask);
	m_wndDateTimePicker.SizeToContent();
    m_wndDateTimePicker.SetDate(COleDateTime(2010,12,28,0,0,0));
	UpdateData(FALSE);
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

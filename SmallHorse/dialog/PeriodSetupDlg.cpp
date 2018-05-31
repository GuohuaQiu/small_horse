// PeriodSetupDlg.cpp : implementation file
//

#include "stdafx.h"
#include "..\SmallHorse.h"
#include "PeriodSetupDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPeriodSetupDlg dialog


CPeriodSetupDlg::CPeriodSetupDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPeriodSetupDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPeriodSetupDlg)
	m_timeBegin = COleDateTime::GetCurrentTime();
	m_timeEnd = COleDateTime::GetCurrentTime();
	m_timePay = COleDateTime::GetCurrentTime();
	//}}AFX_DATA_INIT
}


void CPeriodSetupDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPeriodSetupDlg)
	DDX_DateTimeCtrl(pDX, IDC_DATETIME_BEGIN, m_timeBegin);
	DDX_DateTimeCtrl(pDX, IDC_DATETIME_END, m_timeEnd);
	DDX_DateTimeCtrl(pDX, IDC_DATETIME_PAY, m_timePay);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPeriodSetupDlg, CDialog)
	//{{AFX_MSG_MAP(CPeriodSetupDlg)
	ON_BN_CLICKED(IDC_BUTTON_NEXT_MONTH, OnNextMonth)
	ON_BN_CLICKED(IDC_BUTTON_PREV_MONTH, OnPrevMonth)
	// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPeriodSetupDlg message handlers
void MonthAdd(COleDateTime& time)
{
	int y,m,d;
	y = time.GetYear();
	m = time.GetMonth();
	d = time.GetDay();
	
	if(m == 12)
	{
		y++;
		m=1;
	}
	else
	{
		m++;
	}
	time.SetDate(y,m,d);
}
void MonthDec(COleDateTime& time)
{
	int y,m,d;
	y = time.GetYear();
	m = time.GetMonth();
	d = time.GetDay();
	
	if(m == 1)
	{
		y--;
		m=12;
	}
	else
	{
		m--;
	}
	time.SetDate(y,m,d);
}

void CPeriodSetupDlg::OnNextMonth() 
{
	MonthAdd(m_timeBegin);
	MonthAdd(m_timeEnd);
	MonthAdd(m_timePay);
	UpdateData(FALSE);
}

void CPeriodSetupDlg::OnPrevMonth() 
{
	MonthDec(m_timeBegin);
	MonthDec(m_timeEnd);
	MonthDec(m_timePay);
	UpdateData(FALSE);
}

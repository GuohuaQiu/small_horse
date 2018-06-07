// CreditPayDlg.cpp : implementation file
//

#include "stdafx.h"
#include "..\SmallHorse.h"
#include "CreditPayDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCreditPayDlg dialog


CCreditPayDlg::CCreditPayDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCreditPayDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCreditPayDlg)
	m_strComment = _T("");
	m_strID = _T("");
	m_datePay = 0;
	m_dateStatement = 0;
	m_EffectYearMonth = COleDateTime::GetCurrentTime();
	//}}AFX_DATA_INIT
}


void CCreditPayDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCreditPayDlg)
	DDX_Text(pDX, IDC_COMMENT, m_strComment);
	DDX_CBString(pDX, IDC_NEWCARD, m_strID);
	DDX_Text(pDX, IDC_EDIT_PAY_DATE, m_datePay);
	DDX_Text(pDX, IDC_EDIT_STATEMENT_DATE, m_dateStatement);
	DDX_MonthCalCtrl(pDX, IDC_MONTHCALENDAR, m_EffectYearMonth);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCreditPayDlg, CDialog)
	//{{AFX_MSG_MAP(CCreditPayDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCreditPayDlg message handlers

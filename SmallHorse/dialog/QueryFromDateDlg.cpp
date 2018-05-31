// QueryFromDateDlg.cpp : implementation file
//

#include "stdafx.h"
#include "..\SmallHorse.h"
#include "QueryFromDateDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CQueryFromDateDlg dialog


CQueryFromDateDlg::CQueryFromDateDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CQueryFromDateDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CQueryFromDateDlg)
	m_dateMid = COleDateTime::GetCurrentTime();
	m_strInfo = _T("");
	m_nBound = 1;
	//}}AFX_DATA_INIT
}


void CQueryFromDateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CQueryFromDateDlg)
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER, m_dateMid);
	DDX_Text(pDX, IDC_EDIT_INFO, m_strInfo);
	DDX_Text(pDX, IDC_EDIT_DATE_BOUND, m_nBound);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CQueryFromDateDlg, CDialog)
	//{{AFX_MSG_MAP(CQueryFromDateDlg)
	ON_EN_CHANGE(IDC_EDIT_DATE_BOUND, OnChangeEditDateBound)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER, OnDatetimechangeDatetimepicker)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CQueryFromDateDlg message handlers

void CQueryFromDateDlg::OnChangeEditDateBound() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData();
    COleDateTimeSpan span;
    span.SetDateTimeSpan(m_nBound,0,0,0);
    COleDateTime timea = m_dateMid + span;
    COleDateTime timeb = m_dateMid - span;
// OperDate BETWEEN #2009-12-14# and #2009-12-31#   
    m_strInfo=timeb.Format("OperDate BETWEEN #%Y-%m-%d# and ");
    m_strInfo+=timea.Format("#%Y-%m-%d#");
    UpdateData(FALSE);
}

void CQueryFromDateDlg::OnDatetimechangeDatetimepicker(NMHDR* pNMHDR, LRESULT* pResult) 
{
	UpdateData();
    COleDateTimeSpan span;
    span.SetDateTimeSpan(m_nBound,0,0,0);
    COleDateTime timea = m_dateMid + span;
    COleDateTime timeb = m_dateMid - span;
// OperDate BETWEEN #2009-12-14# and #2009-12-31#   
    m_strInfo=timeb.Format("OperDate BETWEEN #%Y-%m-%d# and ");
    m_strInfo+=timea.Format("#%Y-%m-%d#");
    UpdateData(FALSE);
	
	*pResult = 0;
}

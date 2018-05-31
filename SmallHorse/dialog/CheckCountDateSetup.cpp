// CheckCountDateSetup.cpp : implementation file
//

#include "stdafx.h"
#include "..\SmallHorse.h"
#include "CheckCountDateSetup.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCheckCountDateSetup dialog


CCheckCountDateSetup::CCheckCountDateSetup(CWnd* pParent /*=NULL*/)
	: CDialog(CCheckCountDateSetup::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCheckCountDateSetup)
	m_dateEnd = -1;
	m_datePay = -1;
	m_timeBegin = COleDateTime::GetCurrentTime();
	m_timeEnd = COleDateTime::GetCurrentTime();
	//}}AFX_DATA_INIT
}


void CCheckCountDateSetup::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCheckCountDateSetup)
	DDX_CBIndex(pDX, IDC_COMBO_DATE_END, m_dateEnd);
	DDX_CBIndex(pDX, IDC_COMBO_DATE_PAY, m_datePay);
	DDX_DateTimeCtrl(pDX, IDC_DATETIME_BEGIN, m_timeBegin);
	DDX_DateTimeCtrl(pDX, IDC_DATETIME_END, m_timeEnd);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCheckCountDateSetup, CDialog)
	//{{AFX_MSG_MAP(CCheckCountDateSetup)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCheckCountDateSetup message handlers

void CCheckCountDateSetup::OnOK() 
{
	CDialog::OnOK();
	m_dateEnd += 1;
	m_datePay += 1;
}

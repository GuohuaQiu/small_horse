// CopyRecordsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "..\SmallHorse.h"
#include "CopyRecordsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCopyRecordsDlg dialog


CCopyRecordsDlg::CCopyRecordsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCopyRecordsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCopyRecordsDlg)
	m_bTransfer = TRUE;
	m_mainCount = _T("");
	m_SubCount = _T("");
	//}}AFX_DATA_INIT
}


void CCopyRecordsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCopyRecordsDlg)
	DDX_Check(pDX, IDC_CHECK_TRANSFER, m_bTransfer);
	DDX_Text(pDX, IDC_EDIT_MAINCOUNT, m_mainCount);
	DDX_Text(pDX, IDC_EDIT_SUBCOUNT, m_SubCount);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCopyRecordsDlg, CDialog)
	//{{AFX_MSG_MAP(CCopyRecordsDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCopyRecordsDlg message handlers

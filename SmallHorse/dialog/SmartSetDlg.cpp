// SmartSetDlg.cpp : implementation file
//

#include "stdafx.h"
#include "..\SmallHorse.h"
#include "SmartSetDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSmartSetDlg dialog


CSmartSetDlg::CSmartSetDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSmartSetDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSmartSetDlg)
	m_strNoString = _T("");
	m_strYesString = _T("");
	m_nTypeIndex = -1;
	m_strSite = _T("");
	m_bActiveSite = FALSE;
	m_bActiveType = TRUE;
	//}}AFX_DATA_INIT
}


void CSmartSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSmartSetDlg)
	DDX_Control(pDX, IDC_COMBO_TYPE, m_cmbType);
	DDX_Text(pDX, IDC_EDIT_HAVE_NOT, m_strNoString);
	DDX_Text(pDX, IDC_EDIT_MUST_HAVE, m_strYesString);
	DDX_CBIndex(pDX, IDC_COMBO_TYPE, m_nTypeIndex);
	DDX_Text(pDX, IDC_EDIT_SITE, m_strSite);
	DDX_Check(pDX, IDC_CHECK_SITE, m_bActiveSite);
	DDX_Check(pDX, IDC_CHECK_TYPE, m_bActiveType);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSmartSetDlg, CDialog)
	//{{AFX_MSG_MAP(CSmartSetDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSmartSetDlg message handlers

void CSmartSetDlg::OnOK() 
{
	UpdateData();
	
	EndDialog(IDOK);
}

BOOL CSmartSetDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	for(int i=0;i<256;i++)
	{
		if(_tcslen(theApp.m_cType[i])>0)
		{
			m_cmbType.InsertString(i,theApp.m_cType[i]);
		}
		else
		{
			break;
		}
	}
	m_cmbType.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

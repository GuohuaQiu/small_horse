// Pwddlg.cpp : implementation file
//

#include "stdafx.h"
#include "..\SmallHorse.h"
#include "Pwddlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPwddlg dialog


CPwddlg::CPwddlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPwddlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPwddlg)
	m_pwd = _T("");
	m_user = _T("");
	//}}AFX_DATA_INIT
}


void CPwddlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPwddlg)
	DDX_Text(pDX, IDC_EDIT_PWD, m_pwd);
	DDX_Text(pDX, IDC_EDIT_USER, m_user);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPwddlg, CDialog)
	//{{AFX_MSG_MAP(CPwddlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPwddlg message handlers

BOOL CPwddlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

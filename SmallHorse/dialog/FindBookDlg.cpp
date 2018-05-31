// FindBookDlg.cpp : implementation file
//

#include "stdafx.h"
#include "..\SmallHorse.h"
#include "FindBookDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFindBookDlg dialog


CFindBookDlg::CFindBookDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFindBookDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFindBookDlg)
	m_strFind = _T("");
	//}}AFX_DATA_INIT
}


void CFindBookDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFindBookDlg)
	DDX_Text(pDX, IDC_EDIT_FIND_STRING, m_strFind);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFindBookDlg, CDialog)
	//{{AFX_MSG_MAP(CFindBookDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFindBookDlg message handlers

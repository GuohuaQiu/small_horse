// QueryFromCommentDlg.cpp : implementation file
//

#include "stdafx.h"
#include "..\SmallHorse.h"
#include "QueryFromCommentDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CQueryFromCommentDlg dialog


CQueryFromCommentDlg::CQueryFromCommentDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CQueryFromCommentDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CQueryFromCommentDlg)
	m_strComment = _T("");
	//}}AFX_DATA_INIT
}


void CQueryFromCommentDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CQueryFromCommentDlg)
	DDX_Text(pDX, IDC_EDIT_COMMENT, m_strComment);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CQueryFromCommentDlg, CDialog)
	//{{AFX_MSG_MAP(CQueryFromCommentDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CQueryFromCommentDlg message handlers

void CQueryFromCommentDlg::OnOK() 
{
    UpdateData();
	m_strInfo="Comment LIKE '%X%'";
    m_strInfo.Replace("X",m_strComment);
	
	CDialog::OnOK();
}

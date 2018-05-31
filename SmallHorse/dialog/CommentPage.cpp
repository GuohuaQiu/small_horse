// CommentPage.cpp : implementation file
//

#include "stdafx.h"
#include "..\SmallHorse.h"
#include "CommentPage.h"
#include "QuerySheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCommentPage property page

IMPLEMENT_DYNCREATE(CCommentPage, CPropertyPage)

CCommentPage::CCommentPage() : CPropertyPage(CCommentPage::IDD)
{
	//{{AFX_DATA_INIT(CCommentPage)
	m_strComment = _T("");
	//}}AFX_DATA_INIT
}

CCommentPage::~CCommentPage()
{
}

void CCommentPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCommentPage)
	DDX_Text(pDX, IDC_COMMENT, m_strComment);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCommentPage, CPropertyPage)
	//{{AFX_MSG_MAP(CCommentPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCommentPage message handlers

BOOL CCommentPage::OnWizardFinish() 
{
    CQuerySheet* psheet=(CQuerySheet*)GetParent();
    UpdateData();
    psheet->m_strCommentLike = m_strComment;
    return CPropertyPage::OnWizardFinish();
    
}

LRESULT CCommentPage::OnWizardNext() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CPropertyPage::OnWizardNext();
}

BOOL CCommentPage::OnSetActive() 
{
    CQuerySheet* psheet = (CQuerySheet*) GetParent();   
    psheet->SetWizardButtons(PSWIZB_BACK|PSWIZB_FINISH);
    
	return CPropertyPage::OnSetActive();
}

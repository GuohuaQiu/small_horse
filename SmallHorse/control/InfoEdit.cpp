// InfoEdit.cpp : implementation file
//

#include "stdafx.h"
#include "..\SmallHorse.h"
#include "InfoEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInfoEdit

CInfoEdit::CInfoEdit()
{
  m_bWaiting = TRUE;
}

CInfoEdit::~CInfoEdit()
{
}


BEGIN_MESSAGE_MAP(CInfoEdit, CEdit)
	//{{AFX_MSG_MAP(CInfoEdit)
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInfoEdit message handlers

void CInfoEdit::OnSetFocus(CWnd* pOldWnd) 
{
	CEdit::OnSetFocus(pOldWnd);
  if(m_bWaiting)
  {
    SetWindowText(_T(""));
    m_bWaiting = FALSE;
  }
  
	
	TRACE("CInfoEdit::OnSetFocus(CWnd* 0x%x) \n",pOldWnd);
}

void CInfoEdit::OnKillFocus(CWnd* pNewWnd) 
{
	CEdit::OnKillFocus(pNewWnd);
  CString strText;
  GetWindowText(strText);
  if(strText.GetLength()==0)
  {
    m_bWaiting = TRUE;
    SetWindowText(_T("≤È—Ø’À∫≈..."));
  }
	TRACE("CInfoEdit::OnKillFocus(CWnd* 0x%x) \n",pNewWnd);
	
	// TODO: Add your message handler code here
	
}

int CInfoEdit::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CEdit::OnCreate(lpCreateStruct) == -1)
		return -1;
  SetWindowText(_T("≤È—Ø’À∫≈..."));
	
	
	return 0;
}

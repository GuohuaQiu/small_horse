// SelEdit.cpp : implementation file
//

#include "stdafx.h"
//#include "..\SmallHorse.h"
#include "SelEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSelEdit

CSelEdit::CSelEdit()
{
}

CSelEdit::~CSelEdit()
{
}


BEGIN_MESSAGE_MAP(CSelEdit, CEdit)
	//{{AFX_MSG_MAP(CSelEdit)
	ON_WM_LBUTTONDOWN()
	ON_CONTROL_REFLECT(EN_SETFOCUS, OnSetfocus)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSelEdit message handlers

void CSelEdit::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CEdit::OnLButtonDown(nFlags, point);
	if(m_bsel)
	{
		m_bsel=FALSE;
		SetSel(0,-1);
	}
}

void CSelEdit::OnSetfocus() 
{
	m_bsel=TRUE;// TODO: Add your control notification handler code here
}

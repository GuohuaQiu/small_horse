// CurveBar.cpp : implementation of the CCurveBar class
//

#include "stdafx.h"
#include "..\SmallHorse.h"
#include "CurveBar.h"
#include "CurveView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const int nBorderSize = 1;

/////////////////////////////////////////////////////////////////////////////
// CCurveBar

BEGIN_MESSAGE_MAP(CCurveBar, CBCGPDockingControlBar)
	//{{AFX_MSG_MAP(CCurveBar)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCurveBar construction/destruction

CCurveBar::CCurveBar()
{
    m_pContext = NULL;

}

CCurveBar::~CCurveBar()
{
}

/////////////////////////////////////////////////////////////////////////////
// CCurveBar message handlers

class CA : public CCurveView
{
	friend class CCurveBar;
};

int CCurveBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CBCGPDockingControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;

    CRuntimeClass* pFactory = RUNTIME_CLASS(CCurveView);
    m_pFormView = (CCurveView *)(pFactory->CreateObject());
	
	if (m_pFormView != NULL)
	{
		m_pFormView->CreateView(this, m_pContext);
		((CA*)m_pFormView)->OnInitialUpdate();
	}

	return 0;
}

void CCurveBar::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	CRect rect;
	GetClientRect (rect);

	dc.FillSolidRect (rect, ::GetSysColor (COLOR_3DFACE));
}

void CCurveBar::OnSize(UINT nType, int cx, int cy) 
{
	CBCGPDockingControlBar::OnSize(nType, cx, cy);
	
	m_pFormView->MoveWindow(CRect(0,0,cx,cy));
}

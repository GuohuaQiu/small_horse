// SmallHorseView.cpp : implementation of the CSmallHorseView class
//

#include "stdafx.h"
#include "SmallHorse.h"

#include "SmallHorseDoc.h"
#include "SmallHorseView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSmallHorseView

IMPLEMENT_DYNCREATE(CSmallHorseView, CView)

BEGIN_MESSAGE_MAP(CSmallHorseView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, OnFilePrintPreview)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
END_MESSAGE_MAP()

// CSmallHorseView construction/destruction

CSmallHorseView::CSmallHorseView()
{
	// TODO: add construction code here

}

CSmallHorseView::~CSmallHorseView()
{
}

BOOL CSmallHorseView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CSmallHorseView drawing

void CSmallHorseView::OnDraw(CDC* /*pDC*/)
{
	CSmallHorseDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}


// CSmallHorseView printing

void CSmallHorseView::OnFilePrintPreview()
{
	BCGPPrintPreview (this);
}

BOOL CSmallHorseView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CSmallHorseView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CSmallHorseView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CSmallHorseView diagnostics

#ifdef _DEBUG
void CSmallHorseView::AssertValid() const
{
	CView::AssertValid();
}

void CSmallHorseView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSmallHorseDoc* CSmallHorseView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSmallHorseDoc)));
	return (CSmallHorseDoc*)m_pDocument;
}
#endif //_DEBUG


// CSmallHorseView message handlers

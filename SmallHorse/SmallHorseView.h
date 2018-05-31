// SmallHorseView.h : interface of the CSmallHorseView class
//


#pragma once


class CSmallHorseView : public CView
{
protected: // create from serialization only
	CSmallHorseView();
	DECLARE_DYNCREATE(CSmallHorseView)

// Attributes
public:
	CSmallHorseDoc* GetDocument() const;

// Operations
public:

// Overrides
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CSmallHorseView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in SmallHorseView.cpp
inline CSmallHorseDoc* CSmallHorseView::GetDocument() const
   { return reinterpret_cast<CSmallHorseDoc*>(m_pDocument); }
#endif


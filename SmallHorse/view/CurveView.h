#if !defined(AFX_CURVEVIEW_H__4556CC6E_7EBE_11D5_96DC_837659F4FF05__INCLUDED_)
#define AFX_CURVEVIEW_H__4556CC6E_7EBE_11D5_96DC_837659F4FF05__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CurveView.h : header file
//
#include "MyToolTipCtrl.h"
/////////////////////////////////////////////////////////////////////////////
// CCurveView view
 
typedef struct  {
	int x_start;
	int nID;
}Area,*LPAREA;

class CReportFrame;    
class CCurveView : public CScrollView
{
protected:
	CCurveView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CCurveView)

// Attributes
public:
	CReportFrame* m_pParent;
	LPAREA GetArea(int logx,int logy);
	LPAREA m_pArea;
	LPAREA m_pLastArea;
	int m_nAreaCount;

	CMyToolTipCtrl			m_OwnToolTipCtrl;
// Operations
public:
	void DrawInformation(CDC* pDC, LPGEN_INFO pinfo);
	void ClearAreaInfo();
	CPoint m_beginpt;
	BOOL m_bdown;
	static int CalDenoninator(int max);
	BOOL GetDisSpend();
	BOOL GetDisBalance();
	BOOL GetDisSave();
	void SetDisSave(BOOL b=TRUE);
	void SetDisBalance(BOOL b=TRUE);
	void SetDisSpend(BOOL b=TRUE);
	BOOL m_bDisSpend;
	BOOL m_bDisSave;
	BOOL m_bDisBalance;
	void DrawAllExpenseCurve(CDC *pDC);
	void DrawAllSaveCurve(CDC *pDC);
	CString m_curvename;
	void DrawName(CDC* pDC, CString strName);
	int m_beginyear;
	void SetBeginYear();
	BOOL bDraw;
	void GetMaxValue();
	void DrawCurve(CDC* pDC);
	int Get1999Days(COleDateTime time,BOOL bLocal=FALSE);
	int m_daysum;
	void DrawScale(CDC *pDC,int a,int b0,int b1,int number,int ahead, BOOL bV=TRUE);
	int m_denominator;
	void DrawCoordinate(CDC *pDC);
	BOOL CreateView(CWnd* pParent, CCreateContext* pContext);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCurveView)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnInitialUpdate();     // first time after construct
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CCurveView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CCurveView)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	//}}AFX_MSG
//	afx_msg BOOL OnNeedTipText(UINT id, NMHDR* pNMH, LRESULT* pResult);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CURVEVIEW_H__4556CC6E_7EBE_11D5_96DC_837659F4FF05__INCLUDED_)

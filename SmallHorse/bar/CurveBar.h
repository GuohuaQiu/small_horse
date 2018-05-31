// CurveBar.h : interface of the CCurveBar class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CurveBar_H__31A54C4A_F9C8_4C0A_9B39_D2AEA6C9D082__INCLUDED_)
#define AFX_CurveBar_H__31A54C4A_F9C8_4C0A_9B39_D2AEA6C9D082__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCurveView;

class CCurveBar : public CBCGPDockingControlBar
{
public:
	CCurveBar();

// Attributes
protected:
	CCurveView* m_pFormView;
	CCreateContext* m_pContext;

// Operations
public:
	void SetContext (CCreateContext* pContext)
	{
		m_pContext = pContext;
	}


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCurveBar)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCurveBar();

// Generated message map functions
protected:
	//{{AFX_MSG(CCurveBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CurveBar_H__31A54C4A_F9C8_4C0A_9B39_D2AEA6C9D082__INCLUDED_)

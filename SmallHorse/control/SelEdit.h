#if !defined(AFX_SELEDIT_H__E507C0C6_8AB2_11D5_96DC_E95000D44507__INCLUDED_)
#define AFX_SELEDIT_H__E507C0C6_8AB2_11D5_96DC_E95000D44507__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SelEdit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSelEdit window

class CSelEdit : public CEdit
{
// Construction
public:
	CSelEdit();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSelEdit)
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL m_bsel;
	virtual ~CSelEdit();

	// Generated message map functions
protected:
	//{{AFX_MSG(CSelEdit)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnSetfocus();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SELEDIT_H__E507C0C6_8AB2_11D5_96DC_E95000D44507__INCLUDED_)

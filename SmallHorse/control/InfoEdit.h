#if !defined(AFX_INFOEDIT_H__479D7582_620C_44F1_ABB7_7DAA348E2E64__INCLUDED_)
#define AFX_INFOEDIT_H__479D7582_620C_44F1_ABB7_7DAA348E2E64__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InfoEdit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CInfoEdit window

class CInfoEdit : public CEdit
{
// Construction
public:
	CInfoEdit();
  BOOL m_bWaiting;

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInfoEdit)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CInfoEdit();

	// Generated message map functions
protected:
	//{{AFX_MSG(CInfoEdit)
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INFOEDIT_H__479D7582_620C_44F1_ABB7_7DAA348E2E64__INCLUDED_)

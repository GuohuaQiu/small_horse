#if !defined(AFX_COMMENTPAGE_H__8E4C4197_F222_4C20_9FE1_F100A08757BE__INCLUDED_)
#define AFX_COMMENTPAGE_H__8E4C4197_F222_4C20_9FE1_F100A08757BE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CommentPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCommentPage dialog

class CCommentPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CCommentPage)

// Construction
public:
	CCommentPage();
	~CCommentPage();

// Dialog Data
	//{{AFX_DATA(CCommentPage)
	enum { IDD = IDD_S5 };
	CString	m_strComment;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CCommentPage)
	public:
	virtual BOOL OnWizardFinish();
	virtual LRESULT OnWizardNext();
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CCommentPage)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMMENTPAGE_H__8E4C4197_F222_4C20_9FE1_F100A08757BE__INCLUDED_)

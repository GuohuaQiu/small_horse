#if !defined(AFX_QUERYFROMCOMMENTDLG_H__0F0DFB5C_DB8D_4021_A4C9_8D5FB4E76F4B__INCLUDED_)
#define AFX_QUERYFROMCOMMENTDLG_H__0F0DFB5C_DB8D_4021_A4C9_8D5FB4E76F4B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// QueryFromCommentDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CQueryFromCommentDlg dialog

class CQueryFromCommentDlg : public CDialog
{
// Construction
public:
    CString m_strInfo;
	CQueryFromCommentDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CQueryFromCommentDlg)
	enum { IDD = IDD_QUERY_FROM_COMMENT };
	CString	m_strComment;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQueryFromCommentDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CQueryFromCommentDlg)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_QUERYFROMCOMMENTDLG_H__0F0DFB5C_DB8D_4021_A4C9_8D5FB4E76F4B__INCLUDED_)

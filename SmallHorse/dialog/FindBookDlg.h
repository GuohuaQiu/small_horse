#if !defined(AFX_FINDBOOKDLG_H__391D4D92_6C71_411B_B438_9DD40AB52284__INCLUDED_)
#define AFX_FINDBOOKDLG_H__391D4D92_6C71_411B_B438_9DD40AB52284__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FindBookDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFindBookDlg dialog

class CFindBookDlg : public CDialog
{
// Construction
public:
	CFindBookDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFindBookDlg)
	enum { IDD = IDD_FINDBOOK_SETUP };
	CString	m_strFind;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFindBookDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFindBookDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FINDBOOKDLG_H__391D4D92_6C71_411B_B438_9DD40AB52284__INCLUDED_)

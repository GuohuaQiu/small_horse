#if !defined(AFX_PASSWORDDLG_H__322F3BC0_8799_11D5_96DC_A6D90720BF07__INCLUDED_)
#define AFX_PASSWORDDLG_H__322F3BC0_8799_11D5_96DC_A6D90720BF07__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PassWordDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPassWordDlg dialog

class CPassWordDlg : public CDialog
{
// Construction
public:
	CPassWordDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPassWordDlg)
	enum { IDD = IDD_PASSWORD };
	CString	m_password;
	CString	m_id;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPassWordDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPassWordDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PASSWORDDLG_H__322F3BC0_8799_11D5_96DC_A6D90720BF07__INCLUDED_)

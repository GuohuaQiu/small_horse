#if !defined(AFX_PWDDLG_H__43DB85E0_F4D1_11D5_96DC_F924AD8FAE06__INCLUDED_)
#define AFX_PWDDLG_H__43DB85E0_F4D1_11D5_96DC_F924AD8FAE06__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Pwddlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPwddlg dialog

class CPwddlg : public CDialog
{
// Construction
public:
	CPwddlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPwddlg)
	enum { IDD = IDD_ENTRY };
	CString	m_pwd;
	CString	m_user;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPwddlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPwddlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PWDDLG_H__43DB85E0_F4D1_11D5_96DC_F924AD8FAE06__INCLUDED_)

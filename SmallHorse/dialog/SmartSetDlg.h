#if !defined(AFX_SMARTSETDLG_H__E0879E4D_A738_4650_887E_B95D36C30DD0__INCLUDED_)
#define AFX_SMARTSETDLG_H__E0879E4D_A738_4650_887E_B95D36C30DD0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SmartSetDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSmartSetDlg dialog

class CSmartSetDlg : public CDialog
{
// Construction
public:
	CSmartSetDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSmartSetDlg)
	enum { IDD = IDD_SET_RECORD_TYPE };
	CComboBox	m_cmbType;
	CString	m_strNoString;
	CString	m_strYesString;
	int		m_nTypeIndex;
	CString	m_strSite;
	BOOL	m_bActiveSite;
	BOOL	m_bActiveType;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSmartSetDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSmartSetDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SMARTSETDLG_H__E0879E4D_A738_4650_887E_B95D36C30DD0__INCLUDED_)

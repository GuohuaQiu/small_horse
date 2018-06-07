#if !defined(AFX_CREDITPAYDLG_H__0955E0A4_695E_4826_84D4_8840895FC65B__INCLUDED_)
#define AFX_CREDITPAYDLG_H__0955E0A4_695E_4826_84D4_8840895FC65B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CreditPayDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCreditPayDlg dialog

class CCreditPayDlg : public CDialog
{
// Construction
public:
	CCreditPayDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCreditPayDlg)
	enum { IDD = IDD_ADDCREDITCARD };
	CString	m_strComment;
	CString	m_strID;
	BYTE	m_datePay;
	BYTE	m_dateStatement;
	COleDateTime	m_EffectYearMonth;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCreditPayDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCreditPayDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CREDITPAYDLG_H__0955E0A4_695E_4826_84D4_8840895FC65B__INCLUDED_)

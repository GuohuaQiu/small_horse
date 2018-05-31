#if !defined(AFX_QUERYFROMMONEYDLG_H__0974ADA2_72CE_478B_A189_B6CCD21C2187__INCLUDED_)
#define AFX_QUERYFROMMONEYDLG_H__0974ADA2_72CE_478B_A189_B6CCD21C2187__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// QueryFromMoneyDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CQueryFromMoneyDlg dialog

//#include "NumEdit.h"
//#include "NumSpinCtrl.h"

class CQueryFromMoneyDlg : public CDialog
{
private:
    BOOL m_bValid;
// Construction
public:
	void RefreshInfo();
	CQueryFromMoneyDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CQueryFromMoneyDlg)
	enum { IDD = IDD_QUERY_FROM_MONEY };
	CSpinButtonCtrl	m_spinRange;
	CEdit	m_editRange;
	CEdit	m_ctrlEditSmall;
	CEdit	m_ctrlEditGreat;
	CButton	m_ctrlCheckSmall;
	CButton	m_ctrlCheckGreat;
	BOOL	m_bGreat;
	BOOL	m_bSmall;
	int		m_nSmall;
	int		m_nGreat;
	int		m_bOr;
	int		m_bSmallRange;
	int 	m_fRange;
	CString	m_strInfo;
	int		m_fBase;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQueryFromMoneyDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CQueryFromMoneyDlg)
	afx_msg void OnCheckGreat();
	afx_msg void OnCheckSmall();
	afx_msg void OnRadioAnd();
	afx_msg void OnRadioOr();
	virtual void OnOK();
	afx_msg void OnRadioRangeSimple();
	afx_msg void OnRadioRangeFree();
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeEditEqual();
	afx_msg void OnChangeEditMoneyRange();
	afx_msg void OnChangeEditGreat();
	afx_msg void OnChangeEditSmall();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_QUERYFROMMONEYDLG_H__0974ADA2_72CE_478B_A189_B6CCD21C2187__INCLUDED_)

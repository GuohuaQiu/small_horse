#if !defined(AFX_DINGQIINPUTDLG_H__F1EF8552_BE8A_47B1_9FDA_693EFBD8E707__INCLUDED_)
#define AFX_DINGQIINPUTDLG_H__F1EF8552_BE8A_47B1_9FDA_693EFBD8E707__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DingQiInputDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDingQiInputDlg dialog
#include "seledit.h"

class CDingQiInputDlg : public CDialog
{
// Construction
public:
    BOOL    m_bModifyMode;
	int     m_nMonth;
	BOOL	m_bNewItem;
	BOOL	m_bnewbook;
	BOOL	bgonext;
	CDingQiInputDlg(CWnd* pParent = NULL);   // standard constructor
	BOOL UpdateData (BOOL bSaveAndValidate = TRUE);

// Dialog Data
	//{{AFX_DATA(CDingQiInputDlg)
	enum { IDD = IDD_DINGQI_SAVE };
	CEdit	m_editSubCount;
	CComboBox	m_cmbSpan;
	CSelEdit	m_money;
    CBCGPDateTimeCtrl	m_wndDateTimePicker;
	COleDateTime	m_date;
	CString	m_id;
	CString	m_remain;
	int		m_nSpan;
	CString	m_strSubCount;
	float	m_sum;
	int		m_bNewSave;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDingQiInputDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDingQiInputDlg)
	afx_msg void OnNextinput();
	afx_msg void OnYES();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DINGQIINPUTDLG_H__F1EF8552_BE8A_47B1_9FDA_693EFBD8E707__INCLUDED_)











































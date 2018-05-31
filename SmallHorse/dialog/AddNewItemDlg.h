#if !defined(AFX_ADDNEWITEMDLG_H__2BE29A20_8044_11D5_96DC_D3771AD7D905__INCLUDED_)
#define AFX_ADDNEWITEMDLG_H__2BE29A20_8044_11D5_96DC_D3771AD7D905__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AddNewItemDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAddNewItemDlg dialog
#include "SelEdit.h"
#include "..\resource.h"
#include "AutoCompl.h"

class CAddNewItemDlg : public CDialog
{
// Construction
public:
	BOOL UpdateData (BOOL bSaveAndValidate = TRUE);
	BOOL	m_bNewItem;
	BOOL	m_bnewbook;
	BOOL	bgonext;
	CAddNewItemDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAddNewItemDlg)
	enum { IDD = IDD_ADDRECORD };
	CAutoComplete m_cmbSite;			 // hook for combo box
	CComboBox	m_cmbSubCount;
	CComboBox	m_cmbType;
	CSelEdit	m_money;
    CBCGPDateTimeCtrl	m_wndDateTimePicker;
	COleDateTime	m_date;
	CString	m_sum;
	CString	m_id;
	CString	m_remain;
	int		m_nType;
	CString	m_strSubCount;
	CString	m_strSite;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAddNewItemDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAddNewItemDlg)
	afx_msg void OnNextinput();
	afx_msg void OnYES();
	afx_msg void OnAddDefaultNotes();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADDNEWITEMDLG_H__2BE29A20_8044_11D5_96DC_D3771AD7D905__INCLUDED_)

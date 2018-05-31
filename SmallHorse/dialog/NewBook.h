#if !defined(AFX_NEWBOOK_H__64A739E5_8069_11D5_96DC_D3771AD7D905__INCLUDED_)
#define AFX_NEWBOOK_H__64A739E5_8069_11D5_96DC_D3771AD7D905__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NewBook.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNewBook dialog

class CNewBook : public CDialog
{
// Construction
public:
    CIDSet* m_pIDSet;
    BOOL m_bModeNew;//new or modify

	CNewBook(CIDSet* pIDSet ,BOOL bModeNew = TRUE,CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CNewBook)
	enum { IDD = IDD_ADDNEWBANKBOOK };
	CEdit	m_editID;
	CComboBox	m_cmbType;
	CComboBox	m_cmbBank;
	CString	m_newcomit;
	CString	m_newbank;
	CString	m_newname;
	CString	m_newid;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNewBook)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNewBook)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NEWBOOK_H__64A739E5_8069_11D5_96DC_D3771AD7D905__INCLUDED_)

#if !defined(AFX_QUERYENDDLG_H__D164CE00_DBAC_11D5_96DC_D59E2F29DF05__INCLUDED_)
#define AFX_QUERYENDDLG_H__D164CE00_DBAC_11D5_96DC_D59E2F29DF05__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// QueryEndDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CQueryEndDlg dialog
#include "ListSet.h"
#include "IDSet.h"
class CQueryEndDlg : public CDialog
{
// Construction
public:
	CListSet* m_plistset;
	CIDSet* m_pidset;
	CQueryEndDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CQueryEndDlg)
	enum { IDD = IDD_QUERYEND };
	CListCtrl	m_list;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQueryEndDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CQueryEndDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSaveResult();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_QUERYENDDLG_H__D164CE00_DBAC_11D5_96DC_D59E2F29DF05__INCLUDED_)

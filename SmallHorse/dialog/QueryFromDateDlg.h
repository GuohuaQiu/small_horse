#if !defined(AFX_QUERYFROMDATEDLG_H__2180F306_FE4E_49ED_A8D7_F0B8D25FE77E__INCLUDED_)
#define AFX_QUERYFROMDATEDLG_H__2180F306_FE4E_49ED_A8D7_F0B8D25FE77E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// QueryFromDateDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CQueryFromDateDlg dialog

class CQueryFromDateDlg : public CDialog
{
// Construction
public:
	CQueryFromDateDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CQueryFromDateDlg)
	enum { IDD = IDD_QUERY_FROM_DATE };
	COleDateTime	m_dateMid;
	CString	m_strInfo;
	int		m_nBound;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQueryFromDateDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CQueryFromDateDlg)
	afx_msg void OnChangeEditDateBound();
	afx_msg void OnDatetimechangeDatetimepicker(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_QUERYFROMDATEDLG_H__2180F306_FE4E_49ED_A8D7_F0B8D25FE77E__INCLUDED_)

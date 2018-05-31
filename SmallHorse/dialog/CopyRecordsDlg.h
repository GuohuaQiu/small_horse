#if !defined(AFX_COPYRECORDSDLG_H__69EC9335_054B_4432_A130_6B870134FD81__INCLUDED_)
#define AFX_COPYRECORDSDLG_H__69EC9335_054B_4432_A130_6B870134FD81__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CopyRecordsDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCopyRecordsDlg dialog

class CCopyRecordsDlg : public CDialog
{
// Construction
public:
	CCopyRecordsDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCopyRecordsDlg)
	enum { IDD = IDD_COPY_RECORDS };
	BOOL	m_bTransfer;
	CString	m_mainCount;
	CString	m_SubCount;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCopyRecordsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCopyRecordsDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COPYRECORDSDLG_H__69EC9335_054B_4432_A130_6B870134FD81__INCLUDED_)

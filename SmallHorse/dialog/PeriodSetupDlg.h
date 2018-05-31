#if !defined(AFX_PERIODSETUPDLG_H__777AD216_A66B_4086_9562_956D0DB80479__INCLUDED_)
#define AFX_PERIODSETUPDLG_H__777AD216_A66B_4086_9562_956D0DB80479__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PeriodSetupDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPeriodSetupDlg dialog

class CPeriodSetupDlg : public CDialog
{
// Construction
public:
	CPeriodSetupDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPeriodSetupDlg)
	enum { IDD = IDD_PERIOD_SETUP };
	COleDateTime	m_timeBegin;
	COleDateTime	m_timeEnd;
	COleDateTime	m_timePay;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPeriodSetupDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPeriodSetupDlg)
		afx_msg void OnNextMonth();
		afx_msg void OnPrevMonth();
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PERIODSETUPDLG_H__777AD216_A66B_4086_9562_956D0DB80479__INCLUDED_)

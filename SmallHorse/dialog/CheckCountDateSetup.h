#if !defined(AFX_CHECKCOUNTDATESETUP_H__B9AD4DAB_2381_44C1_945E_9D884DB6B733__INCLUDED_)
#define AFX_CHECKCOUNTDATESETUP_H__B9AD4DAB_2381_44C1_945E_9D884DB6B733__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CheckCountDateSetup.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCheckCountDateSetup dialog

class CCheckCountDateSetup : public CDialog
{
// Construction
public:
	CCheckCountDateSetup(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCheckCountDateSetup)
	enum { IDD = IDD_CHECKMONTHVALUE };
	int		m_dateEnd;
	int		m_datePay;
	COleDateTime	m_timeBegin;
	COleDateTime	m_timeEnd;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCheckCountDateSetup)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCheckCountDateSetup)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHECKCOUNTDATESETUP_H__B9AD4DAB_2381_44C1_945E_9D884DB6B733__INCLUDED_)

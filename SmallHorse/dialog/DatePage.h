#if !defined(AFX_DATEPAGE_H__499A95DE_737C_40AF_B403_742712849346__INCLUDED_)
#define AFX_DATEPAGE_H__499A95DE_737C_40AF_B403_742712849346__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DatePage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDatePage dialog

class CDatePage : public CPropertyPage
{
	DECLARE_DYNCREATE(CDatePage)

// Construction
public:
	CDatePage();
	~CDatePage();

// Dialog Data
	//{{AFX_DATA(CDatePage)
	enum { IDD = IDD_S2 };
	CDateTimeCtrl	m_DateCtrlBegin;
    CDateTimeCtrl	m_DateCtrlEnd;
	BOOL	m_bAllTime;
	COleDateTime	m_BeginTime;
	COleDateTime	m_EndTime;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDatePage)
	public:
	virtual BOOL OnSetActive();
	virtual LRESULT OnWizardNext();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDatePage)
	virtual BOOL OnInitDialog();
	afx_msg void OnCheckAlldate();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DATEPAGE_H__499A95DE_737C_40AF_B403_742712849346__INCLUDED_)

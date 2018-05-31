#if !defined(AFX_TYPEPAGE_H__2DC44E33_557D_490F_AA7F_DF0109FBFB2E__INCLUDED_)
#define AFX_TYPEPAGE_H__2DC44E33_557D_490F_AA7F_DF0109FBFB2E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TypePage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTypePage dialog

class CTypePage : public CPropertyPage
{
	DECLARE_DYNCREATE(CTypePage)

// Construction
public:
	CTypePage();
	~CTypePage();

// Dialog Data
	//{{AFX_DATA(CTypePage)
	enum { IDD = IDD_S3 };
	CListBox	m_listTarget;
	CListBox	m_listSrc;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CTypePage)
	public:
	virtual BOOL OnApply();
	virtual BOOL OnSetActive();
	virtual LRESULT OnWizardNext();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CTypePage)
	virtual BOOL OnInitDialog();
	afx_msg void OnDblclkListSrcType();
	afx_msg void OnDblclkListTargetType();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TYPEPAGE_H__2DC44E33_557D_490F_AA7F_DF0109FBFB2E__INCLUDED_)

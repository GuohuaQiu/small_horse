#if !defined(AFX_NAMEPAGE_H__59C8A28E_B848_4696_9D7F_FA49C71494D7__INCLUDED_)
#define AFX_NAMEPAGE_H__59C8A28E_B848_4696_9D7F_FA49C71494D7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NamePage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNamePage dialog
#include "idset.h"
class CNamePage : public CPropertyPage
{
	DECLARE_DYNCREATE(CNamePage)

// Construction
public:
	CIDSet*	m_pIDSet;
	CNamePage();
	~CNamePage();

// Dialog Data
	//{{AFX_DATA(CNamePage)
	enum { IDD = IDD_S1 };
	CListBox	m_listTarget;
	CListBox	m_listSrc;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CNamePage)
	public:
	virtual BOOL OnWizardFinish();
	virtual LRESULT OnWizardNext();
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CNamePage)
	virtual BOOL OnInitDialog();
	afx_msg void OnDblclkListSrcName();
	afx_msg void OnDblclkListTargetName();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NAMEPAGE_H__59C8A28E_B848_4696_9D7F_FA49C71494D7__INCLUDED_)

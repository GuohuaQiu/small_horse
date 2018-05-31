#if !defined(AFX_FILESELPAGE_H__11835598_DFC6_489E_A315_018A49A31214__INCLUDED_)
#define AFX_FILESELPAGE_H__11835598_DFC6_489E_A315_018A49A31214__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FileSelPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFileSelPage dialog
class CImportSheet;

class CFileSelPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CFileSelPage)

// Construction
public:
	CFileSelPage();
	CFileSelPage(CImportSheet* pParent);
	~CFileSelPage();
	CImportSheet* m_pParent;
	
// Dialog Data
	//{{AFX_DATA(CFileSelPage)
	enum { IDD = IDD_IMPORT1 };
	CString	m_strFile;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CFileSelPage)
	public:
	virtual BOOL OnSetActive();
	virtual BOOL OnKillActive();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CFileSelPage)
    afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnSelectfile();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILESELPAGE_H__11835598_DFC6_489E_A315_018A49A31214__INCLUDED_)

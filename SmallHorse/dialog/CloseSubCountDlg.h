#if !defined(AFX_CLOSESUBCOUNTDLG_H__4F7E1EE9_3D64_44B9_AC27_0F2D6A22D98A__INCLUDED_)
#define AFX_CLOSESUBCOUNTDLG_H__4F7E1EE9_3D64_44B9_AC27_0F2D6A22D98A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CloseSubCountDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCloseSubCountDlg dialog

class CCloseSubCountDlg : public CDialog
{
// Construction
public:
	COleDateTime	m_closeDate;
	CCloseSubCountDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCloseSubCountDlg)
	enum { IDD = IDD_CLOSE_SUBCOUNT };
    CBCGPDateTimeCtrl	m_wndDateTimePicker;
	BOOL	m_bSavetoDefault;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCloseSubCountDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCloseSubCountDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLOSESUBCOUNTDLG_H__4F7E1EE9_3D64_44B9_AC27_0F2D6A22D98A__INCLUDED_)

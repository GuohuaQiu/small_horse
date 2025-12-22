// WorkspaceBar.h : interface of the CWorkspaceBar2 class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_WORKSPACEBAR2_H__2BDE8F87_871B_4B6E_981B_946A4833AE34__INCLUDED_)
#define AFX_WORKSPACEBAR2_H__2BDE8F87_871B_4B6E_981B_946A4833AE34__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "infoedit.h"

class CMyListCtrl : public CBCGPListCtrl
{
    virtual COLORREF OnGetCellTextColor (int nRow, int nColum);
    virtual COLORREF OnGetCellBkColor (int nRow, int nColum);
};

class CWorkspaceBar2 : public CBCGPDockingControlBar
{
public:
	CWorkspaceBar2();

// Attributes
protected:
	CMyListCtrl   m_wndList; 
	CInfoEdit   m_wndIdEdit;
	CFont		m_Font;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWorkspaceBar2)
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL GetSelectedID(CString& strID);
	virtual ~CWorkspaceBar2();

// Generated message map functions
protected:
	//{{AFX_MSG(CWorkspaceBar2)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg void OnIDEditChanged();
	afx_msg void OnDblclkList2(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnRclickList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnRectifyinfo();
	afx_msg void OnAddReturnRecord();
	afx_msg void OnSetAsAutoReturnCard();
	afx_msg void OnSetAsAutoreturnCredit();
	afx_msg void OnTransferDingqi();
	afx_msg void OnInfo();
	afx_msg void OnDoubtInfo();
	afx_msg void OnAddrecord();
	afx_msg void OnOpenSubcountById();
	afx_msg void OnAddCreditPayInfo();
	afx_msg void OnMenuCreditReport();
	afx_msg void OnUpdateMenuCreditReport(CCmdUI* pCmdUI);
	afx_msg void OnCountLock();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WORKSPACEBAR2_H__2BDE8F87_871B_4B6E_981B_946A4833AE34__INCLUDED_)

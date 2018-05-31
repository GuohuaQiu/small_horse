#if !defined(AFX_BANKBOOKTREE_H__4F8D99E8_7670_47B0_A393_91B8D6EA1841__INCLUDED_)
#define AFX_BANKBOOKTREE_H__4F8D99E8_7670_47B0_A393_91B8D6EA1841__INCLUDED_

#include "IDSet.h"	// Added by ClassView
#include "ListSet.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BankbookTree.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBankbookTree window

class CBankbookTree : public CTreeCtrl
{
// Construction
public:
	CBankbookTree();

// Attributes
public:
#ifdef _DEBUG
    CBitmap m_bmBG;
#endif
	HTREEITEM m_hBank;
	HTREEITEM m_hPeople;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBankbookTree)
	//}}AFX_VIRTUAL

// Implementation
public:
	void ReloadAll(void);
	BOOL MovetoSelectedBankbook(CIDSet* pIdSet);
	CString GetSelectedText();
	void DisplayStaticInfo();
	BOOL IsPeople(HTREEITEM item);
	void QueryPeople(CString strname,BOOL bDisBill=FALSE);
	void AddTreeItem(HTREEITEM hparent,CString str);
	void AddTreeGroup(HTREEITEM htree);
	void DisplayBookInfo();
	void DeleteBook();
	BOOL IsBandbook();
	void AddNewItem(BOOL bFirstItem=FALSE);
	CBitmap m_bmpmenu;
	BOOL IsBandbook(HTREEITEM hItem);
	BOOL ValidatePassWord();
	void DisplayRecord(CString strID);
	CImageList* m_pImageList;
	virtual ~CBankbookTree();

	// Generated message map functions
protected:
	//{{AFX_MSG(CBankbookTree)
	afx_msg void OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemexpanding(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRectifypassword();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnAddrecord();
	afx_msg void OnDeletebook();
	afx_msg void OnInfo();
	afx_msg void OnRectifyinfo();
	afx_msg void OnBankbookFree();
	afx_msg void OnSetAsAutoReturnCredit();
	afx_msg void OnFindBook();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnDblclk(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnTransferDingqi();
	afx_msg void OnOpenSubcountById();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnAddCreditPayInfo();
	afx_msg void OnUpdateAddCreditPayInfo(CCmdUI* pCmdUI);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	void FillEmptyTree();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BANKBOOKTREE_H__4F8D99E8_7670_47B0_A393_91B8D6EA1841__INCLUDED_)

// CompareFrame.h: interface for the CCompareFrame class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMPAREFRAME_H__5180C78C_1F26_456A_A4E0_5FBD8C1F6CCB__INCLUDED_)
#define AFX_COMPAREFRAME_H__5180C78C_1F26_456A_A4E0_5FBD8C1F6CCB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ListCompare.h"

class CCompareListCtrl;
class CCompareDetailCtrl;
typedef void (*CB_FUNC_HANDLE_ITEM)(DWORD dwThis,void* pitem) ;

class CCompareFrame : public CBCGPMDIChildWnd
{
	DECLARE_DYNCREATE(CCompareFrame)
public:
	CCompareFrame();

// Attributes
protected:
	CSplitterWnd m_wndSplitter;
    CListCompare m_listCmp;
    CCompareListCtrl* m_pListCtrl;
    CCompareDetailCtrl* m_pDetailCtrl;



public:
    CCompareListCtrl* GetTopPane();
    CCompareDetailCtrl* GetBottomPane();
    static void InitListCtrl(CCompareListCtrl* pCtrl);

    // Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCompareFrame)
	public:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	static void Callback_OnItemDbClk(LPVOID pThis,CBCGPGridRow* pRow);
	void AddTail(Record *precord,int nOffset = 0);
	void AddAlike(Alike2* palike);
	void AddRightRecord(Record *precord);
	void AddLeftRecord(Record* precord);
	void LoadData();

	static void AddAlike(DWORD pThis, void *pRecord);
    static void AddLeft(DWORD pThis, void *pRecord);
    
    static void AddRight(DWORD pThis, void *pRecord);



	virtual ~CCompareFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
// Generated message map functions
protected:
	//{{AFX_MSG(CCompareFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	afx_msg void OnUpdateViewStyles(CCmdUI* pCmdUI);
	afx_msg void OnViewStyle(UINT nCommandID);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
#endif // !defined(AFX_COMPAREFRAME_H__5180C78C_1F26_456A_A4E0_5FBD8C1F6CCB__INCLUDED_)



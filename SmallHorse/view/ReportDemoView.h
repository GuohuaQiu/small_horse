// ReportDemoView.h : interface of the CReportDemoView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_REPORTDEMOVIEW_H__AC23BEA5_8CE3_4B70_B0C3_2D73D6683483__INCLUDED_)
#define AFX_REPORTDEMOVIEW_H__AC23BEA5_8CE3_4B70_B0C3_2D73D6683483__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MailReportCtrl.h"
#include "reportframe.h"

/////////////////////////////////////////////////////////////////////////////
// CFlagItem class

class CFlagItem: public CBCGPGridItem
{
public:
	CFlagItem(
		CBCGPToolBarImages& icons,
		int nSelectedIcon,
		DWORD dwData = 0
	);

public:
	virtual BOOL OnClickValue (UINT uiMsg, CPoint point);
	
protected:
	virtual void OnDrawValue (CDC* pDC, CRect rect);
	virtual void OnPrintValue (CDC* /*pDC*/, CRect /*rect*/) {}
	CBCGPToolBarImages&	m_Icons;
};

/////////////////////////////////////////////////////////////////////////////
// CReportDemoView

class CReportDemoView : public CBCGPReportView
{
    friend class CGroupRow;
protected: // create from serialization only
	VIEW_TYPE    m_ViewType;
	CReportFrame* m_pParent;
	BOOL m_bFirst;
	CReportDemoView();
	DECLARE_DYNCREATE(CReportDemoView)

// Attributes
public:
    BOOL GetPeriod(CString strid,int nYear, int nMonth,COleDateTime& timeBegin,COleDateTime& timeEnd);
	BOOL CheckBill(int nYear, int nMonth, COleDateTime &timeBegin, COleDateTime &timeEnd, COleDateTime &timePay,float& fUse,float& fPay);
	void ExportCreditRecord(const COleDateTime &timeBegin, const COleDateTime &timeEnd,const COleDateTime& timePay);
	void DisplayCreditDetail(int nYear, int nMonth);
	void SelectMaxIndexItem();
	static void DoSerialize(CArchive& ar,CListSet* pList,BOOL bToList);
	void DisplayRecord();
	float AddMembertoList(CListSet* pSet,int index,BOOL bCalSum=FALSE,float sum1=0);
protected:
	//Simon no need CImageList			m_ImagesHeader;
	CImageList			m_Images;
	//Simon no need CBCGPToolBarImages	m_Flags;
	enum IMPORTANCE
	{
		IMPORTANCE_NORMAL,
		IMPORTANCE_HIGH,
		IMPORTANCE_LOW
	};
	
// Operations
public:

// Overrides
	CBCGPGridCtrl* CreateGrid ()
	{
		return new CMailReportCtrl;
	}

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReportDemoView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	//}}AFX_VIRTUAL

// Implementation
public:
	void CopyRecordsTo(const CString& strCount);
	void MoveRecordsTo(const CString& strCount);
	BOOL DisplayReport();
#if 0
	void CheckBill(int nYear, int nMonth,COleDateTime& timeBegin);
#endif
	void BrowseToBackYear(int backYear);
	void FillItems();
	static void Callback_OnItemDbClk(LPVOID pThis,CBCGPGridRow* pRow);
	void DisplayCount();
	void AddSubCount2List(int index,CRecordset* pSet);
	void CreateListCtrl();
	void AdjustColumnWidth();
	void SetSelectedRow(const int nRecordArray);
	virtual ~CReportDemoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
// Generated message map functions
protected:
	//{{AFX_MSG(CReportDemoView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnViewColumnsselector();
	afx_msg void OnUpdateViewColumnsselector(CCmdUI* pCmdUI);
	afx_msg void OnDestroy();
	afx_msg void OnViewGroupbox();
	afx_msg void OnUpdateViewGroupbox(CCmdUI* pCmdUI);
	afx_msg void OnViewColumnAutoResize();
	afx_msg void OnUpdateViewColumnAutoResize(CCmdUI* pCmdUI);
	afx_msg void OnReportExpandAll();
	afx_msg void OnReportCollapseAll();
	afx_msg void OnAddRecord();
	afx_msg void OnCalsum();
	afx_msg void OnQueryThisDay();
	afx_msg void OnRectifyPassword();
	afx_msg void OnDeleteRecord();
	afx_msg void OnEditRecord();
	afx_msg void OnEditPaste();
	afx_msg void OnEditCopy();
	afx_msg void OnExportCsv();
	afx_msg void OnLoadCsv();
	afx_msg void OnCalCredit();
	afx_msg void OnCreditPeroid();
	afx_msg void OnSmartSetType();
	afx_msg void OnReplaceComment();
	afx_msg void OnAddReturnRecord();
	afx_msg void OnUpdateEditCopy(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditPaste(CCmdUI* pCmdUI);
	afx_msg void OnDeletebook();
	afx_msg void OnUpdateDeletebook(CCmdUI* pCmdUI);
	afx_msg void OnRectifyinfo();
	afx_msg void OnUpdateRectifyinfo(CCmdUI* pCmdUI);
	afx_msg void OnInfo();
	afx_msg void OnUpdateInfo(CCmdUI* pCmdUI);
	afx_msg void OnBankbookFree();
	afx_msg void OnSetAsAutoReturnCard();
	afx_msg void OnSetAsAutoreturnCredit();
	afx_msg void OnTransferDingqi();
	afx_msg void OnFindBook();
	afx_msg void OnModifySubcount();
	afx_msg void OnRenewSubcount();
	afx_msg void OnOpenSubcountById();
	afx_msg void OnUpdateOpenSubcountById(CCmdUI* pCmdUI);
	afx_msg void OnSubcountClose();
	afx_msg void OnUpdateSubcountClose(CCmdUI* pCmdUI);
	afx_msg void OnExpandActiveItem();
	afx_msg void OnExpandAllItem();
	afx_msg void OnCollapseAllItem();
	afx_msg void OnCollapseInactiveInactive();
	afx_msg void OnBrowseYear(UINT nID);
	afx_msg void OnUpdateAddReturnRecord(CCmdUI* pCmdUI);
	afx_msg void OnUpdateTransferDingqi(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCalCredit(CCmdUI* pCmdUI);
	afx_msg void OnCheckBill();
	afx_msg void OnCopyRecordsTo(UINT nID);
	afx_msg void OnMoveRecordsTo(UINT nID);
	//}}AFX_MSG
	afx_msg void OnContextMenu(CWnd*, CPoint point);
	afx_msg void OnFilePrintPreview();
    afx_msg void OnDropFiles(HDROP hDropInfo);
	DECLARE_MESSAGE_MAP()
#if 0 //Simon no need
	BOOL AddMail (int nIcon, LPCTSTR strFrom, LPCTSTR strTo,
		 LPCTSTR strSubject, COleDateTime dateCreated, 
		 COleDateTime dateReceived, long lSize, 
		 IMPORTANCE importance = IMPORTANCE_NORMAL,
		 BOOL bHasAttachment = FALSE,
		 int nFlag = 0);
#endif
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REPORTDEMOVIEW_H__AC23BEA5_8CE3_4B70_B0C3_2D73D6683483__INCLUDED_)

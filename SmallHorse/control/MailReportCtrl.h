#if !defined(AFX_MAILREPORTCTRL_H__4C52E118_4FB2_4BBD_8D59_6F9E5A493C80__INCLUDED_)
#define AFX_MAILREPORTCTRL_H__4C52E118_4FB2_4BBD_8D59_6F9E5A493C80__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MailReportCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMailReportCtrl window
typedef void (*CB_FUNC_ONDBCLK_ITEM)(LPVOID pThis,CBCGPGridRow* pRow) ;

class CCompareDetailCtrl;
class CMailReportCtrl : public CBCGPReportCtrl
{
    friend class CGroupRow;
// Construction
public:
	CB_FUNC_ONDBCLK_ITEM m_pCbFun;
	CMailReportCtrl();
    DECLARE_DYNCREATE(CMailReportCtrl)
    CCompareDetailCtrl* m_pDetailCtrl;


// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMailReportCtrl)
	//}}AFX_VIRTUAL

	virtual int CompareGroup (const CBCGPGridRow* pRow1, const CBCGPGridRow* pRow2, int iColumn);
	virtual CString GetGroupName (int nGroupCol, CBCGPGridItem* pItem);
	
// Implementation
public:
	CBCGPGridRow* CreateRow (int nColumns);
	void CollapseAllInactiveGroup();
	void CollapseAllGroup();
	void ExpandAllGroup();
	void ExpandAllActiveGroup();
	static void SetRowBackColor(CBCGPGridRow* pRow, COLORREF crBkColor);
	virtual CBCGPGridRow* CreateRow (CString strName);
	virtual void TrackToolTip (CPoint point);
	BOOL ToggleEditInPlace();
	CBCGPGridRow* GetFirstSelectedRow();
	int GetSelectedRows(CDWordArray& rowArray);
	void Test();
	void SetDbClkCBFunc(CB_FUNC_ONDBCLK_ITEM pfun);
	virtual ~CMailReportCtrl();

	//--------------
	// Drag and drop
	//--------------
	virtual BOOL OnHideInsertedGroupColumn (int nColumn) const
	{
		return TRUE;
	}
protected:
    BOOL m_bEditOnline;
	// Generated message map functions
protected:
	virtual BOOL AllowInPlaceEdit () const
	{
		return m_bEditOnline; // disable inplace editing
	}
	
	virtual BOOL IsSelectionBorderEnabled () const
	{
		return FALSE;
	}
	
protected:
	//{{AFX_MSG(CMailReportCtrl)
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAILREPORTCTRL_H__4C52E118_4FB2_4BBD_8D59_6F9E5A493C80__INCLUDED_)

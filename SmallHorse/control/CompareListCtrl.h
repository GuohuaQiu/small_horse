// CompareListCtrl.h: interface for the CCompareListCtrl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMPARELISTCTRL_H__4AA646A6_C1B2_47C3_B355_BF98E7332251__INCLUDED_)
#define AFX_COMPARELISTCTRL_H__4AA646A6_C1B2_47C3_B355_BF98E7332251__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MailReportCtrl.h"
class CListCompare;
class CCompareListCtrl : public CMailReportCtrl  
{
public:
    DECLARE_DYNCREATE(CCompareListCtrl)
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCompareListCtrl)
	//}}AFX_VIRTUAL
// Implementation
public:
	void MakeManualJoin();
	void InitCompareCtrl(CB_FUNC_ONDBCLK_ITEM pfun,CListCompare* pListCompare);
	void UpdateRow(CBCGPGridRow* pRow);
	void AddAlike(Alike2* pAlike);
	void UpdateRow(Alike2* pAlike);
    CJoinedList *m_pJoinList;
    CListCompare *m_pListCompare;
    static Alike2 *m_pJoinA;
    static Alike2 *m_pJoinB;

	CCompareListCtrl();
	virtual ~CCompareListCtrl();

protected:
	//{{AFX_MSG(CCompareListCtrl)
	afx_msg void OnCompareCopyToRight();
	afx_msg void OnUpdateCompareCopyToRight(CCmdUI* pCmdUI);
	afx_msg void OnCompareCopyToLeft();
	afx_msg void OnUpdateCompareCopyToLeft(CCmdUI* pCmdUI);
	afx_msg void OnCompareSave();
	afx_msg void OnUpdateCompareSave(CCmdUI* pCmdUI);
	afx_msg void OnComapreJoin();
	//}}AFX_MSG
	afx_msg void OnContextMenu(CWnd*, CPoint point);
    DECLARE_MESSAGE_MAP()
};

#endif // !defined(AFX_COMPARELISTCTRL_H__4AA646A6_C1B2_47C3_B355_BF98E7332251__INCLUDED_)

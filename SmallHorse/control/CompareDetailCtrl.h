// CompareDetailCtrl.h: interface for the CCompareDetailCtrl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMPAREDETAILCTRL_H__5780CD3A_C27C_4166_836E_9D93BAF651AC__INCLUDED_)
#define AFX_COMPAREDETAILCTRL_H__5780CD3A_C27C_4166_836E_9D93BAF651AC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MailReportCtrl.h"




#define LINE_OPER_DAY       0
#define LINE_VALUE          1
#define LINE_COMMENT        2
#define LINE_SITE           3
#define LINE_TYPE           4

#define LINE_ACCOUNT        5
#define LINE_SUB_COUNT      6
#define LINE_ARRAY_NUMBER   7
#define LINE_ADD_TIME       8
#define LINE_MODIFY_TIME    9
#define LINE_COUNT          10



class CCompareDetailCtrl : public CBCGPReportCtrl  
{
public:
    DECLARE_DYNCREATE(CCompareDetailCtrl)
public:
	void SetItemsColor();
    Alike2 * m_pAlike;

	void FillContent(int nColumn,LPRECORD pRecord);
	CBCGPGridItem* GetDetailItem(int line, int column);
	void Setup();
	void ShowDetail(CBCGPGridRow *pRow);
	CCompareDetailCtrl();
	virtual ~CCompareDetailCtrl();

protected:
	//{{AFX_MSG(CCompareDetailCtrl)

	//}}AFX_MSG
	afx_msg void OnContextMenu(CWnd*, CPoint point);
    DECLARE_MESSAGE_MAP()

};

#endif // !defined(AFX_COMPAREDETAILCTRL_H__5780CD3A_C27C_4166_836E_9D93BAF651AC__INCLUDED_)

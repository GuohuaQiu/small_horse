#if !defined(AFX_QIUHEADCTRL_H__DD53C228_0921_4312_AFF6_BE5146C580A0__INCLUDED_)
#define AFX_QIUHEADCTRL_H__DD53C228_0921_4312_AFF6_BE5146C580A0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// QiuHeadCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CQiuHeadCtrl window
#include "Convertdata.h"

class CQiuHeadCtrl : public CHeaderCtrl
{
// Construction
public:
	CQiuHeadCtrl();
	void SetColumnName(int count, TCHAR* pNames,int nAttrArry[]);
	BOOL ValidateNames();
	int* GetNameIndex();
	int GetAddToComments(int** ppATC);
// Attributes
private:
	int m_nFieldCount;
	TCHAR *m_pFieldNames;
	int* m_pIndex;
	int* m_pFieldAttr;

	//Below item for "add to comments"
	int m_TotalColumnCount;
	int *m_pAddToComments;
	void SetColumeAs(int col_index,int name_index);
	void UpdateName(int col_index);
	void ClearName(int col_index);

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQiuHeadCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	CString GetItemString(int nIndex);
	virtual ~CQiuHeadCtrl();
private:
	int m_nLastSelectedItem;
	void AddToComments(int col_index);
	// Generated message map functions
protected:
	//{{AFX_MSG(CQiuHeadCtrl)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnMenuitem(UINT nID);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_QIUHEADCTRL_H__DD53C228_0921_4312_AFF6_BE5146C580A0__INCLUDED_)

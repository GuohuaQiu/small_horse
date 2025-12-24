#if !defined(AFX_SELFILEPAGE_H__93A901A0_4624_48CA_8985_BD7CC671D429__INCLUDED_)
#define AFX_SELFILEPAGE_H__93A901A0_4624_48CA_8985_BD7CC671D429__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SelFilePage.h : header file
//
#include "QiuHeadCtrl.h"
#include "..\database\ListSet.h" // 引入 IMPORT_ITEM 定义
#include "..\database\SubCountSet.h" // 引入 SUBCOUNT_IMPORT_ITEM

/////////////////////////////////////////////////////////////////////////////
// CImportListPage dialog
class CImportSheet;

class CImportListPage : public CPropertyPage
{
    DECLARE_DYNCREATE(CImportListPage)

// Construction
public:
    void ReFillbyPaste();
    int FindSubCountConflict(int nType[]);
    int FindConflict(int nType[5]);
    BOOL SaveDataToDataLib();
    
    // 新增：负责将 UI 数据转换为中间结构
    void PrepareImportData(std::vector<IMPORT_ITEM>& items, int nType[], const CString& strId, int pATC[], int column_count);

    // 新增：负责将 UI 数据转换为中间结构 (SubCountSet)
    void PrepareSubCountImportData(std::vector<SUBCOUNT_IMPORT_ITEM>& items, int nType[], const CString& strMainCount);

    void ReFill();
    CImportListPage();
    CImportListPage(CImportSheet* pParent);
    ~CImportListPage();
    CImportSheet* m_pParent;

// Dialog Data
	//{{AFX_DATA(CImportListPage)
	enum { IDD = IDD_IMPORT2 };
	CListCtrl	m_listctrl;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CImportListPage)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CQiuHeadCtrl m_qiuheadCtrl;
	// Generated message map functions
	//{{AFX_MSG(CImportListPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnMarkall();
	afx_msg void OnUnmarkall();
	afx_msg void OnMarkseled();
	afx_msg void OnUnmarkselected();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	int GetCheckedCount();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SELFILEPAGE_H__93A901A0_4624_48CA_8985_BD7CC671D429__INCLUDED_)

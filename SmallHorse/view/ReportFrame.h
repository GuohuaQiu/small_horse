// ChildFrm.h : interface of the CReportFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHILDFRM_H__B535331C_179F_4FD8_9547_9449B7BFA6A8__INCLUDED_)
#define AFX_CHILDFRM_H__B535331C_179F_4FD8_9547_9449B7BFA6A8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CurveBar.h"
#include "Convertdata.h"

class CReportFrame : public CBCGPMDIChildWnd
{
	DECLARE_DYNCREATE(CReportFrame)
public:
	VIEW_TYPE m_ViewType;
	CReportFrame();

// Attributes
public:
	CString m_strID;
	CString m_strFilter;
	CString m_strSort;
	CString m_strTitle;
    CString m_strPagePath;
    GEN_INFO mInformation;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReportFrame)
	virtual void OnUpdateFrameTitle(BOOL bAddToTitle);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void ActivateFrame(int nCmdShow);
	//}}AFX_VIRTUAL

// Implementation
public:
    void SetReportInfo(const CString &strID);
	void SetPage(LPCTSTR lpPagePath);
	void CreateCurveView();
	void SetCountsFilter(const CString &strFilter,VIEW_TYPE view_Type, LPCTSTR lpStrName);
	VIEW_TYPE GetViewType();
	void SetFilter(const CString& strFilter, const CString& strSort);
	virtual ~CReportFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	CCurveBar				m_wndOutput;
// Generated message map functions
protected:
	//{{AFX_MSG(CReportFrame)
	afx_msg void OnEditCopy();
	afx_msg void OnEditCut();
	afx_msg void OnEditPaste();
	afx_msg void OnEditPasteSpecial();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnViewOutput();
	afx_msg void OnUpdateViewOutput(CCmdUI* pCmdUI);
	afx_msg void OnViewFilter();
    afx_msg void OnSetAsAutoreturnCredit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHILDFRM_H__B535331C_179F_4FD8_9547_9449B7BFA6A8__INCLUDED_)

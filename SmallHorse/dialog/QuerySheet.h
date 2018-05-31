#if !defined(AFX_QUERYSHEET_H__CDCC2F90_32ED_4698_9CFD_061C296005EA__INCLUDED_)
#define AFX_QUERYSHEET_H__CDCC2F90_32ED_4698_9CFD_061C296005EA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// QuerySheet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CQuerySheet
#include "namepage.h"
#include "datepage.h"
#include "typepage.h"
#include "CommentPage.h"


class CQuerySheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CQuerySheet)

// Construction
public:
	CNamePage	m_pgName;
	CTypePage	m_pgType;
	CDatePage	m_pgDate;
	CCommentPage	m_pgComment;
	CStringList	*m_pTypeList;
	CStringList *m_pNameList;
	COleDateTime		m_beginTime;
	COleDateTime		m_endTime;
	BOOL		m_bUseTime;
    CString     m_strCommentLike;
	
	
	CQuerySheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CQuerySheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQuerySheet)
	//}}AFX_VIRTUAL

// Implementation
public:
	static void AddStringToList(const CString&str,CListBox& list);
	virtual ~CQuerySheet();

	// Generated message map functions
protected:
	//{{AFX_MSG(CQuerySheet)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_QUERYSHEET_H__CDCC2F90_32ED_4698_9CFD_061C296005EA__INCLUDED_)

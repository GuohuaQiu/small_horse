// BankBookDoc.h : interface of the CBankBookDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_BANKBOOKDOC_H__223FC1AA_793C_11D5_96DA_EC47C6041904__INCLUDED_)
#define AFX_BANKBOOKDOC_H__223FC1AA_793C_11D5_96DA_EC47C6041904__INCLUDED_

#include "IDSet.h"	// Added by ClassView
#include "ListSet.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CBankBookDoc : public CDocument
{
protected: // create from serialization only
	CBankBookDoc();
	DECLARE_DYNCREATE(CBankBookDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBankBookDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	int m_displaytype;
	int m_begindays;
	int m_curbeginyear;
	COleDateTime GetCompareTime(COleDateTime timea,COleDateTime timeb,BOOL bMax=TRUE);
	virtual ~CBankBookDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CBankBookDoc)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BANKBOOKDOC_H__223FC1AA_793C_11D5_96DA_EC47C6041904__INCLUDED_)

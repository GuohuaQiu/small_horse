#if !defined(AFX_IMPORTSHEET_H__08799191_3B34_40FC_A902_F6EA8507313F__INCLUDED_)
#define AFX_IMPORTSHEET_H__08799191_3B34_40FC_A902_F6EA8507313F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ImportSheet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CImportSheet
#include "..\SmallHorse.h"
#include "fileselpage.h"
#include "ImportListPage.h"
#include "csvloader.h"
#include "ListSet.h"	// Added by ClassView


enum ImportType
{
	IMPORT_TYPE_RECORD,
	IMPORT_TYPE_SUBCONT
};
 
class CImportSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CImportSheet)

// Construction
public:
	int             m_nImportType;
	BOOL            m_bLoadOK;
	CString         m_strFile;
	CImportListPage m_ListPage;
	CFileSelPage    m_FilePage;
	CImportSheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
//	CImportSheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
    CImportSheet(LPCTSTR pszFullPath,const CString& strId,int nImportType = IMPORT_TYPE_RECORD);
	CImportSheet(const CString& strId);//for paste usage.
	CCSVLoader      m_loader;
	CString         m_strMainCount;
	BOOL            m_bFromFile;
// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImportSheet)
	protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	CSubCountSet *m_pSubCountSet;
	CListSet *m_pListSet;
	BOOL SetNewFile(const CString& strfile);
	virtual ~CImportSheet();

	// Generated message map functions
protected:
	//{{AFX_MSG(CImportSheet)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMPORTSHEET_H__08799191_3B34_40FC_A902_F6EA8507313F__INCLUDED_)

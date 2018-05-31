#if !defined(AFX_BOOKTYPESET_H__0CAB30D3_27E1_4EC3_BE9B_9DBAA796FDAA__INCLUDED_)
#define AFX_BOOKTYPESET_H__0CAB30D3_27E1_4EC3_BE9B_9DBAA796FDAA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BookTypeSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBookTypeSet recordset

class CBookTypeSet : public CRecordset
{
public:
	CString GetBookType(int nType);
	CBookTypeSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CBookTypeSet)

// Field/Param Data
	//{{AFX_FIELD(CBookTypeSet, CRecordset)
	int		m_ID;
	CString	m_Type;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBookTypeSet)
	public:
	virtual CString GetDefaultConnect();    // Default connection string
	virtual CString GetDefaultSQL();    // Default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);  // RFX support
	//}}AFX_VIRTUAL

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BOOKTYPESET_H__0CAB30D3_27E1_4EC3_BE9B_9DBAA796FDAA__INCLUDED_)

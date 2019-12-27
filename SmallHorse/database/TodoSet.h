#if !defined(AFX_TODOSET_H__223FC1B4_793C_11D5_96DA_EC47C6041904__INCLUDED_)
#define AFX_TODOSET_H__223FC1B4_793C_11D5_96DA_EC47C6041904__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// IDSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTodoSet recordset

class CTodoSet : public CRecordset
{
public:
	CTodoSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CTodoSet)

// Field/Param Data
	//{{AFX_FIELD(CTodoSet, CRecordset)
	int m_id;
	CString	m_body;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTodoSet)
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

public:
	BOOL Change_Pwd(const CString& strNewPwd);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TODOSET_H__223FC1B4_793C_11D5_96DA_EC47C6041904__INCLUDED_)

#if !defined(AFX_MANAGERSET_H__38F8AEE0_43E2_11D6_9B97_00004C0E2DC9__INCLUDED_)
#define AFX_MANAGERSET_H__38F8AEE0_43E2_11D6_9B97_00004C0E2DC9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ManagerSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CManagerSet recordset

class CManagerSet : public CRecordset
{
public:
	int Verify(CString strName,CString strPwd);
	CManagerSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CManagerSet)

// Field/Param Data
	//{{AFX_FIELD(CManagerSet, CRecordset)
	CString	m_pwd;
	CString	m_name;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CManagerSet)
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

#endif // !defined(AFX_MANAGERSET_H__38F8AEE0_43E2_11D6_9B97_00004C0E2DC9__INCLUDED_)

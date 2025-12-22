#if !defined(AFX_IDSET_H__223FC1B4_793C_11D5_96DA_EC47C6041904__INCLUDED_)
#define AFX_IDSET_H__223FC1B4_793C_11D5_96DA_EC47C6041904__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// IDSet.h : header file
#include "BaseRecordset.h"

/////////////////////////////////////////////////////////////////////////////
// CIDSet recordset

class CIDSet : public CBaseRecordset
{
public:
	void RevertExist();
	BOOL Modify_Book(CIDSet* pInData);
	BOOL LockEditStatus(const CString &strid);
	int GetEditStatus(const CString &strID);
	CString GetType();
	void SetAllDefaultType(int nType);
	int Find(const CString &strContain,const CString &strID);
	BOOL Find(const CString& strField, CString& strFind);
	BOOL MovetoCurID(const CString& strid);
	CIDSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CIDSet)

// Field/Param Data
	//{{AFX_FIELD(CIDSet, CRecordset)
	CString	m_ID;
	CString	m_bank;
	CString	m_name;
	CString	m_remain;
	CString	m_password;
	BYTE	m_bDefaultNetIncome;
	BOOL	m_bExist;
	int		m_nType;
	int		m_EditStatus;
	COleDateTime	m_InitDate;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIDSet)
    public:
    virtual CString GetTableName() const override { return _T("[Books]"); }
    virtual int GetFieldCount() const override { return 10; }
    virtual CString GetDefaultSQL();    // Default SQL for Recordset
    virtual void DoFieldExchange(CFieldExchange* pFX);  // RFX support
	//}}AFX_VIRTUAL
    // ¸¨Öúº¯Êý
    BOOL UpdateAndRefresh(BOOL bRefresh = TRUE);
    
    // ±ã½Ýº¯Êý
    BOOL FindByID(const CString& strID);

    
// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

public:
	void MakeDataCopy(CIDSet& idSet);
public:
	BOOL Change_Pwd(const CString& strNewPwd);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IDSET_H__223FC1B4_793C_11D5_96DA_EC47C6041904__INCLUDED_)

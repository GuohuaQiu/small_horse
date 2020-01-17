#if !defined(AFX_SUBCOUNTSETINONECOUNT_H__F1FE468A_F0BC_46CF__INCLUDED_)
#define AFX_SUBCOUNTSETINONECOUNT_H__F1FE468A_F0BC_46CF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SubCountSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSubCountInOneCountSet recordset

class CSubCountInOneCountSet : public CRecordset
{
public:
	CSubCountInOneCountSet(const CString& strId,BOOL bNameOnly = TRUE);
	DECLARE_DYNAMIC(CSubCountInOneCountSet)
	CString m_MainId;

// Field/Param Data
	//{{AFX_FIELD(CSubCountInOneCountSet, CRecordset)
	CString	m_Sub_Count_ID;
	CString	m_Remains;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSubCountInOneCountSet)
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

#endif // !defined(AFX_SUBCOUNTSETINONECOUNT_H__F1FE468A_F0BC_46CF__INCLUDED_)

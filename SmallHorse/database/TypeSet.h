#if !defined(AFX_TYPESET_H__F2B021D6_EC12_4DBF_ADC7_A37593B19854__INCLUDED_)
#define AFX_TYPESET_H__F2B021D6_EC12_4DBF_ADC7_A37593B19854__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TypeSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTypeSet recordset

class CTypeSet : public CRecordset
{
public:
	BYTE GetTypeIndex(const CString& strType);
	CTypeSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CTypeSet)

// Field/Param Data
	//{{AFX_FIELD(CTypeSet, CRecordset)
	BYTE	m_typeid;
	CString	m_strType;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTypeSet)
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

#endif // !defined(AFX_TYPESET_H__F2B021D6_EC12_4DBF_ADC7_A37593B19854__INCLUDED_)

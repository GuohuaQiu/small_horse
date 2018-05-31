#if !defined(AFX_INTERESTSET_H__607AF854_7875_4775_BA37_0FD8B6C59F5A__INCLUDED_)
#define AFX_INTERESTSET_H__607AF854_7875_4775_BA37_0FD8B6C59F5A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RateSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRateSet recordset

class CRateSet : public CRecordset
{
public:
	BOOL HasRecord(const COleDateTime& date);
	void AddRate(const COleDateTime& fromDate,float* rates);
	float GetDepositRate(const COleDateTime& fromDate, COleDateTime& toDate);
	void TRACE_ALL();
	float* GetRatePtr(int nMonth);
	float GetRate(const COleDateTime &date, int nMonth);
	CRateSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CRateSet)

// Field/Param Data
	//{{AFX_FIELD(CRateSet, CRecordset)
	COleDateTime	m_FromDate;
	float	m_Deposit;
	float	m_Fix3Month;
	float	m_Fix6Month;
	float	m_Fix1Year;
	float	m_Fix2Year;
	float	m_Fix3Year;
	float	m_Fix5Year;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRateSet)
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

#endif // !defined(AFX_INTERESTSET_H__607AF854_7875_4775_BA37_0FD8B6C59F5A__INCLUDED_)

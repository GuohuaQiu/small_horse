#if !defined(AFX_CREDITPAYSET_H__17A367A1_CFA1_436A_9E7F_8C54FCDCBA67__INCLUDED_)
#define AFX_CREDITPAYSET_H__17A367A1_CFA1_436A_9E7F_8C54FCDCBA67__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CreditPaySet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCreditPaySet recordset

class CCreditPaySet : public CRecordset
{
public:
	BOOL GetPeriodStart(const CString& strID,int inY,int inM,int inD,int &outY,int &outM,int &outD);
	
	static void AddMonth(int& year,int& month, int ms);
	static int GetSpan(int aYear, int aMonth, int bYear, int bMonth);
	void trace();
	BOOL GetPayInfo(const CString& strID,int nYear, int nMonth, COleDateTime& dayBegin, COleDateTime& dayEnd, COleDateTime& dayPay);
	CCreditPaySet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CCreditPaySet)

// Field/Param Data
	//{{AFX_FIELD(CCreditPaySet, CRecordset)
	CString	m_BookID;
	int		m_StartYear;
	BYTE	m_StartMonth;
	BYTE	m_StatementDate;
	BYTE	m_PaymentDueDate;
	CString	m_Comment;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCreditPaySet)
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

#endif // !defined(AFX_CREDITPAYSET_H__17A367A1_CFA1_436A_9E7F_8C54FCDCBA67__INCLUDED_)

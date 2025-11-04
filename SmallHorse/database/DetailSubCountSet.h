#if !defined(AFX_DETAIL_SUBCOUNT_H__F1FE468A_F0BC_46CF__INCLUDED_)
#define AFX_DETAIL_SUBCOUNT_H__F1FE468A_F0BC_46CF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SubCountSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDetailSubCountSet recordset
//1. LISTSET_ID，作为键值对应LISTSET中的一项
//2. 存期，字符串型，根据字符串转数字使用，来推算结束日期
//3. 注释
//4. 利率，按年化显示，比如年化5 就是5.0
//5. 余额，从LISTSET中提取
//5. 银行，从LISTSET中间接提取
//8. 姓名，从LISTSET中间接提取
//6. 主账户 从LISTSET中提取
//7. 子账户名 从LISTSET中提取


class CDetailSubCountSet : public CRecordset
{
public:
	CDetailSubCountSet(const CString& strFilter);
	DECLARE_DYNAMIC(CDetailSubCountSet)


// Field/Param Data
	//{{AFX_FIELD(CDetailSubCountSet, CRecordset)
    CString m_strBank;
    CString m_strOwner;
    CString m_strBookId;
    CString m_strRecordId;
    float m_fValue;
    COleDateTime m_dateStart;
    COleDateTime m_dateEnd;
    float m_fRate;
    CString m_strTimeSpan;
    CString m_strComment;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDetailSubCountSet)
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

#endif // !defined(AFX_DETAIL_SUBCOUNT_H__F1FE468A_F0BC_46CF__INCLUDED_)

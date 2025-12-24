#if !defined(AFX_SUBCOUNTSET_H__F1FE468A_F0BC_46CF_B2D7_ABE08B4C390D__INCLUDED_)
#define AFX_SUBCOUNTSET_H__F1FE468A_F0BC_46CF_B2D7_ABE08B4C390D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SubCountSet.h : header file
//

#include <vector>

// 定义子账户导入数据的中间结构
struct SUBCOUNT_IMPORT_ITEM
{
    CString strMainCount;
    CString strSubCountID;
    
    // 数据值
    double fBeginValue;
    COleDateTime dtStartDate;
    COleDateTime dtEndDate;
    float fYearRate;
    long nTimeSpan;
    CString strComment;

    // 有效性标志 (对应原代码中的 nType[j] >= 0 判断)
    BOOL bHasBeginValue;
    BOOL bHasStartDate;
    BOOL bHasEndDate;
    BOOL bHasYearRate;
    BOOL bHasTimeSpan;
    BOOL bHasComment;

    SUBCOUNT_IMPORT_ITEM()
    {
        fBeginValue = 0.0;
        fYearRate = 0.0f;
        nTimeSpan = 0;
        bHasBeginValue = FALSE;
        bHasStartDate = FALSE;
        bHasEndDate = FALSE;
        bHasYearRate = FALSE;
        bHasTimeSpan = FALSE;
        bHasComment = FALSE;
    }
};

/////////////////////////////////////////////////////////////////////////////
// CSubCountSet recordset

class CSubCountSet : public CRecordset
{
public:
    BOOL Modify(CSubCountSet* pInData);
    void MakeDataCopy(CSubCountSet& subSet);
    void SetNoExist();
    void SetAllExist();
    void GetTipString(CString& strTip);
    void AddFirstRecordforSubCount(const CString& strMainCount);
    BOOL Find(const CString& strMainCount,const CString& strSubCount);
    
    // 修改处：使用结构体向量作为参数
    BOOL AddItems(const std::vector<SUBCOUNT_IMPORT_ITEM>& items);
    // 保留旧接口声明如果需要，或者直接删除
    // BOOL AddItems(CListCtrl *pctrl,int nType[],CString strMainCount,int pATC[],int column_count);
    
    void RequeryCount(const CString& strCount);
    CSubCountSet(CDatabase* pDatabase = NULL);
    DECLARE_DYNAMIC(CSubCountSet)

// Field/Param Data
	//{{AFX_FIELD(CSubCountSet, CRecordset)
	long	m_Index;
	CString	m_Count_ID;
	CString	m_Sub_Count_ID;
	COleDateTime	m_Start_Date;
	COleDateTime	m_End_Date;
	float	m_Year_Rate;
	CString	m_Comment;
	long	m_Time_Span;
	float	m_BeginValue;
	BOOL	m_bExist;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSubCountSet)
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

#endif // !defined(AFX_SUBCOUNTSET_H__F1FE468A_F0BC_46CF_B2D7_ABE08B4C390D__INCLUDED_)

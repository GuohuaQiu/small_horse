#if !defined(AFX_LISTSET_H__56AE3DC3_794D_11D5_96DA_CB0138A24207__INCLUDED_)
#define AFX_LISTSET_H__56AE3DC3_794D_11D5_96DA_CB0138A24207__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ListSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CListSet recordset

#include "database_setup.h"
#include "recordlist.h"
#include "BaseRecordSet.h"
//#include "ListCompare.h"	// Added by ClassView
class CSmartDate;


class CListSet : public CBaseRecordset
{
protected:
    CCriticalSection m_LockModify;
    BOOL m_bSetUpdateTime;
public:
    CListSet(CDatabase* pDatabase = NULL);
    DECLARE_DYNAMIC(CListSet)

    virtual CString GetDefaultSQL();
    virtual CString GetTableName() const override { return _T("[Items]"); }
    virtual int GetFieldCount() const override { return 11; }
    BOOL EnsureOpen();
    BOOL FindByID(int nId);
    void Move(long nRows, WORD wFetchType);
	BOOL Modify_Transfer(const CString& strComment);
#if 0
	BOOL Modify_Type(BYTE type);
#endif
	BOOL Modify_Record(CListSet* inData);
	BOOL Edit_CalSum(float *fSum);
	static BOOL New_Item(CListSet* pInData);
	BOOL GetLastDate(CSmartDate &date);
		
	BOOL GetFirstDate(CSmartDate &date);
	BOOL ModifyRecord(Record* precord);
	BOOL NewRecord(Record* precord);
	void GetGenerationInfo(LPGEN_INFO pinfo,const CString &strSubId);
	BOOL LoadAll(CRecordList* pList);
	LPRECORD NewCopy();
	void GetGenerationInfo(LPGEN_INFO pinfo);
	void SetUpdateTime(BOOL bSet);
	void OpenOneRecord(int nID);
	int RequerySubCount(const CString& strMainCount,const CString& strSubCount);
	BOOL MoveToID(int nID,LPCTSTR lpFilter=NULL);
	BOOL Find(const COleDateTime& time,float fRecord,const CString& strSubCount);
	BOOL IsOnlyOneBook();
	BOOL GetCurrentBookId(CString &strID);
	static BOOL AddItems(CListCtrl* pctrl,int nType[],const CString& strId,int pATC[],int column_count);
// 	void SetNetIncome(BYTE bType);
	CString GetDate();
	CString GetArray();
	CString GetSum();
	CString GetAddorSub();
	CString GetRemain(CString strID);
	void SetSumValue(float f);
	void SetAddOrSubValue(float f);
	float GetAddorSubValue();
	float GetSumValue(BOOL bInt=TRUE);


// Field/Param Data
	//{{AFX_FIELD(CListSet, CRecordset)
	COleDateTime	m_day;
	CString	m_ID;
	CString	m_sum;
	CString	m_addorsub;
	CString	m_remain;
	int		m_arraynumber;
	BYTE	m_bType;
	CString	m_strSubCount;
    CString m_strSite;
	COleDateTime	m_TimeAdd;
	COleDateTime	m_TimeModify;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListSet)
	public:
	virtual CString GetDefaultConnect();    // Default connection string
	virtual void DoFieldExchange(CFieldExchange* pFX);  // RFX support
	virtual BOOL UpdateRequery();

	//}}AFX_VIRTUAL

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
    virtual void AddNew();      // add new record at the end
	virtual void Edit();        // start editing

public:
	void Trace(void);
	int Modify_Type_ByComment(int type,const CString& strNoHas, const CString& strHas,const CDWordArray& dbArray,int count);
	int Modify_Site_ByComment(const CString&strSite,const CString& strNoHas, const CString& strHas,const CDWordArray& dbArray,int count);
	int Replace_Comment(const CString& strOldString, const CString& strNewString,const CDWordArray& dbArray,int count);
	int MoveRecordsTo(const CString& Count, const CString& SubCount,const CDWordArray& dbArray,int count);
	int StartEdit();
	int SubmitEdit();
	int EndEdit();
	int SubmitNew();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTSET_H__56AE3DC3_794D_11D5_96DA_CB0138A24207__INCLUDED_)

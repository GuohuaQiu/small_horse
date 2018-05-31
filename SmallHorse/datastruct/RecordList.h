// RecordList.h: interface for the CRecordList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RECORDLIST_H__66FFADF0_8C3B_4BFF_A9BF_2CFD2249B70B__INCLUDED_)
#define AFX_RECORDLIST_H__66FFADF0_8C3B_4BFF_A9BF_2CFD2249B70B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#define FIELD_ID        0X0001
#define FIELD_SUBID     0X0002
#define FIELD_DAY       0X0004
#define FIELD_VALUE     0X0008
#define FIELD_TYPE      0X0010
#define FIELD_COMMENT   0X0020
#define FIELD_SITE      0X0040

#define FIELD_ALIKE     0X000F




class Record  {
public:
	CString	m_ID;
	CString	m_strSubCount;
	COleDateTime	m_day;
	CString	m_sum;
	CString	m_addorsub;
	int		m_arraynumber;
	BYTE	m_bType;
	CString	m_remain;
    CString m_strSite;
	COleDateTime	m_TimeAdd;
	COleDateTime	m_TimeModify;
public:
	int CompareDay(Record* pSrcRecord);
	DWORD CompareNotAlikeField(const Record& sSrc);
	void Output(const CString& strInfo);
    bool operator ==(const Record &rSrc) const;
    bool IsAlike(const Record &rSrc) const;
	void CopyRecord(Record* pSrcRecord);
};
typedef Record *LPRECORD;



#define ITEM_NEW  0x01
#define ITEM_EXIST 0X00

#define ITEM_ORIGINAL 0X00
#define ITEM_MODIFIED 0X10

class Alike2
{
    friend class CCompareFrame;
public:
	void SetBStateExist();
	void SetAStateExist();
	BOOL IsModifiedB();
	BOOL IsModifiedA();
	BOOL IsNewA();
	BOOL IsNewB();
	void MergeFields(DWORD dwFields);
	void CopyB2A();
	void CopyA2B();
    int     m_editor;
    Alike2(Record * pRecordA,Record * pRecordB);
    virtual ~Alike2();
    
	void Output();
	LPRECORD FindSame(LPRECORD pSrcRecord);
    int      m_editStateA;
    int      m_editStateB;
    LPRECORD m_pRecordA;
    LPRECORD m_pRecordB;
    DWORD    m_dwSameFields;
};

typedef CTypedPtrList<CPtrList, LPRECORD> CTypedRecordList;
typedef CTypedPtrList<CPtrList, Alike2*> CTypedJoinedList;

typedef void (*CB_FUNC_HANDLE_ITEM)(DWORD dwThis,void* pitem) ;

class CRecordList : public CTypedRecordList  
{
public:
	void HandleAllItem(CB_FUNC_HANDLE_ITEM pFun,DWORD pThis);
	void DeleteAll();
	void Output(const CString& strInfo);
	CRecordList();
	virtual ~CRecordList();

};

class CJoinedList : public CTypedJoinedList  
{
public:
	void HandleAllItem(CB_FUNC_HANDLE_ITEM pFun, DWORD pThis);
	void DeleteAll();
    void Output(const CString& strInfo);
    CJoinedList();
    virtual ~CJoinedList();
    
};

#endif // !defined(AFX_RECORDLIST_H__66FFADF0_8C3B_4BFF_A9BF_2CFD2249B70B__INCLUDED_)

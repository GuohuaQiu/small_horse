// QueryHistoryList.h: interface for the CQueryHistoryList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_QUERYHISTORYLIST_H__D7059D50_4C59_4AC2_9C14_CB29C05B8792__INCLUDED_)
#define AFX_QUERYHISTORYLIST_H__D7059D50_4C59_4AC2_9C14_CB29C05B8792__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CQueryItem 
{
public:
	CString strFilter;
	CString strName;
};

typedef CTypedPtrList<CPtrList,CQueryItem*> CQueryItemList__;

class CQueryItemList : public CQueryItemList__ 
{
public:
	CQueryItem* GetItem(const CString &strFilter, const CString &strName);
	CQueryItem* Get(int nIndex);
	void AddNewQuery(const CString& strFilter, const CString& strName);
	int GetNumber();
	BOOL Load();
	BOOL Save();
	CQueryItemList();
	virtual ~CQueryItemList();
};



#endif // !defined(AFX_QUERYHISTORYLIST_H__D7059D50_4C59_4AC2_9C14_CB29C05B8792__INCLUDED_)

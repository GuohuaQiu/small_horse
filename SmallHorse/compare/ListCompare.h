// ListCompare.h: interface for the CListCompare class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LISTCOMPARE_H__D667C488_69CA_4211_984A_9DD6D7C43DD2__INCLUDED_)
#define AFX_LISTCOMPARE_H__D667C488_69CA_4211_984A_9DD6D7C43DD2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//第一步，先能比出来。

#include "RecordList.h"

class CListCompare
{
    friend class CCompareFrame;
private:
    CRecordList m_lstA;
    CRecordList m_lstB;
protected:
public:
    CJoinedList m_lstJoin;
	void SaveAlltoA();
	void SaveAlltoB();
	void OutputGeneralInformation();
	void Output();
	BOOL Merge(Alike2 *pAlike);
	BOOL Join(LPRECORD* pRecordA,LPRECORD* pRecordB);
	BOOL Split(Alike2* pAlike);
	BOOL FindAlikeRecords();
	BOOL ClearAllSameRecords();
	void Load2Set();
	CListCompare();
	virtual ~CListCompare();

};

#endif // !defined(AFX_LISTCOMPARE_H__D667C488_69CA_4211_984A_9DD6D7C43DD2__INCLUDED_)

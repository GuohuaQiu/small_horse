// QueryHistoryList.cpp: implementation of the CQueryHistoryList class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "..\SmallHorse.h"
#include "QueryHistoryList.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////



CQueryItemList::CQueryItemList()
{
}

CQueryItemList::~CQueryItemList()
{
	POSITION pos = GetHeadPosition();
	while (pos)
	{
		delete GetNext(pos);
	}
}


BOOL CQueryItemList::Save()
{
	POSITION pos = GetHeadPosition();
	int nCount = 0;
	CString strSection       = "HISTORY";
	CString strStringItem    ;
	theApp.WriteProfileInt(strSection, "Count", GetCount());
	while(pos)
	{
		CQueryItem* pItem = GetNext(pos);
		strStringItem.Format("%.2d",nCount);
		theApp.WriteProfileString(strSection, strStringItem, pItem->strFilter);
		strStringItem += "Name";
		theApp.WriteProfileString(strSection, strStringItem, pItem->strName);
		nCount++;
	}
	return TRUE;
}

BOOL CQueryItemList::Load()
{
	RemoveAll();
	CString strSection       = "HISTORY";
	CString strStringItem    ;
	int nTotalCount = theApp.GetProfileInt(strSection, "Count", 0);
	for(int nCount = 0; nCount < nTotalCount; nCount++)
	{
		CQueryItem* pItem = new CQueryItem;
		strStringItem.Format("%.2d",nCount);
		pItem->strFilter = theApp.GetProfileString(strSection, strStringItem);
		strStringItem += "Name";
		pItem->strName = theApp.GetProfileString(strSection, strStringItem);
		AddTail(pItem);
	}
	return TRUE;
}

int CQueryItemList::GetNumber()
{
	return 0;
}

void CQueryItemList::AddNewQuery(const CString &strFilter, const CString &strName)
{
	CQueryItem* pItem = GetItem(strFilter,strName);
	if(pItem != NULL)
	{
		return;
	}
	pItem = new CQueryItem;
	pItem->strFilter = strFilter;
	pItem->strName = strName;
	AddHead(pItem);
}


/*******************************************
    Function Name : 
    author        : Qiu Guohua
    Date          : 2009-4-20 21:40:06
    Description   : 
    Return type  : 
    Argument      : 
********************************************/
CQueryItem* CQueryItemList::Get(int nIndex)
{
	CQueryItem *pItem = NULL;
	POSITION pos = FindIndex( nIndex );
	if(pos)
	{
		pItem = GetAt(pos);
	}
	return pItem;
}


/*******************************************
    Function Name : 
    author        : Qiu Guohua
    Date          : 2009-5-5 20:33:28
    Description   : 
    Return type  : 
    Argument      : 
********************************************/
CQueryItem* CQueryItemList::GetItem(const CString &strFilter, const CString &strName)
{
	POSITION pos = GetHeadPosition();
	CQueryItem* pItem = NULL;
	while (pos)
	{
		pItem = GetNext(pos);
		if(strFilter == pItem->strFilter &&
			strName == pItem->strName)
		{
			return pItem;
		}
	}
	return NULL;

}

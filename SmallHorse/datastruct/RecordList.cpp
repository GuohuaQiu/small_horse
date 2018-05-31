// RecordList.cpp: implementation of the CRecordList class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RecordList.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

bool Record::operator ==(const Record &rSrc) const
{
    if(m_ID != rSrc.m_ID)
    {
        return false;
    }
    if(m_day.GetYear() != rSrc.m_day.GetYear())
    {
        return false;
    }
    if(m_day.GetMonth() != rSrc.m_day.GetMonth())
    {
        return false;
    }
    if(m_day.GetDay() != rSrc.m_day.GetDay())
    {
        return false;
    }

    
    if(m_addorsub != rSrc.m_addorsub)
    {
        return false;
    }
    if(m_remain != rSrc.m_remain)
    {
        return false;
    }
    if(m_bType != rSrc.m_bType)
    {
        return false;
    }
    if(m_strSubCount != rSrc.m_strSubCount)
    {
        return false;
    }
    if(m_strSite != rSrc.m_strSite)
    {
        return false;
    }
    return true;

}

bool Record::IsAlike(const Record &rSrc) const
{
    if(m_day.GetYear() != rSrc.m_day.GetYear())
    {
        return false;
    }
    if(m_day.GetMonth() != rSrc.m_day.GetMonth())
    {
        return false;
    }
    if(m_day.GetDay() != rSrc.m_day.GetDay())
    {
        return false;
    }
    
    if(m_ID != rSrc.m_ID)
    {
        return false;
    }
    if(m_strSubCount != rSrc.m_strSubCount)
    {
        return false;
    }
    
    
    if(m_addorsub != rSrc.m_addorsub)
    {
        return false;
    }

    return true;
}


CRecordList::CRecordList()
{

}

CRecordList::~CRecordList()
{
    DeleteAll();

}
CJoinedList::CJoinedList()
{
    
}

CJoinedList::~CJoinedList()
{
    DeleteAll();
    
}

LPRECORD Alike2::FindSame(LPRECORD pSrcRecord)
{
    return NULL;
}

#define TRACE_TIME(reason,time) TRACE("%s:%s   \t",reason,time.Format("%Y-%m-%d"));

/*******************************************
    Function Name : 
    author        : Qiu Guohua
    Date          : 2010-12-25 20:33:27
    Description   : 
    Return type   : 
    Argument      : 
********************************************/
void Record::Output(const CString &strInfo)
{
    TRACE("\n%s \t",strInfo);
    TRACE_TIME("Day\t",m_day);
    TRACE("%s \t",	m_ID);
    TRACE("%s \t",	m_addorsub);
    TRACE("%s \t",	m_sum);
    TRACE("%s \t",	m_remain);
    TRACE("%d \t",	m_arraynumber);
    TRACE("%d \t",	m_bType);
    TRACE("%s \t",	m_strSubCount);
    TRACE("%s \t", m_strSite);
    TRACE_TIME("DayAdd \t",m_TimeAdd);
    TRACE_TIME("Day\t",m_TimeModify);
}


/*******************************************
    Function Name : 
    author        : Qiu Guohua
    Date          : 2010-12-25 20:41:57
    Description   : 
    Return type   : 
    Argument      : 
********************************************/
void CRecordList::Output(const CString& strInfo)
{
    TRACE("\n-----------------%s ------------------------------------------------", strInfo);
    POSITION pos = GetHeadPosition();
    LPRECORD pRecord = NULL;
    while(pos)
    {
        pRecord = GetNext(pos);
        pRecord->Output("");
    }
}

void CJoinedList::Output(const CString& strInfo)
{
    TRACE("\n-----------------%s ------------------------------------------------", strInfo);
    POSITION pos = GetHeadPosition();
    Alike2* pAlike = NULL;
    while(pos)
    {
        pAlike = GetNext(pos);
        pAlike->Output();
    }
}

void Alike2::Output()
{
    TRACE("\n----------------------------------------------------------------");
    m_pRecordA->Output("");
    m_pRecordB->Output("");
    TRACE("\n----------------------------------------------------------------");
}

void CRecordList::DeleteAll()
{
    POSITION pos = GetHeadPosition();
    while(pos)
    {
        delete GetNext(pos);
    }
    RemoveAll();
}

void CJoinedList::DeleteAll()
{
    POSITION pos = GetHeadPosition();
    while(pos)
    {
        delete GetNext(pos);
    }
    RemoveAll();
}

Alike2::Alike2(Record * pRecordA,Record * pRecordB)
{
    m_pRecordA=pRecordA;
    m_pRecordB=pRecordB;
    if(pRecordA&&pRecordB)
    {
        m_dwSameFields = FIELD_ALIKE;
        m_dwSameFields |= pRecordA->CompareNotAlikeField(*pRecordB);
    }
    else
    {
        m_dwSameFields = 0;
    }
    m_editStateA = ITEM_EXIST;
    m_editStateB = ITEM_EXIST;

}

Alike2:: ~Alike2()
{
    if(m_pRecordA)
    {
        delete m_pRecordA;
    }
    if(m_pRecordB)
    {
        delete m_pRecordB;
    }
}


/*******************************************
    Function Name :	 
    Create by     :	  Qiu Simon
    Input         :   
    Output        :   
    Description   :   
    Date          :   1/12/2011 3:13:01 PM
********************************************/
void CRecordList::HandleAllItem(CB_FUNC_HANDLE_ITEM pFun, DWORD pThis)
{
    POSITION pos = GetHeadPosition();
    LPRECORD pRecord = NULL;
    while(pos)
    {
        pRecord = GetNext(pos);
        (*pFun)(pThis,pRecord);
    }
}

void CJoinedList::HandleAllItem(CB_FUNC_HANDLE_ITEM pFun, DWORD pThis)
{
    POSITION pos = GetHeadPosition();
    Alike2* pAlike = NULL;
    while(pos)
    {
        pAlike = GetNext(pos);
        (*pFun)(pThis,pAlike);
    }
}


/*******************************************
    Function Name :	 
    Create by     :	  Qiu Simon
    Input         :   
    Output        :   
    Description   :   
    Date          :   1/13/2011 2:18:30 PM
********************************************/
DWORD Record::CompareNotAlikeField(const Record &sSrc)
{
    DWORD dwFields = 0;
    if(m_bType == sSrc.m_bType)
    {
        dwFields |= FIELD_TYPE;
    }
    if(m_remain == sSrc.m_remain)
    {
        dwFields |= FIELD_COMMENT;
    }
    if(m_strSite == sSrc.m_strSite)
    {
        dwFields |= FIELD_SITE;
    }
    return dwFields;
}

#define ITEM_NEW  0x01
#define ITEM_EXIST 0X00

#define ITEM_ORIGINAL 0X00
#define ITEM_MODIFIED 0X10

//2017-07-22 23:00 added
void Record::CopyRecord(Record* pSrcRecord)
{
	int arraynumber = m_arraynumber;
	
	m_TimeModify = COleDateTime::GetCurrentTime();
	*this = *pSrcRecord;
	TRACE("%d <<< %d\n", arraynumber, m_arraynumber);
	m_arraynumber=arraynumber;
}

/*******************************************
    Function Name :	 
    Create by     :	  Qiu Simon
    Input         :   
    Output        :   
    Description   :   
    Date          :   1/13/2011 4:59:42 PM
********************************************/
void Alike2::CopyB2A()
{
    ASSERT(m_pRecordB);
    if(m_pRecordA)
    {
		m_pRecordA->CopyRecord(m_pRecordB);
        //*m_pRecordA = *m_pRecordB;
        m_editStateA |= ITEM_MODIFIED;
    }
    else
    {
        m_pRecordA = new Record;
        *m_pRecordA = *m_pRecordB;
        m_editStateA |= ITEM_NEW;
    }
}


/*******************************************
    Function Name :	 
    Create by     :	  Qiu Simon
    Input         :   
    Output        :   
    Description   :   
    Date          :   9/15/2011 4:44:05 PM
********************************************/
void Alike2::CopyA2B()
{
    ASSERT(m_pRecordA);
    if(m_pRecordB)
    {
		m_pRecordB->CopyRecord(m_pRecordA);
        //*m_pRecordB = *m_pRecordA;
        m_editStateB |= ITEM_MODIFIED;
    }
    else
    {
        m_pRecordB = new Record;
        *m_pRecordB = *m_pRecordA;
        m_editStateB |= ITEM_NEW;
    }
}


/*******************************************
    Function Name :	 
    Create by     :	  Qiu Simon
    Input         :   
    Output        :   
    Description   :   
    Date          :   1/13/2011 5:16:20 PM
********************************************/
void Alike2::MergeFields(DWORD dwFields)
{
    ASSERT(m_pRecordA);
    if(dwFields&FIELD_TYPE)
    {
        m_pRecordA->m_bType = m_pRecordB->m_bType;
    }
    if(dwFields&FIELD_COMMENT)
    {
        m_pRecordA->m_remain = m_pRecordB->m_remain;
    }
    if(dwFields&FIELD_SITE)
    {
        m_pRecordA->m_strSite = m_pRecordB->m_strSite;
    }
}

BOOL Alike2::IsNewB()
{
	return m_editStateB&ITEM_NEW;
}

BOOL Alike2::IsNewA()
{
	return m_editStateA&ITEM_NEW;
}

BOOL Alike2::IsModifiedA()
{
	return m_editStateA&ITEM_MODIFIED;
}

BOOL Alike2::IsModifiedB()
{
	return m_editStateB&ITEM_MODIFIED;
}

void Alike2::SetAStateExist()
{
	m_editStateA = ITEM_ORIGINAL;
}

void Alike2::SetBStateExist()
{
	m_editStateB = ITEM_ORIGINAL;

}


/*******************************************
    Function Name : 
    author        : Qiu Guohua
    Date          : 2017/7/23 8:03:21
    Description   : 
    Return type   : 
    Argument      : 
********************************************/
int Record::CompareDay(LPRECORD pRecord)
{
    if(m_day.GetYear() < pRecord->m_day.GetYear())
    {
        return -1;
    }
	if (m_day.GetYear() > pRecord->m_day.GetYear()) 
	{
		return 1;
	}
	
    if(m_day.GetMonth() < pRecord->m_day.GetMonth())
    {
        return -1;
    }
    if(m_day.GetMonth() > pRecord->m_day.GetMonth())
    {
        return 1;
    }
    if(m_day.GetDay() < pRecord->m_day.GetDay())
    {
        return -1;
    }
    if(m_day.GetDay() > pRecord->m_day.GetDay())
    {
        return 1;
    }
	return 0;
}

// ListCompare.cpp: implementation of the CListCompare class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "..\SmallHorse.h"
#include "ListCompare.h"
#include "CmpListA.h"
#include "CmpListB.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CListCompare::CListCompare()
{

}

CListCompare::~CListCompare()
{
    POSITION pos = m_lstA.GetHeadPosition();
    while(pos)
    {
        delete m_lstA.GetNext(pos);
    }
	pos = m_lstB.GetHeadPosition();
    while(pos)
    {
        delete m_lstB.GetNext(pos);
    }
    m_lstA.RemoveAll();
    m_lstB.RemoveAll();
	pos = m_lstJoin.GetHeadPosition();
    while(pos)
    {
        delete m_lstJoin.GetNext(pos);
    }
	
}

void CListCompare::Load2Set()
{
    CCmpListA listsetA;
    CCmpListB listsetB;
    listsetB.Open();
    TRACE("Right: loaded %d",listsetB.GetRecordCount());
    listsetB.LoadAll(&m_lstB);
    TRACE("Right: loaded %d",m_lstB.GetCount());
    
    listsetB.Close();
    
    listsetA.Open();
    TRACE("Left: loaded %d",listsetA.GetRecordCount());
    listsetA.LoadAll(&m_lstA);
    TRACE("Left: loaded %d",m_lstA.GetCount());
    listsetA.Close();

}


/*******************************************
    Function Name : 
    author        : Qiu Guohua
    Date          : 2010-12-25 20:18:44
    Description   : 
    Return type   : 
    Argument      : 
********************************************/
BOOL CListCompare::ClearAllSameRecords()
{
    CRecordList listTmp;
    POSITION pos = m_lstA.GetHeadPosition();
    POSITION pospre;
    LPRECORD pRecord = NULL;
    while(pos)
    {
        pospre = pos;
        pRecord = m_lstA.GetNext(pos);
        BOOL b = FALSE;
        {
            POSITION posB = m_lstB.GetHeadPosition();
            POSITION pospreB;
            while(posB)
            {
                pospreB = posB;
                LPRECORD pRecordB = m_lstB.GetNext(posB);
                if(*pRecord == *pRecordB)
                {
                    m_lstB.RemoveAt(pospreB);
                    delete pRecordB;
                    b = TRUE;
                    break;
                }
            }
        }
        m_lstA.RemoveAt(pospre);
        if(b)
        {
            delete pRecord;
        }
        else
        {
            listTmp.AddTail(pRecord);
        }
    }
    ASSERT(m_lstA.GetCount() == 0);
    pos = listTmp.GetHeadPosition();
    while(pos)
    {
        pRecord = listTmp.GetNext(pos);
        m_lstA.AddTail(pRecord);
    }
    listTmp.RemoveAll();
    return FALSE;
}


/*******************************************
    Function Name : 
    author        : Qiu Guohua
    Date          : 2010-12-25 20:29:40
    Description   : 
    Return type   : 
    Argument      : 
********************************************/
BOOL CListCompare::FindAlikeRecords()
{
    m_lstJoin.RemoveAll();
    POSITION pos = m_lstA.GetHeadPosition();
    POSITION pospre;
    LPRECORD pRecord = NULL;
   /* while(pos)
    {
        pospre = pos;
        pRecord = m_lstA.GetNext(pos);
        BOOL b = FALSE;
        {
            POSITION posB = m_lstB.GetHeadPosition();
            POSITION pospreB;
            while(posB)
            {
                pospreB = posB;
                LPRECORD pRecordB = m_lstB.GetNext(posB);
				//As time order list, no possible to make alike!
				int r = pRecord->CompareDay(pRecordB);
				if(r == -1)
				{
					//continue get next A.
					break;
				}
				if(r == 1)
				{
                    m_lstB.RemoveAt(pospreB);
                    continue;
				}

                if(pRecord->IsAlike(*pRecordB))
                {
                    Alike2* pAlike = new Alike2(pRecord,pRecordB);
                    m_lstJoin.AddTail(pAlike);
                    m_lstB.RemoveAt(pospreB);
                    b = TRUE;
                    break;
                }

            }
        }
        if(!b)
        {
             Alike2* pAlike = new Alike2(pRecord,NULL);
             m_lstJoin.AddTail(pAlike);
        }
        m_lstA.RemoveAt(pospre);
    }
*/
    //copy all from listb to joinlist.
    while(pos)
    {
        pospre = pos;
        pRecord = m_lstA.GetNext(pos);
        BOOL b = FALSE;
        {
            POSITION posB = m_lstB.GetHeadPosition();
            POSITION pospreB;
            while(posB)
            {
                pospreB = posB;
                LPRECORD pRecordB = m_lstB.GetNext(posB);
				int r = pRecord->CompareDay(pRecordB);
				//A<B As time order list, no possible to make alike!
				if(r == -1)
				{
					Alike2* pAlike = new Alike2(pRecord,NULL);
					m_lstJoin.AddTail(pAlike);
					m_lstA.RemoveAt(pospre);
					//continue get next A.
					break;
				}
				//A>B
				if(r == 1)
				{
					Alike2* pAlike = new Alike2(NULL,pRecordB);
					m_lstJoin.AddTail(pAlike);
                    m_lstB.RemoveAt(pospreB);
                    continue;
				}
                //A==B
                if(pRecord->IsAlike(*pRecordB))
                {
                    Alike2* pAlike = new Alike2(pRecord,pRecordB);
                    m_lstJoin.AddTail(pAlike);
					m_lstA.RemoveAt(pospre);
                    m_lstB.RemoveAt(pospreB);

                    b = TRUE;
                    break;
                }
            }
        }
    }
    POSITION posA = m_lstA.GetHeadPosition();
    while(posA)
    {
        LPRECORD pRecordA = m_lstA.GetNext(posA);
        Alike2* pAlike = new Alike2(pRecordA,NULL);
        m_lstJoin.AddTail(pAlike);
    }
    m_lstA.RemoveAll();
	
    POSITION posB = m_lstB.GetHeadPosition();
    while(posB)
    {
        LPRECORD pRecordB = m_lstB.GetNext(posB);
        Alike2* pAlike = new Alike2(NULL,pRecordB);
        m_lstJoin.AddTail(pAlike);
    }
    m_lstB.RemoveAll();
    return TRUE;
}

BOOL CListCompare::Split(Alike2 *pAlike)
{
    return FALSE;
}

BOOL CListCompare::Join(LPRECORD *pRecordA, LPRECORD *pRecordB)
{
    return FALSE;

}

BOOL CListCompare::Merge(Alike2 *pAlike)
{
    return FALSE;

}


/*******************************************
    Function Name : 
    author        : Qiu Guohua
    Date          : 2010-12-25 20:45:20
    Description   : 
    Return type   : 
    Argument      : 
********************************************/
void CListCompare::Output()
{
    m_lstA.Output("$$$$$$$$$$$$$$$$$$$$$$$$$  Left  $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$");
    m_lstB.Output("$$$$$$$$$$$$$$$$$$$$$$$$$  Right $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$");
    m_lstJoin.Output("$$$$$$$$$$$$$$$$$$$$$$$$$  Join  $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$");
}

void CListCompare::OutputGeneralInformation()
{
    TRACE("\nLeft:%d",m_lstA.GetCount());
    TRACE("\nRight:%d",m_lstB.GetCount());
    TRACE("\nJoin:%d",m_lstJoin.GetCount());
}


/*******************************************
    Function Name :	 
    Create by     :	  Qiu Simon
    Input         :   
    Output        :   
    Description   :   
    Date          :   9/16/2011 9:48:14 AM
********************************************/
void CListCompare::SaveAlltoB()
{
    CCmpListB listsetB;
    BOOL b = listsetB.Open();
    if(b)
    {
	    POSITION pos = m_lstJoin.GetHeadPosition();
	    while (pos)
        {
		    Alike2* palike = (Alike2*)m_lstJoin.GetNext(pos);
		    if(palike->IsNewB())
		    {
                listsetB.NewRecord(palike->m_pRecordB);
				palike->SetBStateExist();
			}
		    else if(palike->IsModifiedB())
		    {
                listsetB.ModifyRecord(palike->m_pRecordB);
				palike->SetBStateExist();
		    }
	    }
    }
    listsetB.Close();
}


/*******************************************
    Function Name :	 
    Create by     :	  Qiu Simon
    Input         :   
    Output        :   
    Description   :   
    Date          :   9/16/2011 9:48:10 AM
********************************************/
void CListCompare::SaveAlltoA()
{
    CCmpListA listsetA;
    BOOL b = listsetA.Open();
    if(b)
    {
        POSITION pos = m_lstJoin.GetHeadPosition();
        while (pos)
        {
            Alike2* palike = (Alike2*)m_lstJoin.GetNext(pos);
            if(palike->IsNewA())
            {
                listsetA.NewRecord(palike->m_pRecordA);
				palike->SetAStateExist();
            }
            else if(palike->IsModifiedA())
            {
                listsetA.ModifyRecord(palike->m_pRecordA);
				palike->SetAStateExist();
            }
        }
    }
    listsetA.Close();
}

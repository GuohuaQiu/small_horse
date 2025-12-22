// ListSet.cpp : implementation file
//

#include "stdafx.h"
#include "..\SmallHorse.h"
#include "ListSet.h"
#include "Convertdata.h"
#include "database_setup.h"
#include "SmartDate.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CListSet

IMPLEMENT_DYNAMIC(CListSet, CBaseRecordset)

CListSet::CListSet(CDatabase* pdb)
    : CBaseRecordset(pdb, snapshot)
{
    //{{AFX_FIELD_INIT(CListSet)
    m_ID = _T("");
    m_sum = _T("");
    m_addorsub = _T("");
    m_remain = _T("");
    m_arraynumber = 0;
    m_bType = 0;
    m_strSubCount = _T("");
    m_strSite = _T("");
    m_nFields = GetFieldCount();
    //}}AFX_FIELD_INIT
    m_nDefaultType = snapshot;
    m_strSort=_T("OperDate,Index");

    m_bSetUpdateTime = TRUE;
}

CString CListSet::GetDefaultSQL()
{
    return GetTableName();
}

BOOL CListSet::EnsureOpen()
{
    if (IsOpen())
    {
        return TRUE;
    }
    return OpenEx();
}




void CListSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CListSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Date(pFX, _T("[OperDate]"), m_day);
	RFX_Text(pFX, _T("[Item_Book_ID]"), m_ID);
	RFX_Text(pFX, _T("[Balance]"), m_sum);
	RFX_Text(pFX, _T("[Oper]"), m_addorsub);
	RFX_Text(pFX, _T("[Comment]"), m_remain);
	RFX_Int(pFX, _T("[Index]"), m_arraynumber);
	RFX_Byte(pFX, _T("[Type]"), m_bType);
	RFX_Text(pFX, _T("[SubCountID]"), m_strSubCount);
    RFX_Text(pFX, _T("[Site]"), m_strSite);
	RFX_Date(pFX, _T("[AddDate]"), m_TimeAdd);
	RFX_Date(pFX, _T("[ModifyDate]"), m_TimeModify);
	//}}AFX_FIELD_MAP
    if(pFX->m_nOperation == CFieldExchange::Fixup)
    {
        m_day.m_status = COleDateTime::valid;
    }
}
BOOL CListSet::FindByID(int nId)
{
    CString strFilter;
    strFilter.Format(_T("Index = '%d'"), nId);
    m_strFilter = strFilter;
    
    if (OpenEx())
    {
        return !IsEOF();
    }
    
    return FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// CListSet diagnostics

#ifdef _DEBUG
void CListSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CListSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


float CListSet::GetSumValue(BOOL bInt/*=TRUE*/)
{
    TCHAR* p;
	return (float)_tcstod(m_sum,&p);
}

float CListSet::GetAddorSubValue()
{
    TCHAR* p;
	return (float)_tcstod(m_addorsub,&p);
}

void CListSet::SetAddOrSubValue(float f)
{
	CString str;
	str.Format(_T("%8.2f"),f);
	m_addorsub=str;
}

void CListSet::SetSumValue(float f)
{
	CString str;
	str.Format(_T("%8.2f"),f);
	m_sum=str;
}

CString CListSet::GetRemain(CString strID)
{
	CString strfilter=m_strFilter;
	CString strsort=m_strSort;
	CString strfil=_T("\'")+strID+_T("\'");
	m_strFilter=_T("Item_Book_ID=")+ strfil;
	m_strSort=_T("OperDate,Index");
	Requery();
	MoveLast();
	CString strremain=m_sum;
	m_strFilter= strfilter;
	m_strSort =strsort;
	Requery();
	return strremain;
}

CString CListSet::GetAddorSub()
{
	CString str;
	str=m_addorsub;
	str.Delete(m_addorsub.GetLength()-2,2);
	return str;
}

CString CListSet::GetSum()
{
	CString str;
	str=m_sum;
	str.Delete(m_sum.GetLength()-2,2);
	return str;
}

CString CListSet::GetArray()
{
	CString str;
	str.Format(_T("%d"),m_arraynumber);
	return str;
}

CString CListSet::GetDate()
{
	CString str;
	str=m_day.Format(_T("%Y-%m-%d %H:%M:%S"));
	return str;
}


/*******************************************
    Function Name : 
    author        : Qiu Guohua
    Date          : 2004-09-22 13:59:09
    Description   : 
    Return type   : 
    Argument      : 
********************************************/
// void CListSet::SetNetIncome(BYTE bType)
// {
//     if(!IsBOF())
//     {
//         MoveFirst();
//     }
//     while(!IsEOF())
// 	{
// 		m_LockModify.Lock();
// 		Edit();
// 		m_bType=bType;
// 		Update();
// 		m_LockModify.Unlock();
// 		MoveNext();
// 	}
// }


BOOL CListSet::AddItems(CListCtrl *pctrl,int nType[],const CString& strId,int pATC[],int column_count)
{
	int nCount = pctrl->GetItemCount();
	CString strDate;
	CString strAdd;
	CString strComment;
	CString strType;
	double  fIncome;
	int nYear,nMonth,nDay,nHour, nMinute,nSec;
	nHour = 0;
	nMinute = 0;
	nSec = 0;
    CString strStamp;
	COleDateTime time = COleDateTime::GetCurrentTime();
	strStamp = time.Format(_T("(%Y-%m-%d %H:%M)"));

	CListSet listData;
	listData.StartEdit();
		

	BOOL bRet = TRUE;
	for(int i = 0;i<nCount;i++)
	{
		if(pctrl->GetCheck(i))
		{
			listData.AddNew();
			listData.m_ID = strId;
			if(nType[VALUE_TYPE_DATE]>=0)
			{
				strDate = pctrl->GetItemText(i,nType[VALUE_TYPE_DATE]);
				if(nType[VALUE_TYPE_ONLYTIME]>=0)
				{
					strDate += " ";
					strDate += pctrl->GetItemText(i,nType[VALUE_TYPE_ONLYTIME]);
				}
				nHour = 8;
				nMinute = 0;
				nSec = 0;

				int ret = theApp.GetDate(strDate,nYear,nMonth,nDay,nHour, nMinute,nSec);

				if(ret == 0)
				{
					CString msg;
					msg.Format("Below format cant be read:\n %s",strDate);

					AfxMessageBox(msg);
					return FALSE;
				}

				listData.m_day = COleDateTime(nYear,nMonth,nDay,nHour,nMinute,nSec);
			}
			fIncome = 0.0;

			TCHAR *pTempTchar;
			if(nType[VALUE_TYPE_INCOME]>=0)
			{
				strAdd = pctrl->GetItemText(i,nType[VALUE_TYPE_INCOME]);
				if(strAdd.Remove(','))
				{
					TRACE(_T("%s"),strAdd);
				}
				fIncome = _tcstod(strAdd,&pTempTchar);
			}
			if(nType[VALUE_TYPE_PAY]>=0)
			{
				strAdd = pctrl->GetItemText(i,nType[VALUE_TYPE_PAY]);
				if(strAdd.Remove(','))
				{
					TRACE(_T("%s"),strAdd);
				}
				fIncome -= _tcstod(strAdd,&pTempTchar);
			}
			listData.SetAddOrSubValue(fIncome);
			if(nType[VALUE_TYPE_SUBCOUNT]>=0)
			{
				listData.m_strSubCount = pctrl->GetItemText(i,nType[VALUE_TYPE_SUBCOUNT]);
			}
			CString strComment;
			if(nType[VALUE_TYPE_COMMENT]>=0)
			{
				strComment = pctrl->GetItemText(i,nType[VALUE_TYPE_COMMENT]);
			}

			//ADD TO COMMENTS
			for(int j = 0;j< column_count;j++)
			{
				if(pATC[j]==1)
				{
					strComment += " ";
					strComment += pctrl->GetItemText(i,j);
				}
			}

			int len = strComment.GetLength();

			while(len > 0 && strComment.GetAt(0) == _TCHAR(' '))
			{
				len--;
				strComment = strComment.Right(len);
			}
			listData.m_remain = strComment;


			if(nType[VALUE_TYPE_SUM]>=0)
			{
				CString str = pctrl->GetItemText(i,nType[VALUE_TYPE_SUM]);
				CString strSum;
				strSum.Format("(R:%s)",str);
				listData.m_remain += strSum;
			}
			listData.m_remain += strStamp;
			if(nType[VALUE_TYPE_SITE]>=0)
			{
				listData.m_strSite = pctrl->GetItemText(i,nType[VALUE_TYPE_SITE]);
			}

			int ret = listData.SubmitNew();

			//bRet = New_Item(&listData);

			if(ret)
			{
				bRet = FALSE;
				break;
			}
		}
	}
	listData.EndEdit();
	return bRet;
}

BOOL CListSet::GetCurrentBookId(CString &strID)
{
	if(!IsOnlyOneBook())
	{
		return FALSE;
	}
	int nLength = m_strFilter.GetLength();
	strID = m_strFilter.Mid(14,nLength - 15);
	return TRUE;
}

BOOL CListSet::IsOnlyOneBook()
{
	if(m_strFilter.Left(14) != _T("Item_Book_ID=\'"))
	{
		return FALSE;
	}
	return TRUE;
}

BOOL CListSet::Find(const COleDateTime &time, float fRecord,const CString& strSubCount)
{
    if(!IsBOF())
    {
        MoveFirst();
    }
    while(!IsEOF())
	{
		if(m_day.GetYear() != time.GetYear() || m_day.GetMonth() != time.GetMonth() || m_day.GetDay() != time.GetDay())
		{
			MoveNext();
			continue;
		}
        if((GetAddorSubValue() - fRecord)>0.001||(GetAddorSubValue() - fRecord)<-0.001)
		{
            MoveNext();
            continue;
		}
        if(m_strSubCount != strSubCount)
        {
            MoveNext();
            continue;
        }
		return TRUE;
	}
	return FALSE;
}


BOOL CListSet::MoveToID(int nID,LPCTSTR lpFilter)
{
	if(lpFilter!=NULL)
	{
		if(m_strFilter != lpFilter)
		{
			m_strFilter = lpFilter;
			Requery();
		}
		if(GetRecordCount()==0)
		{
			return FALSE;
		}
		MoveFirst();
		while(!IsEOF())
		{
			if(m_arraynumber==nID)
				return TRUE;
			MoveNext();
		}
		TRACE(_T("\nNo Move to End %d FALSE"),m_arraynumber);
		return FALSE;
	}
	else
	{
		if(GetRecordCount()>0)
		{
			MoveFirst();
			while(!IsEOF())
			{
				if(m_arraynumber==nID)
					return TRUE;
				MoveNext();
			}
		}
		OpenOneRecord(nID);
		if(GetRecordCount()>0)
		{
			return TRUE;
		}

		TRACE(_T("\nNo Move to End %d FALSE"),m_arraynumber);
		return FALSE;
	}
}





/*******************************************
    Function Name : 
    author        : Qiu Guohua
    Date          : 2009-5-5 22:56:32
    Description   : 
    Return type  : 
    Argument      : 
********************************************/
BOOL CListSet::UpdateRequery()
{
	BOOL b = CRecordset::Update();
	if(!b)
	{
		return FALSE;
	}
	
	return Requery();
}




/*******************************************
    Function Name : 
    author        : Qiu Guohua
    Date          : 2009-5-7 21:16:15
    Description   : 
    Return type  : 
    Argument      : 
********************************************/
int CListSet::RequerySubCount(const CString &strMainCount, const CString &strSubCount)
{
	CString strfil=_T("\'")+strMainCount+_T("\'");
	CString strFilter;

	strFilter =_T("Item_Book_ID = ") + strfil;// '379 70052992*3'
	
	strfil=_T("\'")+strSubCount+_T("\'");
	strFilter +=_T(" and  SubCountID = ") + strfil;// '379 70052992*3'
	m_strFilter = strFilter;
	Requery();
	return GetRecordCount();
}

void CListSet::OpenOneRecord(int nID)
{
	m_strFilter.Format(_T("Index = %d "),nID);
	Requery();
}


/*******************************************
    Function Name :	 
    Create by     :	  Qiu Simon
    Input         :   
    Output        :   
    Description   :   
    Date          :   2010-4-12 14:56:47
********************************************/
void  CListSet::AddNew()
{
    CRecordset::AddNew();
    m_TimeAdd = COleDateTime::GetCurrentTime();
}


/*******************************************
    Function Name :	 
    Create by     :	  Qiu Simon
    Input         :   
    Output        :   
    Description   :   
    Date          :   2010-4-12 14:56:51
********************************************/
void  CListSet::Edit()
{
    CRecordset::Edit();
    if(m_bSetUpdateTime)
    {
        m_TimeModify = COleDateTime::GetCurrentTime();
    }
}



/*******************************************
    Function Name :	 
    Create by     :	  Qiu Simon
    Input         :   
    Output        :   
    Description   :   
    Date          :   2010-5-14 14:30:43
********************************************/
void CListSet::SetUpdateTime(BOOL bSet)
{
    m_bSetUpdateTime = bSet;
}


/*******************************************
    Function Name : 
    author        : Qiu Guohua
    Date          : 2010-12-17 21:34:59
    Description   : 
    Return type   : 
    Argument      : 
********************************************/
void CListSet::GetGenerationInfo(LPGEN_INFO pinfo)
{
/*    for(int i= 0;i< 80;i++)
    {
        CString str;
        str.Format("%d",i);
        GetGenerationInfo(pinfo,str);
    }*/
    pinfo->mAmountEarn=0;
    pinfo->mTimesEarn=0;
    pinfo->mAmountExpense=0;
    pinfo->mTimesExpense=0;
    pinfo->mAmountTotal=0;
    pinfo->mTimesTotal=0;
    
    if(GetRecordCount()==0)
    {
        return ;
    }
    MoveFirst();
    float fThis;
    while(!IsEOF())
    {
        fThis = GetAddorSubValue();
        if(fThis >= 0.0)
        {
            pinfo->mAmountEarn += fThis;
            pinfo->mTimesEarn++;
        }
        else
        {
            pinfo->mAmountExpense += fThis;
            pinfo->mTimesExpense++;
        }
        MoveNext();
    }
    pinfo->mAmountTotal=pinfo->mAmountEarn+pinfo->mAmountExpense;
    pinfo->mTimesTotal=pinfo->mTimesEarn+pinfo->mTimesExpense;
}


/*******************************************
    Function Name :	 
    Create by     :	  Qiu Simon
    Input         :   
    Output        :   
    Description   :   
    Date          :   12/24/2010 5:03:39 PM
********************************************/
LPRECORD CListSet::NewCopy()
{
    LPRECORD pRecord = new Record;
	pRecord->m_day  = m_day;
	pRecord->m_ID  = m_ID;
	pRecord->m_addorsub  = m_addorsub;
	pRecord->m_remain  = m_remain;
	pRecord->m_arraynumber  = m_arraynumber;
	pRecord->m_bType  = m_bType;
	pRecord->m_strSubCount  = m_strSubCount;
    pRecord->m_strSite  = m_strSite;

	pRecord->m_sum  = m_sum;
	pRecord->m_TimeAdd  = m_TimeAdd;
	pRecord->m_TimeModify  = m_TimeModify;
    return pRecord;
}


/*******************************************
    Function Name :	 
    Create by     :	  Qiu Simon
    Input         :   
    Output        :   
    Description   :   
    Date          :   12/24/2010 5:18:51 PM
********************************************/
BOOL CListSet::LoadAll(CRecordList* pList)
{
    pList->RemoveAll();
    if(GetRecordCount()==0)
    {
        return TRUE;
    }
    MoveFirst();
    while(!IsEOF())
    {
        LPRECORD pRecord = NewCopy();
        pList->AddTail(pRecord);
        MoveNext();
    }
    return TRUE;
}

void CListSet::GetGenerationInfo(LPGEN_INFO pinfo, const CString &strSubId)
{
    pinfo->mAmountEarn=0;
    pinfo->mTimesEarn=0;
    pinfo->mAmountExpense=0;
    pinfo->mTimesExpense=0;
    pinfo->mAmountTotal=0;
    pinfo->mTimesTotal=0;
    
    if(GetRecordCount()==0)
    {
        return ;
    }
    MoveFirst();
    float fThis;
    while(!IsEOF())
    {
        if(this->m_strSubCount != strSubId)
        {
            MoveNext();
            continue;
        }
        fThis = GetAddorSubValue();
        if(fThis >= 0.0)
        {
            pinfo->mAmountEarn += fThis;
            pinfo->mTimesEarn++;
            TRACE("%d:mAmountEarn %.2f\n",pinfo->mTimesEarn,pinfo->mAmountEarn);
        }
        else
        {
            pinfo->mAmountExpense += fThis;
            pinfo->mTimesExpense++;
            TRACE("%d:mAmountExpense %.2f\n",pinfo->mTimesExpense,pinfo->mAmountExpense);
        }
        MoveNext();
    }
    pinfo->mAmountTotal=pinfo->mAmountEarn+pinfo->mAmountExpense;
    pinfo->mTimesTotal=pinfo->mTimesEarn+pinfo->mTimesExpense;
    TRACE("%s\t收入：%.2f\t\t支出：%.2f\t\t合计：%.2f\n",strSubId,pinfo->mAmountEarn,pinfo->mAmountExpense,pinfo->mAmountTotal);
}


/*******************************************
    Function Name :	 
    Create by     :	  Qiu Simon
    Input         :   
    Output        :   
    Description   :   New a record from Record ,mainly for compare result. 
    Date          :   9/16/2011 9:29:26 AM
********************************************/
BOOL CListSet::NewRecord(Record *precord)
{
//    AddNew();
	CListSet listData;
	listData.StartEdit();



	listData.AddNew();




    listData.m_remain = precord->m_remain ; 
    listData.m_day = precord->m_day ;
    listData.m_bType = precord->m_bType ;
    listData.m_addorsub = precord->m_addorsub ;
    listData.m_ID = precord->m_ID ;
	listData.m_strSubCount = precord->m_strSubCount;
    listData.m_strSite = precord->m_strSite ;
	listData.m_TimeAdd = precord->m_TimeAdd;
	listData.m_TimeModify = precord->m_TimeModify;
	listData.SubmitNew();
	listData.EndEdit();
	return TRUE;
	//return New_Item(&listData);
}


/*******************************************
    Function Name :	 
    Create by     :	  Qiu Simon
    Input         :   
    Output        :   
    Description   :   
    Date          :   9/16/2011 9:32:06 AM
********************************************/
BOOL CListSet::ModifyRecord(Record *pInData)
{
    MoveToID(pInData->m_arraynumber);
	TRACE("Update %d\n",pInData->m_arraynumber);
	m_LockModify.Lock();
	CString strSQL="update Items set ";
	BOOL IsFirst = TRUE;
	//     m_ID = precord->m_ID ;
	// 	m_strSubCount = precord->m_strSubCount;
	// 
	//     m_day = precord->m_day ;
	// 	
	//     m_addorsub = precord->m_addorsub ;
	// 
	//     m_remain = precord->m_remain ; 
	//     m_bType = precord->m_bType ;
	// 	
	//     m_strSite = precord->m_strSite ;
	IsFirst = CDatabaseUtility::Generate_modify_string("Item_Book_ID",m_ID,pInData->m_ID,strSQL,IsFirst);
	IsFirst = CDatabaseUtility::Generate_modify_string("SubCountID",m_strSubCount,pInData->m_strSubCount,strSQL,IsFirst);
	IsFirst = CDatabaseUtility::Generate_modify_Time("OperDate",m_day,pInData->m_day,strSQL,IsFirst);
	IsFirst = CDatabaseUtility::Generate_modify_string("Oper",m_addorsub,pInData->m_addorsub,strSQL,IsFirst);
	IsFirst = CDatabaseUtility::Generate_modify_string("Comment",m_remain,pInData->m_remain,strSQL,IsFirst);
	IsFirst = CDatabaseUtility::Generate_modify_int("Type",m_bType,pInData->m_bType,strSQL,IsFirst);
	IsFirst = CDatabaseUtility::Generate_modify_string("Site",m_strSite,pInData->m_strSite,strSQL,IsFirst);
	if(!IsFirst)
	{
		CDatabaseUtility::Generate_modify_Time("ModifyDate",m_TimeModify,COleDateTime::GetCurrentTime(),strSQL,FALSE);
		CDatabaseUtility::Append_Condition_Int("Index",strSQL,m_arraynumber);
		TRACE("%s\n",strSQL);
		m_pDatabase->ExecuteSQL(strSQL);
		m_LockModify.Unlock();
		return TRUE;
	}
	TRACE("No any change....\n");
	m_LockModify.Unlock();
	return FALSE;

//     Edit();
//     m_ID = precord->m_ID ;
// 	m_strSubCount = precord->m_strSubCount;
// 
//     m_day = precord->m_day ;
// 	
//     m_addorsub = precord->m_addorsub ;
// 
//     m_remain = precord->m_remain ; 
//     m_bType = precord->m_bType ;
// 	
//     m_strSite = precord->m_strSite ;
// 	m_TimeModify = precord->m_TimeModify;
// 
// 	BOOL b = Update();
	m_LockModify.Unlock();
    return TRUE;
}

BOOL CListSet::GetFirstDate(CSmartDate &date)
{
	if(GetRecordCount()>0)
	{
		MoveFirst();
		date.year = m_day.GetYear();
		date.month = m_day.GetMonth();
		date.day = m_day.GetDay();
		return TRUE;
	}
	else
	{
		return FALSE;
	}
	
}

BOOL CListSet::GetLastDate(CSmartDate &date)
{
	if(GetRecordCount()>0)
	{
		MoveLast();
		date.year = m_day.GetYear();
		date.month = m_day.GetMonth();
		date.day = m_day.GetDay();
		return TRUE;
	}
	else
	{
		return FALSE;
	}
	
}

BOOL CListSet::Edit_CalSum(float* fSum)
{
	m_LockModify.Lock();
	*fSum += GetAddorSubValue();

	CString strSQL;

	strSQL.Format("update Items set Balance=%.2f where Index=%d",*fSum,m_arraynumber);
	TRACE(strSQL);
	TRACE("\n");
	m_pDatabase->ExecuteSQL(strSQL);
	//Edit();
	SetSumValue(*fSum);
	//BOOL b = Update();
	m_LockModify.Unlock();
	return TRUE;
}

BOOL CListSet::New_Item(CListSet* pInData){

	CListSet listData;
	listData.StartEdit();

	listData.AddNew();

	listData.m_day = pInData->m_day;
	listData.m_ID = pInData->m_ID;
	listData.m_strSubCount = pInData->m_strSubCount;
	listData.m_bType = pInData->m_bType;
	listData.m_strSite = pInData->m_strSite;
	listData.m_addorsub = pInData->m_addorsub;
	listData.m_remain = pInData->m_remain;

	listData.SubmitNew();
	listData.EndEdit();
	return TRUE;
}



BOOL CListSet::Modify_Record(CListSet *pInData)
{
	m_LockModify.Lock();
	CString strSQL="update Items set ";
	BOOL IsFirst = TRUE;
	IsFirst = CDatabaseUtility::Generate_modify_string("Item_Book_ID",m_ID,pInData->m_ID,strSQL,IsFirst);
	IsFirst = CDatabaseUtility::Generate_modify_string("SubCountID",m_strSubCount,pInData->m_strSubCount,strSQL,IsFirst);
	IsFirst = CDatabaseUtility::Generate_modify_Time("OperDate",m_day,pInData->m_day,strSQL,IsFirst);
	IsFirst = CDatabaseUtility::Generate_modify_string("Oper",m_addorsub,pInData->m_addorsub,strSQL,IsFirst);
	IsFirst = CDatabaseUtility::Generate_modify_string("Comment",m_remain,pInData->m_remain,strSQL,IsFirst);
	IsFirst = CDatabaseUtility::Generate_modify_int("Type",m_bType,pInData->m_bType,strSQL,IsFirst);
	IsFirst = CDatabaseUtility::Generate_modify_string("Site",m_strSite,pInData->m_strSite,strSQL,IsFirst);
	if(!IsFirst)
	{
		CDatabaseUtility::Generate_modify_Time("ModifyDate",m_TimeModify,COleDateTime::GetCurrentTime(),strSQL,FALSE);
		CDatabaseUtility::Append_Condition_Int("Index",strSQL,m_arraynumber);
		TRACE("%s\n",strSQL);
		m_pDatabase->ExecuteSQL(strSQL);
		m_LockModify.Unlock();
		return TRUE;
	}
	TRACE("No any change....\n");
	m_LockModify.Unlock();
	return FALSE;
}


#if 0
BOOL CListSet::Modify_Type(BYTE type)
{
// 	m_LockModify.Lock();
// 	ASSERT(FALSE);
// 	Edit();
// 	m_bType = type;
// 	BOOL b = Update();
// 	m_LockModify.Unlock();
// 	return b;
}
#endif
BOOL CListSet::Modify_Transfer(const CString &strID)
{
	CString strComments;
	strComments.Format(_T("To %s;%s"),strID,m_remain);

	m_LockModify.Lock();
	CString strSql;
	CString strSQL="update Items set ";
	CDatabaseUtility::Generate_modify_string("Comment",strComments,strSQL);
	strSQL += ",";
	CDatabaseUtility::Generate_modify_int("Type",theApp.GetTypeIndex(_T("转存")),strSQL);
	CDatabaseUtility::Append_Condition_Int("Index",strSQL,m_arraynumber);
	TRACE("%s\n",strSQL);
	m_pDatabase->ExecuteSQL(strSQL);
	m_LockModify.Unlock();
	return TRUE;

// 	Edit();
// 	m_remain = strComments;
// 	m_bType = theApp.GetTypeIndex(_T("转存"));
// 	BOOL b = Update();

}
void CListSet::Move(long nRows, WORD wFetchType)
{
	m_LockModify.Lock();
	CRecordset::Move(nRows,wFetchType);
	m_LockModify.Unlock();
}




void CListSet::Trace(void)
{
	TRACE("Item Record:\n");
	//TRACE("RECORD: m_day = %s\n",m_day);
	TRACE("RECORD: m_ID = %s\n",m_ID);
	TRACE("RECORD: m_sum = %s\n",m_sum);
	TRACE("RECORD: m_addorsub = %s\n",m_addorsub);
	TRACE("RECORD: m_remain = %s\n",m_remain);
	TRACE("RECORD: m_arraynumber = %d\n",m_arraynumber);
	//TRACE("RECORD: m_bType = %d\n",m_bType);
	//TRACE("RECORD: m_strSubCount = %s\n",m_strSubCount);
	//TRACE("RECORD: m_strSite = %s\n",m_strSite);
	//TRACE("RECORD: m_TimeAdd = %s\n",m_TimeAdd);
	//TRACE("RECORD: m_TimeModify = %s\n",m_TimeModify);
}



int CListSet::Modify_Type_ByComment(int type,const CString& strNoHas, const CString& strHas,const CDWordArray& dbArray,int count)
{
	CString strSQL="update Items set ";
	CDatabaseUtility::Generate_modify_int("Type",type,strSQL);
	CDatabaseUtility::Append_Condition_Int_Array("Index",strSQL,dbArray,count);
	CString strTemp;
	if(strHas.GetLength() >0)
	{
		strTemp.Format(" and Comment like \'%%%s\%%\'",strHas);
		strSQL += strTemp;
	}
	if(strNoHas.GetLength() >0)
	{
		strTemp.Format(" and Comment not like \'%%%s%%\'",strNoHas);
		strSQL += strTemp;
	}
	TRACE("%s\n",strSQL);
	m_pDatabase->ExecuteSQL(strSQL);

	return 0;
}

int CListSet::Modify_Site_ByComment(const CString&strSite,const CString& strNoHas, const CString& strHas,const CDWordArray& dbArray,int count)
{
	CString strSQL="update Items set ";
	CDatabaseUtility::Generate_modify_string("Site",strSite,strSQL);
	CDatabaseUtility::Append_Condition_Int_Array("Index",strSQL,dbArray,count);
	CString strTemp;
	if(strHas.GetLength() >0)
	{
		strTemp.Format(" and Comment like \'%%%s\%%\'",strHas);
		strSQL += strTemp;
	}
	if(strNoHas.GetLength() >0)
	{
		strTemp.Format(" and Comment not like \'%%%s%%\'",strNoHas);
		strSQL += strTemp;
	}
	strSQL += strTemp;
	TRACE("%s\n",strSQL);
	m_pDatabase->ExecuteSQL(strSQL);

	return 0;
}

int CListSet::Replace_Comment(const CString& strOldString, const CString& strNewString,const CDWordArray& dbArray,int count)
{
	//"UPDATE tableName SET recordName=REPLACE(recordName,'abc','ddd')"
	CString strSQL="update Items set Comment=REPLACE(Comment,\'";
	strSQL += strOldString;
	strSQL += "\',\'";
	strSQL += strNewString;
	strSQL += "\')";

	CDatabaseUtility::Append_Condition_Int_Array("Index",strSQL,dbArray,count);
	TRACE("%s\n",strSQL);
	m_pDatabase->ExecuteSQL(strSQL);

	return 0;
}



int CListSet::MoveRecordsTo(const CString& Count, const CString& SubCount,const CDWordArray& dbArray,int count)
{
	CString strSQL="update Items set ";
	CDatabaseUtility::Generate_modify_string("Item_Book_ID",Count,strSQL);
	if(SubCount.GetLength()>0)
	{
        strSQL += ",";
		CDatabaseUtility::Generate_modify_string("SubCountID",SubCount,strSQL);
	}
	CDatabaseUtility::Append_Condition_Int_Array("Index",strSQL,dbArray,count);

	TRACE("%s\n",strSQL);
	m_pDatabase->ExecuteSQL(strSQL);

	return 0;
}

int CListSet::StartEdit()
{
	if (IsOpen()) {
		Close();
	}
	Open(CRecordset::dynaset);
	Requery();
	MoveLast();
	
	return 0;
}


int CListSet::SubmitEdit()
{
	m_TimeModify = COleDateTime::GetCurrentTime();
	BOOL b = Update();

	TRACE("New item ok? %s", b ? "TRUE" : "FALSE");

	if (b) {
		return 0;
	}
	return -1;
}


int CListSet::SubmitNew()
{
	m_TimeAdd = COleDateTime::GetCurrentTime();
	m_TimeModify = COleDateTime::GetCurrentTime();
	BOOL b = Update();


	TRACE("New item ok? %s", b ? "TRUE" : "FALSE");

	if (b) {
		return 0;
	}
	return -1;
}

int CListSet::EndEdit()
{
	Close();
	theApp.ForceUpdateViews();
	return 0;

}


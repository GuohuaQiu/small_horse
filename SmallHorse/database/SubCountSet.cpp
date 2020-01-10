// SubCountSet.cpp : implementation file
//

#include "stdafx.h"
#include "..\SmallHorse.h"
#include "SubCountSet.h"
#include "CONVERTDATA.h"
#include "database_setup.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSubCountSet

IMPLEMENT_DYNAMIC(CSubCountSet, CRecordset)

CSubCountSet::CSubCountSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CSubCountSet)
	m_Index = 0;
	m_Count_ID = _T("");
	m_Sub_Count_ID = _T("");
	m_Year_Rate = 0.0f;
	m_Comment = _T("");
	m_Time_Span = 0;
	m_BeginValue = 0.0f;
	m_bExist = TRUE;
	m_nFields = 10;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CSubCountSet::GetDefaultConnect()
{
	return DATA_SOURCE_NAME_ODBC;
}

CString CSubCountSet::GetDefaultSQL()
{
	return _T("[Sub_Count_Table]");
}

void CSubCountSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CSubCountSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[Index]"), m_Index);
	RFX_Text(pFX, _T("[CountID]"), m_Count_ID);
	RFX_Text(pFX, _T("[SubCountID]"), m_Sub_Count_ID);
	RFX_Date(pFX, _T("[StartDate]"), m_Start_Date);
	RFX_Date(pFX, _T("[EndDate]"), m_End_Date);
	RFX_Single(pFX, _T("[YearRate]"), m_Year_Rate);
	RFX_Text(pFX, _T("[Comment]"), m_Comment);
	RFX_Long(pFX, _T("[TimeSpan]"), m_Time_Span);
	RFX_Single(pFX, _T("[BeginValue]"), m_BeginValue);
	RFX_Bool(pFX, _T("[Exist]"), m_bExist);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CSubCountSet diagnostics

#ifdef _DEBUG
void CSubCountSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSubCountSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG

void CSubCountSet::RequeryCount(const CString &strCount)
{
	CString strfil=_T("\'")+strCount+_T("\'");
	m_strFilter =_T("CountID= ") + strfil;
	Requery();
}



TCHAR pFieldName[VALUE_SUBCOUNT_TYPE_number][16]=
{
	_T("SubCountID"),_T("BeginValue"),_T("StartDate"),_T("EndDate"),_T("YearRate"),_T("TimeSpan"),_T("Comment")
};





/*******************************************
    Function Name : 
    author        : Qiu Guohua
    Date          : 2009-4-28 21:59:16
    Description   : 
    Return type  : 
    Argument      : 
********************************************/
BOOL CSubCountSet::AddItems(CListCtrl *pctrl, int nType[],CString strMainCount,int pATC[],int column_count)
{
	int nCount = pctrl->GetItemCount();

	BOOL bRet = TRUE;
	CString strSQL,strField,strValue;
	for(int i = 0;i<nCount;i++)
	{
		if(pctrl->GetCheck(i))
		{
			strField = "CountID";
			strValue = "\'" + strMainCount + "\'";
			CString strTmp;
			for(int j = 0;j<VALUE_SUBCOUNT_TYPE_number;j++)
			{
				if(nType[j]>=0)
				{
					strField += ",";
					strField += pFieldName[j];
					strTmp = pctrl->GetItemText(i,nType[j]);
					strValue += ",\'" + strTmp + "\'"; 
				}
			}
			//INSERT INTO php_table( `id`, `username`, `others` ) VALUES( '$id', '$username', '$others' )
			strSQL.Format("insert into Sub_Count_Table(%s) values(%s)",strField,strValue);
			m_pDatabase->ExecuteSQL(strSQL);
		}
	}
	AddFirstRecordforSubCount(strMainCount);
	return bRet;
}

BOOL CSubCountSet::Find(const CString &strMainCount, const CString &strSubCount)
{
	if(GetRecordCount()==0)
	{
		return FALSE;
	}
    if(!IsBOF())
    {
        MoveFirst();
    }
	while(!IsEOF())
	{
		if((m_Count_ID == strMainCount)&&(m_Sub_Count_ID == strSubCount))
		{
			return TRUE;
		}
		MoveNext();
	}
	return FALSE;
}


/*******************************************
    Function Name : 
    author        : Qiu Guohua
    Date          : 2009-5-7 21:04:43
    Description   : 
    Return type  : 
    Argument      : 
********************************************/
void CSubCountSet::AddFirstRecordforSubCount(const CString& strMainCount)
{
	RequeryCount(strMainCount);
	CListSet listset;
	listset.Open();
	int nCount;
	if(GetRecordCount()>0)
	{
        if(!IsBOF())
        {
            MoveFirst();
        }
		while(!IsEOF())
		{
			//add first record for the 0 record sub counts.
			nCount = listset.RequerySubCount(strMainCount,m_Sub_Count_ID);
			TRACE("%s has %d records\n",m_Sub_Count_ID,nCount);
			if(nCount == 0)
			{
				listset.AddNew();
				listset.m_day=m_Start_Date;
				listset.m_ID=strMainCount;
				listset.m_strSubCount = m_Sub_Count_ID;
				listset.m_remain.Format("first record:%s",m_Sub_Count_ID);
				listset.m_bType=3;
				listset.m_addorsub.Format("%f",m_BeginValue);
				listset.Update();
			}
			MoveNext();
		}
	}
}


/*******************************************
    Function Name :	 
    Create by     :	  Qiu Simon
    Input         :   
    Output        :   
    Description   :   
    Date          :   2010-2-23 16:58:50
********************************************/
void CSubCountSet::GetTipString(CString &strTip)
{
    CString strdate=m_Start_Date.Format("%Y-%m-%d");
    CString strenddate=m_End_Date.Format("%Y-%m-%d");
    strTip.Format("%10.2f %s -> %s",m_BeginValue,strdate,strenddate);
}


/*******************************************
    Function Name : 
    author        : Qiu Guohua
    Date          : 2010-12-20 20:30:01
    Description   : 
    Return type   : 
    Argument      : 
********************************************/
void CSubCountSet::SetAllExist()
{
    if(!IsBOF())
    {
        MoveFirst();
    }
    while(!IsEOF())
    {
        if(!m_bExist)
        {
            Edit( );
            m_bExist = TRUE;
            Update();
        }
        MoveNext();
    }
}
void CSubCountSet::SetNoExist()
{
	CString strSQL;
	strSQL.Format("update Sub_Count_Table set BeginValue=0.000001f,Exist=0 where Index=",m_Index);
	m_pDatabase->ExecuteSQL(strSQL);

}
void CSubCountSet::MakeDataCopy(CSubCountSet& subSet)
{
	subSet.m_Index=m_Index;
	subSet.m_Count_ID=m_Count_ID;
	subSet.m_Sub_Count_ID=m_Sub_Count_ID;
	subSet.m_Start_Date=m_Start_Date;
	subSet.m_End_Date=m_End_Date;
	subSet.m_Year_Rate=m_Year_Rate;
	subSet.m_Comment=m_Comment;
	subSet.m_Time_Span=m_Time_Span;
	subSet.m_BeginValue=m_BeginValue;
	subSet.m_bExist=m_bExist;
}

BOOL CSubCountSet::Modify(CSubCountSet* pInData)
{
	CString strSQL="update Books set ";
	BOOL IsFirst = TRUE;

	IsFirst = CDatabaseUtility::Generate_modify_string("CountID",m_Count_ID,pInData->m_Count_ID,strSQL,IsFirst);
	IsFirst = CDatabaseUtility::Generate_modify_string("SubCountID",m_Sub_Count_ID,pInData->m_Sub_Count_ID,strSQL,IsFirst);
	IsFirst = CDatabaseUtility::Generate_modify_string("Comment",m_Comment,pInData->m_Comment,strSQL,IsFirst);


	IsFirst = CDatabaseUtility::Generate_modify_Time("StartDate",m_Start_Date,pInData->m_Start_Date,strSQL,IsFirst);
	IsFirst = CDatabaseUtility::Generate_modify_Time("EndDate",m_End_Date,pInData->m_End_Date,strSQL,IsFirst);

	IsFirst = CDatabaseUtility::Generate_modify_int("Exist",m_bExist,pInData->m_bExist,strSQL,IsFirst);
	IsFirst = CDatabaseUtility::Generate_modify_int("TimeSpan",m_Time_Span,pInData->m_Time_Span,strSQL,IsFirst);

//	RFX_Single(pFX, _T("[YearRate]"), m_Year_Rate);

	//Simon to do rate 
	IsFirst = CDatabaseUtility::Generate_modify_float("BeginValue",m_BeginValue,pInData->m_BeginValue,strSQL,IsFirst);

	CString strTemp;
	if(!IsFirst)
	{
		CDatabaseUtility::Append_Condition_Int("Index",strSQL,m_Index);
		TRACE("%s\n",strSQL);
		m_pDatabase->ExecuteSQL(strSQL);
		return TRUE;
	}
	TRACE("No any change....\n");
	return FALSE;

}
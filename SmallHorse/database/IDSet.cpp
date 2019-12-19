// IDSet.cpp : implementation file
//

#include "stdafx.h"
#include "..\SmallHorse.h"

#include "database_setup.h"
#include "idset.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIDSet


IMPLEMENT_DYNAMIC(CIDSet, CRecordset)

CIDSet::CIDSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CIDSet)
	m_ID = _T("");
	m_bank = _T("");
	m_name = _T("");
	m_remain = _T("");
	m_password = _T("");
	m_bDefaultNetIncome = 0;
	m_bExist = FALSE;
	m_nType = 0;
	m_EditStatus = 0;
	m_nFields = 10;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CIDSet::GetDefaultConnect()
{
	return DATA_SOURCE_NAME_ODBC;
}

CString CIDSet::GetDefaultSQL()
{
	return _T("[Books]");
}
BOOL CIDSet::Modify_Book(CIDSet* pInData)
{
	CString strSQL="update Books set ";
	BOOL IsFirst = TRUE;
	IsFirst = CDatabaseUtility::Generate_modify_string("Book_Bank",m_bank,pInData->m_bank,strSQL,IsFirst);
	IsFirst = CDatabaseUtility::Generate_modify_string("Book_Owner",m_name,pInData->m_name,strSQL,IsFirst);
	IsFirst = CDatabaseUtility::Generate_modify_string("Book_Comment",m_remain,pInData->m_remain,strSQL,IsFirst);
	IsFirst = CDatabaseUtility::Generate_modify_string("Book_Password",m_password,pInData->m_password,strSQL,IsFirst);
	IsFirst = CDatabaseUtility::Generate_modify_Time("Book_InitDate",m_InitDate,pInData->m_InitDate,strSQL,IsFirst);
	IsFirst = CDatabaseUtility::Generate_modify_int("Book_Type",m_nType,pInData->m_nType,strSQL,IsFirst);
	IsFirst = CDatabaseUtility::Generate_modify_int("Book_Default_Type",m_bDefaultNetIncome,pInData->m_bDefaultNetIncome,strSQL,IsFirst);
	IsFirst = CDatabaseUtility::Generate_modify_int("Book_Exist",m_bExist,pInData->m_bExist,strSQL,IsFirst);
	IsFirst = CDatabaseUtility::Generate_modify_int("Book_Editable",m_EditStatus,pInData->m_EditStatus,strSQL,IsFirst);

	CString strTemp;
	if(!IsFirst)
	{
		CDatabaseUtility::Append_Condition_Str("Book_ID",strSQL,m_ID);
		TRACE("%s\n",strSQL);
		m_pDatabase->ExecuteSQL(strSQL);
		return TRUE;
	}
	TRACE("No any change....\n");
	return FALSE;

}

void CIDSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CIDSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[Book_ID]"), m_ID);
	RFX_Text(pFX, _T("[Book_Bank]"), m_bank);
	RFX_Text(pFX, _T("[Book_Owner]"), m_name);
	RFX_Text(pFX, _T("[Book_Comment]"), m_remain);
	RFX_Text(pFX, _T("[Book_Password]"), m_password);
	RFX_Byte(pFX, _T("[Book_Default_Type]"), m_bDefaultNetIncome);
	RFX_Bool(pFX, _T("[Book_Exist]"), m_bExist);
	RFX_Int(pFX, _T("[Book_Type]"), m_nType);
	RFX_Int(pFX, _T("[Book_Editable]"), m_EditStatus);
	RFX_Date(pFX, _T("[Book_InitDate]"), m_InitDate);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CIDSet diagnostics

#ifdef _DEBUG
void CIDSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CIDSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG

BOOL CIDSet::MovetoCurID(const CString& strid)
{
	BOOL bSuccess=FALSE;
    if(!IsBOF())
    {
	    MoveFirst();
    }
	while(!IsEOF())
	{
		if(m_ID==strid)
		{
			bSuccess=TRUE;
			break;
		}
		MoveNext();
	}
	return bSuccess;
}
int CIDSet::Find(const CString &strField, const CString &strFind)
{
	CString strfilter=m_strFilter;
	CString strsort=m_strSort;
	CString strfil=_T("\'")+strField+_T("\'");
	m_strFilter=_T("ID = ")+ strfil;
	m_strSort=_T("OperDate,Index");
	Requery();
	MoveLast();
	return 0;
}

BOOL CIDSet::Find(const CString &strContain, CString &strID)
{
    if(!IsBOF())
    {
        MoveFirst();
    }
    while(!IsEOF())
	{
		int nRet = m_ID.Find(strContain,0);

		if(nRet != -1)
		{
			strID = m_ID;
			return TRUE;
		}
		MoveNext();
	}
	return FALSE;
}



/*******************************************
    Function Name : 
    author        : Qiu Guohua
    Date          : 2010-10-31 14:18:12
    Description   : 
    Return type   : 
    Argument      : 
********************************************/
void CIDSet::SetAllDefaultType(int nType)
{
    if(!IsBOF())
    {
        MoveFirst();
    }
    while(!IsEOF())
    {
        if(m_nType <0 || m_nType >5)
        {
            Edit( );
            m_nType = nType;
            Update();
        }
        MoveNext();
    }
}


/*******************************************
    Function Name :	 
    Create by     :	  Qiu Simon
    Input         :   
    Output        :   
    Description   :   
    Date          :   1/10/2011 4:59:51 PM
********************************************/
CString CIDSet::GetType()
{
    CBookTypeSet* pset = theApp.GetBookTypeSet();
    return pset->GetBookType(m_nType);
}


/*******************************************
    Function Name :	 
    Create by     :	  Qiu Simon
    Input         :   
    Output        :   -1 represent no this card.
    Description   :   
    Date          :   5/23/2012 3:24:46 PM
********************************************/
int CIDSet::GetEditStatus(const CString &strID)
{
    if(MovetoCurID(strID))
    {
        return m_EditStatus;
    }
    return -1;
}


/*******************************************
    Function Name :	 
    Create by     :	  Qiu Simon
    Input         :   
    Output        :   
    Description   :   
    Date          :   5/23/2012 5:10:20 PM
********************************************/
BOOL CIDSet::LockEditStatus(const CString &strid)
{
    if(MovetoCurID(strid))
    {
		CString strSQL="update Books set ";
		BOOL IsFirst = CDatabaseUtility::Generate_modify_int("Book_Editable",m_EditStatus,0,strSQL,TRUE);

		if(!IsFirst)
		{
			CDatabaseUtility::Append_Condition_Str("Book_ID",strSQL,m_ID);
			TRACE("%s\n",strSQL);
			m_pDatabase->ExecuteSQL(strSQL);
			return TRUE;
		}


//         Edit();
//         m_EditStatus = 0;
//         return Update();
    }
    return FALSE;
}

void CIDSet::MakeDataCopy(CIDSet& idSet)
{
	idSet.m_ID = m_ID;
	idSet.m_bank = m_bank;
	idSet.m_name = m_name;
	idSet.m_remain = m_remain;
	idSet.m_password = m_password;
	idSet.m_bDefaultNetIncome = m_bDefaultNetIncome;
	idSet.m_bExist = m_bExist;
	idSet.m_nType = m_nType;
	idSet.m_EditStatus = m_EditStatus;
	idSet.m_InitDate = m_InitDate;
	TRACE("Just Copy after: status n-o: %d|%d Year %d|%d \n",idSet.m_InitDate.GetStatus(),m_InitDate.GetStatus(),idSet.m_InitDate.GetYear(), m_InitDate.GetYear());
}

BOOL CIDSet::Change_Pwd(const CString& strNewPwd)
{
	CString strSQL="update Books set ";
	BOOL IsFirst = TRUE;

	IsFirst = CDatabaseUtility::Generate_modify_string("Book_Password",m_password,strNewPwd,strSQL,IsFirst);

	if(!IsFirst)
	{
		CDatabaseUtility::Append_Condition_Str("Book_ID",strSQL,m_ID);
		TRACE("%s\n",strSQL);
		m_pDatabase->ExecuteSQL(strSQL);
		return TRUE;
	}
	TRACE("No any change....\n");
	return FALSE;
}
void CIDSet::RevertExist()
{
	CString strSQL;
	m_bExist = !m_bExist;
	strSQL.Format("update Books set Book_Exist=%d where Book_ID=\'%s\'",m_bExist,m_ID);
	TRACE("%s \n",strSQL);
	m_pDatabase->ExecuteSQL(strSQL);
}
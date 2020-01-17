// SubCountSet.cpp : implementation file
//

#include "stdafx.h"
#include "..\SmallHorse.h"
#include "SubCountInOneCountSet.h"
#include "CONVERTDATA.h"
#include "database_setup.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSubCountInOneCountSet

IMPLEMENT_DYNAMIC(CSubCountInOneCountSet, CRecordset)

CSubCountInOneCountSet::CSubCountInOneCountSet(const CString& strId,BOOL bNameOnly)
	: CRecordset(NULL)
{
	//{{AFX_FIELD_INIT(CSubCountInOneCountSet)
	m_MainId = strId;
	if(bNameOnly)
		m_nFields = 1;
	else
		m_nFields = 2;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CSubCountInOneCountSet::GetDefaultConnect()
{
	return DATA_SOURCE_NAME_ODBC;
}

CString CSubCountInOneCountSet::GetDefaultSQL()
{
	CString strSql;
	CString strSum;
	if(m_nFields == 2)
	{
		strSql.Format("Select distinct SubCountID,sum(Oper) as Remains  from Items where Item_Book_ID=\'%s\' group by SubCountID",m_MainId);
	}
	else
	{
		strSql.Format("Select distinct SubCountID from Items where Item_Book_ID=\'%s\'",m_MainId);
	}
	return strSql;
}

void CSubCountInOneCountSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CSubCountInOneCountSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[SubCountID]"), m_Sub_Count_ID);
	if(m_nFields==2)
	{
		RFX_Text(pFX, _T("[Remains]"), m_Remains);
	}
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CSubCountInOneCountSet diagnostics

#ifdef _DEBUG
void CSubCountInOneCountSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSubCountInOneCountSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG

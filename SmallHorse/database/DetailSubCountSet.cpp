// SubCountSet.cpp : implementation file
//

#include "stdafx.h"
#include "..\SmallHorse.h"
#include "DetailSubCountSet.h"
#include "CONVERTDATA.h"
#include "database_setup.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDetailSubCountSet

IMPLEMENT_DYNAMIC(CDetailSubCountSet, CRecordset)

CDetailSubCountSet::CDetailSubCountSet(const CString& strFilter)
	: CRecordset(NULL)
{
	//{{AFX_FIELD_INIT(CDetailSubCountSet)
	//m_strFilter = strFilter;
	m_nFields = 11;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CDetailSubCountSet::GetDefaultConnect()
{
	return DATA_SOURCE_NAME_ODBC;
}

CString CDetailSubCountSet::GetDefaultSQL()
{
    return _T(SQL_OPEN_ALL_ACTIVE_SUB_COUNT);
    //return m_strFilter;
}

void CDetailSubCountSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CDetailSubCountSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
    RFX_Text(pFX, _T("[Book_Bank]"), m_strBank);
    RFX_Text(pFX, _T("[Book_Owner]"), m_strOwner);
    RFX_Text(pFX, _T("[Book_ID]"), m_strBookId);
    RFX_Int(pFX, _T("[Index]"), m_nId);
    RFX_Single(pFX, _T("[Oper]"), m_fValue);
    RFX_Date(pFX, _T("[OperDate]"), m_dateStart);
    RFX_Date(pFX, _T("[DueDate]"), m_dateEnd);
    RFX_Single(pFX, _T("[Rate]"), m_fRate);
    RFX_Text(pFX, _T("[PERIOD]"), m_strTimeSpan);
    RFX_Text(pFX, _T("[Comment]"), m_strComment);
    RFX_Bool(pFX, _T("[Closed]"), m_bClosed);
	//}}AFX_FIELD_MAP

}

//#define SQL_OPEN_ALL_ACTIVE_SUB_COUNT         _T("select Books.Book_Bank, Books.Book_Owner, Books.Book_ID, Items.Index,\
//                                       Items.Oper, Items.OperDate,FixedDeposit.DueDate, FixedDeposit.Rate, FixedDeposit.PERIOD,FixedDeposit.Comment \
//                                       from Books,FixedDeposit,Items \
//                                       where FixedDeposit.ID = Items.Index and \
//                                       Items.Item_Book_ID = Books.Book_ID")

/////////////////////////////////////////////////////////////////////////////
// CDetailSubCountSet diagnostics

#ifdef _DEBUG
void CDetailSubCountSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CDetailSubCountSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG

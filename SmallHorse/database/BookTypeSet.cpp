// BookTypeSet.cpp : implementation file
//

#include "stdafx.h"
#include "..\SmallHorse.h"
#include "BookTypeSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBookTypeSet

IMPLEMENT_DYNAMIC(CBookTypeSet, CRecordset)

CBookTypeSet::CBookTypeSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CBookTypeSet)
	m_ID = 0;
	m_Type = _T("");
	m_nFields = 2;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
    m_strSort=_T("ID");
}


CString CBookTypeSet::GetDefaultConnect()
{
	return DATA_SOURCE_NAME_ODBC;
}

CString CBookTypeSet::GetDefaultSQL()
{
	return _T("[BookType]");
}

void CBookTypeSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CBookTypeSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Int(pFX, _T("[ID]"), m_ID);
	RFX_Text(pFX, _T("[Type]"), m_Type);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CBookTypeSet diagnostics

#ifdef _DEBUG
void CBookTypeSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CBookTypeSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


/*******************************************
    Function Name :	 
    Create by     :	  Qiu Simon
    Input         :   
    Output        :   
    Description   :   
    Date          :   1/10/2011 5:08:12 PM
********************************************/
CString CBookTypeSet::GetBookType(int nType)
{
    if(!IsOpen())
    {
        Open();
    }
    if(GetRecordCount()==0)
    {
        return "wrong set";
    }
    MoveFirst();
    while(!IsEOF())
    {
        if(m_ID == nType)
        {
            return m_Type;
        }
        MoveNext();
    }
    return "wrong type";

}

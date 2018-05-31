// TypeSet.cpp : implementation file
//

#include "stdafx.h"
#include "..\SmallHorse.h"
#include "TypeSet.h"
#include "database_setup.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTypeSet

IMPLEMENT_DYNAMIC(CTypeSet, CRecordset)

CTypeSet::CTypeSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CTypeSet)
	m_typeid = 0;
	m_strType = _T("");
	m_nFields = 2;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CTypeSet::GetDefaultConnect()
{
	return DATA_SOURCE_NAME_ODBC;
}

CString CTypeSet::GetDefaultSQL()
{
	return _T("[ItemType]");
}

void CTypeSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CTypeSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Byte(pFX, _T("[ID]"), m_typeid);
	RFX_Text(pFX, _T("[Type]"), m_strType);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CTypeSet diagnostics

#ifdef _DEBUG
void CTypeSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CTypeSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG

BYTE CTypeSet::GetTypeIndex(const CString &strType)
{
    if(!IsBOF())
    {
        MoveFirst();
    }
    while(!IsEOF())
	{
		if(strType==m_strType)
        {
			return m_typeid;
        }
		MoveNext();
	}
	return -1;
}

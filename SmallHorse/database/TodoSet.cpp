// IDSet.cpp : implementation file
//

#include "stdafx.h"
#include "..\SmallHorse.h"

#include "database_setup.h"
#include "todoset.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTodoSet


IMPLEMENT_DYNAMIC(CTodoSet, CRecordset)

CTodoSet::CTodoSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CTodoSet)
	m_id = 0;
	m_body = _T("");

	m_nFields = 2;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CTodoSet::GetDefaultConnect()
{
	return DATA_SOURCE_NAME_ODBC;
}

CString CTodoSet::GetDefaultSQL()
{
	return _T("[todo_list]");
}


void CTodoSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CTodoSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Int(pFX, _T("[id]"), m_id);
	RFX_Text(pFX, _T("[todo]"), m_body);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CTodoSet diagnostics

#ifdef _DEBUG
void CTodoSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CTodoSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


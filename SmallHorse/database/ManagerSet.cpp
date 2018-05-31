// ManagerSet.cpp : implementation file
//

#include "stdafx.h"
#include "..\SmallHorse.h"
#include "ManagerSet.h"
#include "database_setup.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CManagerSet

IMPLEMENT_DYNAMIC(CManagerSet, CRecordset)

CManagerSet::CManagerSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CManagerSet)
	m_pwd = _T("");
	m_name = _T("");
	m_nFields = 2;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CManagerSet::GetDefaultConnect()
{
	return DATA_SOURCE_NAME_ODBC;
}

CString CManagerSet::GetDefaultSQL()
{
	return _T("[Members]");
}

void CManagerSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CManagerSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[Password]"), m_pwd);
	RFX_Text(pFX, _T("[Name]"), m_name);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CManagerSet diagnostics

#ifdef _DEBUG
void CManagerSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CManagerSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG

int CManagerSet::Verify(CString strName, CString strPwd)
{
    if(!IsBOF())
    {
        MoveFirst();
    }
    while(!IsEOF())
	{
		if(strName==m_name&&strPwd==m_pwd)
			return 0;
		MoveNext();
	}
	return -1;

}


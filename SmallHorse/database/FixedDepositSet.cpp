// testodbcSet.cpp : CFixedDepositSet 类的实现
//

#include "stdafx.h"
#include "..\SmallHorse.h"
#include "FixedDepositSet.h"
#include "database_setup.h"
#include "smartdate.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFixedDepositSet 实现

// 代码生成在 2025年3月9日, 14:41

IMPLEMENT_DYNAMIC(CFixedDepositSet, CRecordset)

CFixedDepositSet::CFixedDepositSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_ID = 0;
	m_StartDate;
	m_DueDate;
	m_Rate = 0.0;
	m_Comment = L"";
	m_SubCountTableId = 0;
	m_nFields = 7;
	m_nDefaultType = dynaset;
}
//#error Security Issue: The connection string may contain a password
// 此连接字符串中可能包含明文密码和/或其他重要
// 信息。请在查看完此连接字符串并找到所有与安全
// 有关的问题后移除 #error。可能需要将此密码存
// 储为其他格式或使用其他的用户身份验证。
CString CFixedDepositSet::GetDefaultConnect()
{
    return DATA_SOURCE_NAME_ODBC;
}

CString CFixedDepositSet::GetDefaultSQL()
{
	return _T("[FixedDeposit]");
}

void CFixedDepositSet::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() 和 RFX_Int() 这类宏依赖的是
// 成员变量的类型，而不是数据库字段的类型。
// ODBC 尝试自动将列值转换为所请求的类型
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Date(pFX, _T("[StartDate]"), m_StartDate);
	RFX_Date(pFX, _T("[DueDate]"), m_DueDate);
	RFX_Single(pFX, _T("[Rate]"), m_Rate);
	RFX_Text(pFX, _T("[Comment]"), m_Comment);
	RFX_Long(pFX, _T("[SubCountTableId]"), m_SubCountTableId);
    RFX_Text(pFX, _T("[PERIOD]"), m_Period);  // 注意字段名标识符

}
/////////////////////////////////////////////////////////////////////////////
// CFixedDepositSet 诊断

#ifdef _DEBUG
void CFixedDepositSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CFixedDepositSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


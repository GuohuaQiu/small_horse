// CBaseRecordset.cpp - 修正版本
#include "stdafx.h"
#include "BaseRecordset.h"
#include "DatabaseManager.h"

IMPLEMENT_DYNAMIC(CBaseRecordset, CRecordset)

CBaseRecordset::CBaseRecordset(CDatabase* pDatabase, BOOL bShareDatabaseConnection, UINT nOpenType, DWORD dwOptions)
    : CRecordset(pDatabase)
    , m_eState(RS_CLOSED)
    , m_bDirty(FALSE)
    , m_bShareDatabaseConnection(bShareDatabaseConnection)
    , m_strLastSQL(_T(""))
{
    m_nDefaultType = nOpenType;
    m_dwOptions = dwOptions;
}

CBaseRecordset::~CBaseRecordset()
{
    // 确保关闭记录集
    if (IsOpen())
    {
        try
        {
            Close();
        }
        catch(...)
        {
            // 忽略析构时的异常
        }
    }
    if(m_bShareDatabaseConnection == FALSE && m_pDatabase != NULL)
    {
        // 如果不共享连接，关闭并删除数据库连接
        try
        {
            if (m_pDatabase->IsOpen())
            {
                m_pDatabase->Close();
            }
        }
        catch(...)
        {
            // 忽略异常
        }
        delete m_pDatabase;
        m_pDatabase = NULL;
    }
}

// 核心：实现final的GetDefaultConnect，返回空字符串
CString CBaseRecordset::GetDefaultConnect() const
{
    // 永远返回空字符串，连接由外部管理
    return _T("");
}

BOOL CBaseRecordset::OpenEx(const CString& strSQL, DWORD dwOptions)
{
    // 确保有数据库连接
    if (!EnsureDatabaseConnection())
    {
        TRACE(_T("无法获取数据库连接\n"));
        return FALSE;
    }
    
    // 调用前置处理
    if (!OnBeforeOpen())
    {
        TRACE(_T("OnBeforeOpen返回FALSE\n"));
        return FALSE;
    }
    
    m_strLastSQL = strSQL;
    
    try
    {
        BOOL bSuccess = FALSE;
        
        if (strSQL.IsEmpty())
        {
            bSuccess = Open(CRecordset::snapshot, NULL, CRecordset::readOnly);
        }
        else
        {
            bSuccess = Open(CRecordset::snapshot, strSQL, CRecordset::readOnly);
        }
        
        if (bSuccess)
        {
            m_eState = RS_OPEN;
            OnAfterOpen();
        }
        else
        {
            m_eState = RS_ERROR;
        }
        
        return bSuccess;
    }
    catch(CDBException* e)
    {
        m_eState = RS_ERROR;
        
        CString strError;
        strError.Format(_T("打开记录集失败: %s"), e->m_strError);
        TRACE(_T("%s\n"), strError);
        
        e->Delete();
        return FALSE;
    }
}

BOOL CBaseRecordset::RefreshData()
{
    if (!IsOpen())
    {
        return FALSE;
    }
    
    // 保存当前位置
    CDBVariant varBookmark;
    if (CanBookmark())
    {
        SaveCurrentPosition(varBookmark);
    }
    
    BOOL bSuccess = FALSE;
    
    try
    {
        // 使用Requery而不是重新打开
        bSuccess = Requery();
        
        if (bSuccess && IsValidBookmark(varBookmark))
        {
            RestorePosition(varBookmark);
        }
    }
    catch(CDBException* e)
    {
        CString strError;
        strError.Format(_T("刷新数据失败: %s"), e->m_strError);
        TRACE(_T("%s\n"), strError);
        e->Delete();
    }
    
    return bSuccess;
}

BOOL CBaseRecordset::ForceRefresh()
{
    if (!IsOpen())
    {
        return FALSE;
    }
    
    // 完全关闭并重新打开
    Close();
    
    // 给数据库一点时间释放资源
    Sleep(50);
    
    return OpenEx(m_strLastSQL, m_dwOptions);
}

BOOL CBaseRecordset::Reopen()
{
    if (IsOpen())
    {
        Close();
    }
    
    return OpenEx(m_strLastSQL, m_dwOptions);
}

long CBaseRecordset::GetRecordCountEx()
{
    if (!IsOpen())
    {
        return 0;
    }
    
    // 保存当前位置
    CDBVariant varBookmark;
    if (CanBookmark())
    {
        SaveCurrentPosition(varBookmark);
    }
    
    // 移动到开始
    MoveFirst();
    
    long nCount = 0;
    while (!IsEOF())
    {
        nCount++;
        MoveNext();
    }
    
    // 恢复位置
    if (IsValidBookmark(varBookmark))
    {
        RestorePosition(varBookmark);
    }
    
    return nCount;
}

BOOL CBaseRecordset::EnsureDatabaseConnection()
{
    // 如果已经有数据库连接，直接返回
    if (m_pDatabase != NULL && m_pDatabase->IsOpen())
    {
        return TRUE;
    }
    if (m_bShareDatabaseConnection)
    {
        // 尝试从数据库管理器获取连接
        m_pDatabase = CDatabaseManager::GetInstance()->GetConnection();
    }
    else
    {
        // 尝试从数据库管理器获取连接
        m_pDatabase = CDatabaseManager::NewConnection();
    }
    if (m_pDatabase == NULL)
    {
        TRACE(_T("数据库管理器返回NULL连接\n"));
        return FALSE;
    }

    if (!m_pDatabase->IsOpen())
    {
        TRACE(_T("获取的数据库连接未打开\n"));
        return FALSE;
    }
    // 如果不共享连接，直接返回TRUE
    return TRUE;
}

void CBaseRecordset::UpdateState()
{
    if (!IsOpen())
    {
        m_eState = RS_CLOSED;
    }
    else if (IsEOF())
    {
        m_eState = RS_EOF;
    }
    else
    {
        m_eState = RS_OPEN;
    }
}

// ?? 书签封装函数实现
BOOL CBaseRecordset::SaveCurrentPosition(CDBVariant& varBookmark)
{
    if (!IsOpen())
    {
        TRACE(_T("记录集未打开，无法保存位置\n"));
        return FALSE;
    }
    
    if (!CanBookmark())
    {
        TRACE(_T("记录集不支持书签\n"));
        varBookmark.Clear();
        return FALSE;
    }
    
    try
    {
        // 调用基类的GetBookmark
        CRecordset::GetBookmark(varBookmark);
        return TRUE;
    }
    catch(CDBException* e)
    {
        TRACE(_T("保存书签失败: %s\n"), e->m_strError);
        varBookmark.Clear();
        e->Delete();
        return FALSE;
    }
}

BOOL CBaseRecordset::RestorePosition(const CDBVariant& varBookmark)
{
    if (!IsOpen())
    {
        TRACE(_T("记录集未打开，无法恢复位置\n"));
        return FALSE;
    }
    
    if (!CanBookmark())
    {
        TRACE(_T("记录集不支持书签\n"));
        return FALSE;
    }
    
    if (!IsValidBookmark(varBookmark))
    {
        TRACE(_T("无效的书签\n"));
        return FALSE;
    }
    
    try
    {
        // 调用基类的SetBookmark
        CRecordset::SetBookmark(varBookmark);
        return TRUE;
    }
    catch(CDBException* e)
    {
        TRACE(_T("恢复书签失败: %s\n"), e->m_strError);
        e->Delete();
        
        // 尝试恢复到开头
        try
        {
            MoveFirst();
        }
        catch(...)
        {
            // 忽略异常
        }
        
        return FALSE;
    }
}

BOOL CBaseRecordset::IsValidBookmark(const CDBVariant& varBookmark) const
{
    // 检查书签是否有效
    if (varBookmark.m_dwType == DBVT_NULL)
    {
        return FALSE;
    }
    
    // 可以根据需要添加更多验证
    return TRUE;
}
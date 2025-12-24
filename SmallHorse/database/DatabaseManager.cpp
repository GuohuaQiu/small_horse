// DatabaseManager.cpp
#include "stdafx.h"
#include "DatabaseManager.h"
#include <windows.h>
#include <shlwapi.h>
#pragma comment(lib, "shlwapi.lib")

#ifdef _DEBUG
#define DB_GROUP "0.1"
#else
#define DB_GROUP "1.0"
#endif

// 初始化静态成员
CDatabaseManager* CDatabaseManager::m_pInstance = nullptr;
std::mutex CDatabaseManager::m_mutex;

CDatabaseManager* CDatabaseManager::GetInstance()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if (m_pInstance == nullptr)
    {
        m_pInstance = new CDatabaseManager();
    }
    return m_pInstance;
}

void CDatabaseManager::Release()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if (m_pInstance != nullptr)
    {
        delete m_pInstance;
        m_pInstance = nullptr;
    }
}

// CDatabaseManager::CDatabaseManager()
//     : m_pDatabase(nullptr)
//     , m_strDbPath(_T("D:\\guohua\\finance\\test.mdb"))
//     , m_strLastError(_T(""))
// {
//     尝试从配置文件读取数据库路径
//     TCHAR szPath[MAX_PATH] = {0};
//     GetModuleFileName(nullptr, szPath, MAX_PATH);
//     PathRemoveFileSpec(szPath);
    
//     CString strIniPath = CString(szPath) + _T("\\config.ini");
//     TCHAR szDbPath[MAX_PATH] = {0};
    
//     GetPrivateProfileString(_T("Database"), _T("DBQ"), 
//                             _T(""), szDbPath, MAX_PATH, strIniPath);
//     m_strDbPath = szDbPath;
// }


CString CDatabaseManager::m_strDbPath = _T("");
void CDatabaseManager::LoadEnvSetting()
{
    TCHAR szExePath[MAX_PATH] = {0};
    GetModuleFileName(nullptr, szExePath, MAX_PATH);
    PathRemoveFileSpec(szExePath);

    CString strIniPath = CString(szExePath) + _T("\\config.ini");
    TCHAR szPath[MAX_PATH] = {0};

    // 读取配置
    GetPrivateProfileString(DB_GROUP, _T("DBQ"),
                            _T(""), szPath, MAX_PATH, strIniPath);

    m_strDbPath = szPath;
    m_strDbPath.Trim();

    if (!m_strDbPath.IsEmpty())
    {
        TRACE(_T("从[%s]节加载数据库路径: %s\n"), DB_GROUP, m_strDbPath);
    }
    else
    {
        TRACE(_T("未找到[%s]节的PATH配置\n"), DB_GROUP);
    }
}
CDatabaseManager::CDatabaseManager()
    : m_pDatabase(nullptr)
    , m_strLastError(_T(""))
{
}







CDatabaseManager::~CDatabaseManager()
{
    Disconnect();
}

BOOL CDatabaseManager::SetDatabasePath(const CString& strPath)
{
    if (strPath.IsEmpty())
        return FALSE;
        
    // 检查文件是否存在
    if (GetFileAttributes(strPath) == INVALID_FILE_ATTRIBUTES)
    {
        //m_strLastError = _T("数据库文件不存在: ") + strPath;
        return FALSE;
    }
    
    m_strDbPath = strPath;
    
    // 保存到配置文件
    TCHAR szPath[MAX_PATH] = {0};
    GetModuleFileName(nullptr, szPath, MAX_PATH);
    PathRemoveFileSpec(szPath);
    
    CString strIniPath = CString(szPath) + _T("\\config.ini");
    WritePrivateProfileString(_T("Database"), _T("Path"), 
                             m_strDbPath, strIniPath);
    
    return TRUE;
}

BOOL CDatabaseManager::InitializeDatabase()
{
    if (m_pDatabase != nullptr)
    {
        try
        {
            if (m_pDatabase->IsOpen())
                m_pDatabase->Close();
        }
        catch(...)
        {
            // 忽略异常
        }
        delete m_pDatabase;
        m_pDatabase = nullptr;
    }
    
    m_pDatabase = new CDatabase();
    return TRUE;
}

CString CDatabaseManager::BuildConnectionString(BOOL bExclusive, BOOL bReadOnly)
{
    CString strConnect;
    
    strConnect.Format(
        _T("DRIVER={Microsoft Access Driver (*.mdb, *.accdb)};")
        _T("DBQ=%s;")
        _T("DriverId=25;")
        _T("FIL=MS Access;")
        _T("MaxBufferSize=2048;")
        _T("PageTimeout=5;")
        _T("PWD=rgb;")
        _T("UID=admin;")
        _T("READONLY=%s;")
        _T("EXCLUSIVE=%s;"),
        m_strDbPath,
        bReadOnly ? _T("TRUE") : _T("FALSE"),
        bExclusive ? _T("TRUE") : _T("FALSE")
    );
    
    return strConnect;
}

BOOL CDatabaseManager::Connect(const CString& strDbPath)
{
    if (!strDbPath.IsEmpty())
    {
        if (!SetDatabasePath(strDbPath))
            return FALSE;
    }
    
    if (m_strDbPath.IsEmpty())
    {
        m_strLastError = _T("数据库路径未设置");
        return FALSE;
    }
    
    if (m_pDatabase != nullptr && m_pDatabase->IsOpen())
    {
        return TRUE;  // 已经连接
    }
    
    if (!InitializeDatabase())
    {
        m_strLastError = _T("初始化数据库失败");
        return FALSE;
    }
    
    try
    {
        CString strConnect = BuildConnectionString();
        
        if (!m_pDatabase->OpenEx(strConnect, CDatabase::noOdbcDialog))
        {
            m_strLastError = _T("无法打开数据库连接");
            return FALSE;
        }
        
        return TRUE;
    }
    catch(CDBException* e)
    {
        m_strLastError = e->m_strError;
        e->Delete();
        return FALSE;
    }
}

void CDatabaseManager::Disconnect()
{
    if (m_pDatabase != nullptr)
    {
        try
        {
            if (m_pDatabase->IsOpen())
                m_pDatabase->Close();
        }
        catch(...)
        {
            // 忽略异常
        }
        delete m_pDatabase;
        m_pDatabase = nullptr;
    }
}

BOOL CDatabaseManager::Reconnect()
{
    Disconnect();
    return Connect();
}

BOOL CDatabaseManager::IsConnected() const
{
    return m_pDatabase != nullptr && m_pDatabase->IsOpen();
}

CDatabase* CDatabaseManager::GetConnection()
{
    if (!IsConnected())
    {
        if (!Connect())
        {
            return nullptr;
        }
    }
    return m_pDatabase;
}
CDatabase* CDatabaseManager::NewConnection()
{
    if (m_strDbPath.IsEmpty())
    {
        TRACE( _T("数据库路径未设置"));
        return nullptr;
    }
    
    try
    {
        CDatabase* pdb = new CDatabase();
        CString strConnect = BuildConnectionString(TRUE,TRUE);
        
        if (!pdb->OpenEx(strConnect, CDatabase::noOdbcDialog))
        {
            TRACE( _T("无法打开数据库连接"));
            delete pdb;
            return nullptr;
        }
        
        return pdb;
    }
    catch(CDBException* e)
    {
        TRACE(e->m_strError);
        e->Delete();
        return FALSE;
    }
}

BOOL CDatabaseManager::ExecuteSQL(const CString& strSQL)
{
    CDatabase* pDb = GetConnection();
    if (pDb == nullptr)
        return FALSE;
        
    try
    {
        pDb->ExecuteSQL(strSQL);
        return TRUE;
    }
    catch(CDBException* e)
    {
        m_strLastError = e->m_strError;
        e->Delete();
        return FALSE;
    }
}

BOOL CDatabaseManager::BeginTransaction()
{
    CDatabase* pDb = GetConnection();
    if (pDb == nullptr)
        return FALSE;
        
    try
    {
        pDb->BeginTrans();
        return TRUE;
    }
    catch(...)
    {
        return FALSE;
    }
}

BOOL CDatabaseManager::CommitTransaction()
{
    CDatabase* pDb = GetConnection();
    if (pDb == nullptr)
        return FALSE;
        
    try
    {
        pDb->CommitTrans();
        return TRUE;
    }
    catch(...)
    {
        return FALSE;
    }
}

BOOL CDatabaseManager::RollbackTransaction()
{
    CDatabase* pDb = GetConnection();
    if (pDb == nullptr)
        return FALSE;
        
    try
    {
        pDb->Rollback();
        return TRUE;
    }
    catch(...)
    {
        return FALSE;
    }
}

BOOL CDatabaseManager::TestConnection()
{
    if (!IsConnected())
    {
        if (!Connect())
            return FALSE;
    }
    
    // 执行一个简单的测试查询
    try
    {
        CDatabase* pDb = GetConnection();
        CRecordset rs(pDb);
        
        if (rs.Open(CRecordset::forwardOnly, _T("SELECT 1"), CRecordset::readOnly))
        {
            rs.Close();
            return TRUE;
        }
        return FALSE;
    }
    catch(CDBException* e)
    {
        m_strLastError = e->m_strError;
        e->Delete();
        return FALSE;
    }
}
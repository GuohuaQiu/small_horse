// DatabaseManager.h
#pragma once
#include <afxdb.h>
#include <string>
#include <mutex>

class CDatabaseManager
{
private:
    static CDatabaseManager* m_pInstance;
    static std::mutex m_mutex;
    
    CDatabase* m_pDatabase;
    CString m_strDbPath;
    CString m_strLastError;
    
    // 私有构造函数，单例模式
    CDatabaseManager();
    
    // 禁止拷贝
    CDatabaseManager(const CDatabaseManager&) = delete;
    CDatabaseManager& operator=(const CDatabaseManager&) = delete;
    
    BOOL InitializeDatabase();
    CString BuildConnectionString() const;
    
public:
    ~CDatabaseManager();
    
    // 单例获取
    static CDatabaseManager* GetInstance();
    static void Release();
    
    // 连接管理
    BOOL Connect(const CString& strDbPath = _T(""));
    void Disconnect();
    BOOL Reconnect();
    BOOL IsConnected() const;
    
    // 获取连接
    CDatabase* GetConnection();
    
    // 获取/设置数据库路径
    CString GetDatabasePath() const { return m_strDbPath; }
    BOOL SetDatabasePath(const CString& strPath);
    
    // 执行SQL
    BOOL ExecuteSQL(const CString& strSQL);
    
    // 获取最后错误
    CString GetLastError() const { return m_strLastError; }
    
    // 事务支持
    BOOL BeginTransaction();
    BOOL CommitTransaction();
    BOOL RollbackTransaction();
    
    // 连接测试
    BOOL TestConnection();
};
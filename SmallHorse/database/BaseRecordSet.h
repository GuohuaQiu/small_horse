// CBaseRecordset.h - 修正版本
#pragma once
#include <afxdb.h>
#include <string>

class CBaseRecordset : public CRecordset
{
    DECLARE_DYNAMIC(CBaseRecordset)
    
public:
    // 记录集状态
    enum RecordsetState
    {
        RS_CLOSED = 0,
        RS_OPEN,
        RS_EOF,
        RS_ERROR
    };
    
    // 构造函数
    CBaseRecordset(CDatabase *pDatabase = NULL, BOOL bShareDatabaseConnection = TRUE,
                   UINT nOpenType = dynaset,
                   DWORD dwOptions = none);
    virtual ~CBaseRecordset();
    
    // 核心修改：将GetDefaultConnect设为final，禁止子类覆盖
    virtual CString GetDefaultConnect() const final;
    
    // 添加OpenEx函数
    BOOL OpenEx(const CString& strSQL = _T(""), DWORD dwOptions = none);
    
    // 强制刷新功能
    BOOL RefreshData();
    BOOL ForceRefresh();
    
    // 便捷功能
    BOOL Reopen();
    long GetRecordCountEx();
    BOOL IsDataDirty() const { return m_bDirty; }
    
    // ?? 书签封装函数（不是重写基类的GetBookmark/SetBookmark）
    BOOL SaveCurrentPosition(CDBVariant& varBookmark);
    BOOL RestorePosition(const CDBVariant& varBookmark);
    BOOL IsValidBookmark(const CDBVariant& varBookmark) const;
    
    // 状态管理
    RecordsetState GetState() const { return m_eState; }
    BOOL IsOpen() const { return m_eState == RS_OPEN; }
    void SetShareDatabase(BOOL bShare) {
        m_bShareDatabaseConnection = bShare;
    }
    
protected:
    // 子类需要重写的函数
    virtual CString GetTableName() const = 0;
    virtual int GetFieldCount() const = 0;
    
    // 可选的虚函数
    virtual BOOL OnBeforeOpen() { return TRUE; }
    virtual BOOL OnAfterOpen() { return TRUE; }
    virtual BOOL OnBeforeClose() { return TRUE; }
    virtual BOOL OnAfterClose() { return TRUE; }
    
    virtual BOOL OnBeforeAddNew() { return TRUE; }
    virtual BOOL OnAfterAddNew(BOOL bSuccess) { return bSuccess; }
    
    virtual BOOL OnBeforeEdit() { return TRUE; }
    virtual BOOL OnAfterEdit(BOOL bSuccess) { return bSuccess; }
    
    virtual BOOL OnBeforeUpdate() { return TRUE; }
    virtual BOOL OnAfterUpdate(BOOL bSuccess) { return bSuccess; }
    
    virtual BOOL OnBeforeDelete() { return TRUE; }
    virtual BOOL OnAfterDelete(BOOL bSuccess) { return bSuccess; }
    
    // 内部状态
    RecordsetState m_eState;
    BOOL m_bDirty;
    BOOL m_bShareDatabaseConnection = TRUE;
    
private:
    // 禁止拷贝和赋值
    CBaseRecordset(const CBaseRecordset&) = delete;
    CBaseRecordset& operator=(const CBaseRecordset&) = delete;
    
    // 内部辅助函数
    BOOL EnsureDatabaseConnection();
    void UpdateState();
    
    CString m_strLastSQL;
};
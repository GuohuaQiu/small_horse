#include "stdafx.h"
#include "CDbConfigure.h"

CDbConfigure::CDbConfigure()
{
}

#define MAXPATH 256

CString GetIniFile()
{
    TCHAR path[MAX_PATH];
    ZeroMemory(path, MAX_PATH);
    GetModuleFileName(NULL, path, MAX_PATH); 
    CString strPath = _T(path);
    int pos = strPath.ReverseFind('\\');
    strPath = strPath.Left(pos+1); 
    strPath += _T("config.ini"); // Ensure _T macro is used for consistency
    TRACE(strPath);
    return strPath;
}

CString CDbConfigure::mStrDataSource = _T("");

// Helper to read string from INI
CString GetIniString(const CString& section, const CString& key, const CString& defaultVal, const CString& iniPath)
{
    TCHAR result[MAX_PATH];
    GetPrivateProfileString(section, key, defaultVal, result, MAX_PATH, iniPath);
    return CString(result);
}

#ifdef _DEBUG
#define DB_GROUP _T("0.1")
#else
#define DB_GROUP _T("1.0")
#endif

void CDbConfigure::OpenIni()
{
    CString IniFile = GetIniFile();
    CDbConfigure::mStrDataSource = _T("");
    
    // Read the database file path from INI (DBQ)
    // Assuming your INI has:
    // [1.0]
    // DBQ=C:\path\to\your\database.mdb
    CString strDBQ = GetIniString(DB_GROUP, _T("DBQ"), _T(""), IniFile);
    
    if (strDBQ.IsEmpty())
    {
        // Fallback or error handling if needed
        TRACE("Error: No DBQ found in config.ini\n");
        return;
    }

    // Construct DSN-less connection string for Microsoft Access Driver
    // Note: You might need to adjust the Driver string depending on installed drivers (e.g., *.mdb vs *.accdb)
    // For older .mdb files: "Driver={Microsoft Access Driver (*.mdb)};"
    // For newer .accdb files: "Driver={Microsoft Access Driver (*.mdb, *.accdb)};"
    
    CString strDriver = _T("Driver={Microsoft Access Driver (*.mdb, *.accdb)};");
    
    // Build the full connection string
    // Format: Driver={...};DBQ=c:\path\to\db.mdb;Uid=admin;Pwd=;
    
    CString strUid = GetIniString(DB_GROUP, _T("UID"), _T("admin"), IniFile);
    CString strPwd = GetIniString(DB_GROUP, _T("PWD"), _T(""), IniFile);

    CDbConfigure::mStrDataSource.Format(_T("%sDBQ=%s;Uid=%s;Pwd=%s;"), 
        strDriver, strDBQ, strUid, strPwd);

    TRACE(_T("Connection String: %s\n"), CDbConfigure::mStrDataSource);
}

CString CDbConfigure::GetDataSource()
{
    if (CDbConfigure::mStrDataSource.GetLength() == 0)
    {
        CDbConfigure::OpenIni();
    }
    return CDbConfigure::mStrDataSource;
}

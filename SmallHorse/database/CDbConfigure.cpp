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
    GetModuleFileName(NULL, path, MAX_PATH); // E:\Repository\Public\Debug\MainDisplay.exe
    CString strPath = _T(path);
    int pos = strPath.ReverseFind('\\');
    strPath = strPath.Left(pos+1); 
    strPath += L"config.ini";
    TRACE(strPath);
	return strPath;
}

CString CDbConfigure::mStrDataSource = _T("");

void _Append(CString &strConfig, char *sGroup, char *sField, const CString &IniFile)
{
	char cTarget[MAX_PATH];

    GetPrivateProfileString(sGroup, sField, "", cTarget, MAX_PATH, IniFile);
    strConfig += _T(sField);
    strConfig += _T("=");
    strConfig += _T(cTarget);
    strConfig += _T(";");
    // DSN = test;
}

#ifdef _DEBUG
#define DB_GROUP "0.1"
#else
#define DB_GROUP "1.0"
#endif

void CDbConfigure::OpenIni()
{
    CString IniFile = GetIniFile();
    CDbConfigure::mStrDataSource = _T("");
    CString &strSource = CDbConfigure::mStrDataSource;

    _Append(strSource, DB_GROUP, "DSN", IniFile);
    _Append(strSource, DB_GROUP, "DBQ", IniFile);
    _Append(strSource, DB_GROUP, "DriverId", IniFile);
    _Append(strSource, DB_GROUP, "FIL", IniFile);
    _Append(strSource, DB_GROUP, "MaxBufferSize", IniFile);
    _Append(strSource, DB_GROUP, "PageTimeout", IniFile);
    _Append(strSource, DB_GROUP, "PWD", IniFile);
    _Append(strSource, DB_GROUP, "UID", IniFile);
    TRACE(strSource);

    //	_T("DSN=test_a_64;DBQ=D:\\test\\bankbook_a.mdb;DriverId=25;FIL=MS Access;MaxBufferSize=2048;PageTimeout=5;PWD=rgb;UID=admin;");
}

CString CDbConfigure::GetDataSource()
{
    if (CDbConfigure::mStrDataSource.GetLength() == 0)
    {
        CDbConfigure::OpenIni();
    }
    return CDbConfigure::mStrDataSource;
}

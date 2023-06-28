#pragma once
class CDbConfigure
{
public:
    CDbConfigure();
    static CString GetDataSource();

    static void OpenIni();

private:
    static CString mStrDataSource;
    // look likes below:

    // _T("DSN=test;DBQ=C:\\guohua\\finance\\test.mdb;DriverId=25;FIL=MS Access;MaxBufferSize=2048;PageTimeout=5;PWD=rgb;UID=admin;")
};
// CmpListB.cpp: implementation of the CCmpListB class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CmpListB.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCmpListB::CCmpListB()
{

}

CCmpListB::~CCmpListB()
{

}

CString CCmpListB::GetDefaultConnect()
{
    return _T("DSN=test_b_64;DBQ=D:\\test\\bankbook_b.mdb;DriverId=25;FIL=MS Access;MaxBufferSize=2048;PageTimeout=5;PWD=rgb;UID=admin;");
}

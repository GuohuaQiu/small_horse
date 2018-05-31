// CmpListA.cpp: implementation of the CCmpListA class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "..\SmallHorse.h"
#include "CmpListA.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCmpListA::CCmpListA()
{

}

CCmpListA::~CCmpListA()
{

}


/*******************************************
    Function Name :	 
    Create by     :	  Qiu Simon
    Input         :   
    Output        :   
    Description   :   
    Date          :   12/24/2010 4:55:02 PM
********************************************/
CString CCmpListA::GetDefaultConnect()
{
    return _T("DSN=test_a_64;DBQ=D:\\test\\bankbook_a.mdb;DriverId=25;FIL=MS Access;MaxBufferSize=2048;PageTimeout=5;PWD=rgb;UID=admin;");
}

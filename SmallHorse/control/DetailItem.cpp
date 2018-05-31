// DetailItem.cpp: implementation of the CDetailItem class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "..\SmallHorse.h"
#include "DetailItem.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDetailItem::CDetailItem()
{
    

}

CDetailItem::~CDetailItem()
{

}


/*******************************************
    Function Name :	 
    Create by     :	  Qiu Simon
    Input         :   
    Output        :   
    Description   :   to assign value for m_varValue, 
                      but m_varValue is a protected value. 
                      so we use a sub class to get get the right.
    Date          :   2/12/2011 2:42:51 PM
********************************************/
void CDetailItem::EmptyItem()
{
    m_varValue.Clear();
}

// CmpListA.h: interface for the CCmpListA class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CMPLISTA_H__B5406341_3D93_4D7F_AACB_CA577A0FBCF8__INCLUDED_)
#define AFX_CMPLISTA_H__B5406341_3D93_4D7F_AACB_CA577A0FBCF8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ListSet.h"

class CCmpListA : public CListSet  
{
public:
	virtual CString GetDefaultConnect();
	CCmpListA();
	virtual ~CCmpListA();

};

#endif // !defined(AFX_CMPLISTA_H__B5406341_3D93_4D7F_AACB_CA577A0FBCF8__INCLUDED_)

// CmpListB.h: interface for the CCmpListB class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CMPLISTB_H__196C2414_9EE7_455D_A3F7_41BCFD0D5CBC__INCLUDED_)
#define AFX_CMPLISTB_H__196C2414_9EE7_455D_A3F7_41BCFD0D5CBC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ListSet.h"

class CCmpListB : public CListSet  
{
public:
	virtual CString GetDefaultConnect();
	CCmpListB();
	virtual ~CCmpListB();

};

#endif // !defined(AFX_CMPLISTB_H__196C2414_9EE7_455D_A3F7_41BCFD0D5CBC__INCLUDED_)

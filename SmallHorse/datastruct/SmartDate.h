// SmartData.h: interface for the CSmartDate class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SMARTDATA_H__03A9C745_0AA2_4E17_90D7_06F7C9D3818A__INCLUDED_)
#define AFX_SMARTDATA_H__03A9C745_0AA2_4E17_90D7_06F7C9D3818A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSmartDate  
{
public:
	bool operator ==(const CSmartDate &rSrc) const;
	bool operator <=(const CSmartDate &rSrc) const;
	bool operator >=(const CSmartDate &rSrc) const;
	bool operator >(const CSmartDate &rSrc) const;
	bool operator <(const CSmartDate &rSrc) const;
public:
	static void Test();
	int year;
	BYTE month;
	BYTE day;
	int  test;
	
	CSmartDate();
	CSmartDate(int y,int m, int d);
	CSmartDate(const COleDateTime& date);
	void Set(int y,int m, int d);
	virtual ~CSmartDate();
	static void Validate(int& y,int& m,int& d);
};

#endif // !defined(AFX_SMARTDATA_H__03A9C745_0AA2_4E17_90D7_06F7C9D3818A__INCLUDED_)

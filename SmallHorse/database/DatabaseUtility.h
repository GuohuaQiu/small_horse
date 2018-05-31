#pragma once

class CDatabaseUtility
{
public:
	CDatabaseUtility(void);
public:
	~CDatabaseUtility(void);
public:
	static CString GetDateTime(const COleDateTime& time);
	static BOOL IsTimeSame(const COleDateTime& a, const COleDateTime& b);
	static BOOL Generate_modify_Time(const CString& strFieldName,const COleDateTime& oldTime, const COleDateTime& newTime, CString& sqlCommandStr, BOOL isFirst);
	static BOOL Generate_modify_string(const CString& strFieldName,const CString& oldStr, const CString& newStr, CString& sqlCommandStr, BOOL isFirst);
	static BOOL Generate_modify_string(const CString& strFieldName,const CString& newStr, CString& sqlCommandStr);
	static BOOL Generate_modify_int(const CString& strFieldName,int oldValue, int newValue, CString& sqlCommandStr, BOOL isFirst);
	static BOOL Generate_modify_int(const CString& strFieldName,int newValue, CString& sqlCommandStr);
	static BOOL Generate_modify_float(const CString& strFieldName,float oldValue, float newValue, CString& sqlCommandStr, BOOL isFirst);
	static BOOL Append_Condition_Str(const CString& strFieldName, CString& sqlCommandStr, const CString& strValue);
	static BOOL Append_Condition_Int(const CString& strFieldName, CString& sqlCommandStr, int iValue);
	static BOOL Append_Condition_Int_Array(const CString& strFieldName, CString& sqlCommandStr, const CDWordArray& dbArray, int count);
};

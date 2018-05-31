#include "StdAfx.h"
#include "DatabaseUtility.h"

CDatabaseUtility::CDatabaseUtility(void)
{
}

CDatabaseUtility::~CDatabaseUtility(void)
{
}

BOOL CDatabaseUtility::Generate_modify_string(const CString& strFieldName,const CString& oldStr, const CString& newStr, CString& sqlCommandStr, BOOL isFirst)
{
	if(oldStr != newStr)
	{
		if(!isFirst)
		{
			sqlCommandStr += ",";
		}
		CString strTemp;
		strTemp.Format("%s=\'%s\'",strFieldName,newStr);
		sqlCommandStr += strTemp;
		return FALSE;
	}
	return isFirst;
}
BOOL CDatabaseUtility::Generate_modify_string(const CString& strFieldName,const CString& newStr, CString& sqlCommandStr)
{
	CString strTemp;
	strTemp.Format("%s=\'%s\'",strFieldName,newStr);
	sqlCommandStr += strTemp;
	return FALSE;

}
CString CDatabaseUtility::GetDateTime(const COleDateTime& time)
{
	CString str;
	str=time.Format(_T("%Y-%m-%d %H:%M:%S"));
	return str;
}

BOOL CDatabaseUtility::IsTimeSame(const COleDateTime& a, const COleDateTime& b)
{
	if(a == b)
	{
		return TRUE;
	}
	TRACE("%d----%d  %d----%d   \n",a.GetStatus(),b.GetStatus(),a.GetYear(),b.GetYear());


	if(a.GetYear() != b.GetYear())
	{
		return FALSE;
	}
	if(a.GetMonth() != b.GetMonth())
	{
		return FALSE;
	}
	if(a.GetDay() != b.GetDay())
	{
		return FALSE;
	}
	if(a.GetHour() != b.GetHour())
	{
		return FALSE;
	}
	if(a.GetMinute() != b.GetMinute())
	{
		return FALSE;
	}
	if(a.GetSecond() != b.GetSecond())
	{
		return FALSE;
	}
	return TRUE;

}
BOOL CDatabaseUtility::Generate_modify_Time(const CString& strFieldName,const COleDateTime& oldTime, const COleDateTime& newTime, CString& sqlCommandStr, BOOL isFirst)
{
	if(!IsTimeSame(oldTime, newTime))
	{
		if(!isFirst)
		{
			sqlCommandStr += ",";
		}
		CString strTemp;
		strTemp.Format("%s=\'%s\'",strFieldName,GetDateTime(newTime));
		sqlCommandStr += strTemp;
		return FALSE;
	}
	return isFirst;
}

BOOL CDatabaseUtility::Generate_modify_int(const CString& strFieldName,int oldValue, int newValue, CString& sqlCommandStr, BOOL isFirst)
{
	if(oldValue != newValue)
	{
		if(!isFirst)
		{
			sqlCommandStr += ",";
		}
		CString strTemp;
		strTemp.Format("%s=\'%d\'",strFieldName,newValue);
		sqlCommandStr += strTemp;
		return FALSE;
	}
	return isFirst;
}
BOOL CDatabaseUtility::Generate_modify_int(const CString& strFieldName,int newValue, CString& sqlCommandStr)
{
	CString strTemp;
	strTemp.Format("%s=\'%d\'",strFieldName,newValue);
	sqlCommandStr += strTemp;
	return FALSE;

}
BOOL CDatabaseUtility::Generate_modify_float(const CString& strFieldName,float oldValue, float newValue, CString& sqlCommandStr, BOOL isFirst)
{
	if(oldValue != newValue)
	{
		if(!isFirst)
		{
			sqlCommandStr += ",";
		}
		CString strTemp;
		strTemp.Format("%s=\'%.6f\'",strFieldName,newValue);
		sqlCommandStr += strTemp;
		return FALSE;
	}
	return isFirst;
}
BOOL CDatabaseUtility::Append_Condition_Str(const CString& strFieldName, CString& sqlCommandStr, const CString& strValue)
{
	CString strTemp;
	strTemp.Format(" where %s=%s",strFieldName,strValue);
	sqlCommandStr += strTemp;
	return TRUE;
}
BOOL CDatabaseUtility::Append_Condition_Int(const CString& strFieldName, CString& sqlCommandStr, int iValue)
{
	CString strTemp;
	strTemp.Format(" where %s=%d",strFieldName,iValue);
	sqlCommandStr += strTemp;
	return TRUE;
}
BOOL CDatabaseUtility::Append_Condition_Int_Array(const CString& strFieldName, CString& sqlCommandStr, const CDWordArray& dbArray, int count)
{
	CString strTemp,strTemp2;
	strTemp.Format(" where %s in (",strFieldName);
	for(int i = 0;i<count;i++)
	{
		if(i>0)
		{
			strTemp += ",";
		}
		strTemp2.Format("%d",dbArray[i]);
		strTemp += strTemp2;
	}
	strTemp += ")";
	sqlCommandStr += strTemp;
	return TRUE;
}

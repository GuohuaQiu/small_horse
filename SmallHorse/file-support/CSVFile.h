// CSVFile.h: interface for the CCSVFile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CSVFILE_H__597D7C5B_8B7F_49F7_9A82_9956C6D31C09__INCLUDED_)
#define AFX_CSVFILE_H__597D7C5B_8B7F_49F7_9A82_9956C6D31C09__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "mailreportctrl.h"
class CCSVFile  
{
public:
	int Save(CMailReportCtrl* pReportCtrl,CString& strfile,BOOL bFailIfExist=FALSE);
    int Save(CListCtrl* pctrl,CString& strfile,BOOL bFailIfExist=FALSE);
	int SaveTo(CListCtrl* pctrl,BOOL bFailIfExist=FALSE);
    int SaveTo(CMailReportCtrl* pctrl,BOOL bFailIfExist=FALSE);
	CCSVFile();
	virtual ~CCSVFile();
protected:
	void WriteAString(CFile* pfile,TCHAR * pszStr,BOOL bLineEnd=FALSE);
	
};

#endif // !defined(AFX_CSVFILE_H__597D7C5B_8B7F_49F7_9A82_9956C6D31C09__INCLUDED_)

// GridHtmlExporter.h: interface for the CGridHtmlExporter class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRIDHTMLEXPORTER_H__65C39E52_FF4B_4E3E_B2A3_BAE212D1A2F8__INCLUDED_)
#define AFX_GRIDHTMLEXPORTER_H__65C39E52_FF4B_4E3E_B2A3_BAE212D1A2F8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CGridHtmlExporter  
{
public:
	int ExportTail();
	int CloseFile();
	int ExportLine(CString strDate,CString strMoney,CString strComment,UINT uBackColor);
	int ExportCheckLine(int nYear, int nMonth, const COleDateTime &timeBegin, const COleDateTime &timeEnd, const COleDateTime &timePay,float fUse,float fPay);
	CString m_strFileName;
	CFile   m_file;
	BOOL SetExportFile(LPCTSTR lpFileName);
	CGridHtmlExporter();
	virtual ~CGridHtmlExporter();

};

#endif // !defined(AFX_GRIDHTMLEXPORTER_H__65C39E52_FF4B_4E3E_B2A3_BAE212D1A2F8__INCLUDED_)

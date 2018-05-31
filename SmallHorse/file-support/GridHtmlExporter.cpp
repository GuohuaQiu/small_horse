// GridHtmlExporter.cpp: implementation of the CGridHtmlExporter class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "..\SmallHorse.h"
#include "GridHtmlExporter.h"
#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
TCHAR cHeader[]="<html><head><meta http-equiv=\"Content-Type\" content=\"text/html; charset=gb2312\">\r\n \
	   <title>月对帐单</title><style type=\"text/css\"> \r\n\
	   <!--body {background-color: #EFECDD;}td{ font-family:\"宋体\"; font-size:9pt; color=#666666;}.style9 {color: #000000}--></style></head> \
	   <body> \r\n \
	   <table width=\"760\" border=\"0\" align=\"center\" cellpadding=\"0\" cellspacing=\"1\" bgcolor=\"#EFECDD\">  \r\n";

CGridHtmlExporter::CGridHtmlExporter()
{

}

CGridHtmlExporter::~CGridHtmlExporter()
{
//    CloseFile();
}

BOOL CGridHtmlExporter::SetExportFile(LPCTSTR lpFileName)
{
	if(m_file.Open(lpFileName,CFile::modeCreate|CFile::modeReadWrite)) 
	{
		m_strFileName = lpFileName;
		m_file.Write(cHeader,_tcslen(cHeader));
		return TRUE;
	}
	return FALSE;
}

int CGridHtmlExporter::ExportLine(CString strDate, CString strMoney, CString strComment, UINT uBackColor)
{
	CString str;
	str.Format("<tr bgcolor=\"#%.6x\">\r\n",uBackColor);
	m_file.Write(str,str.GetLength());
    str.Format("<td height=\"26\" width=\"80\"><div align=\"center\" class=\"style9\">%s</div></td>\r\n",strDate);
	m_file.Write(str,str.GetLength());
    str.Format("<td width=\"80\"><div align=\"center\" class=\"style9\">%s</div></td>\r\n",strMoney);
	m_file.Write(str,str.GetLength());
    str.Format("<td width=\"180\"><div align=\"center\" class=\"style9\">%s</div></td>\r\n",strComment);
	
	m_file.Write(str,str.GetLength());
    str.Format("</tr>\r\n");
	m_file.Write(str,str.GetLength());
	return 1;
}



int CGridHtmlExporter::CloseFile()
{
    m_file.Close();
	return 1;
}

int CGridHtmlExporter::ExportTail()
{
	CString str;
	str.Format("</table></body></html>");
	m_file.Write(str,str.GetLength());
	return 1;
}


int CGridHtmlExporter::ExportCheckLine(int nYear, int nMonth, const COleDateTime &timeBegin, const COleDateTime &timeEnd, const COleDateTime &timePay,float fUse,float fPay)
{
	CString str;
	if(fabs(fUse + fPay)< 0.01) 
	{
		str.Format("<tr bgcolor=\"#35ff77\">\r\n");
	}
	else
	{
		str.Format("<tr bgcolor=\"#aa0000\">\r\n");
	}
	m_file.Write(str,str.GetLength());

    str.Format("<td height=\"26\" width=\"70\"><div align=\"center\" class=\"style9\">%.4d-%.2d</div></td>\r\n",nYear,nMonth);
	m_file.Write(str,str.GetLength());


    str.Format("<td height=\"26\" width=\"50\"><div align=\"center\" class=\"style9\">%.2f</div></td>\r\n",fUse);
	m_file.Write(str,str.GetLength());

    str.Format("<td height=\"26\" width=\"50\"><div align=\"center\" class=\"style9\">%.2f</div></td>\r\n",fPay);
	m_file.Write(str,str.GetLength());

	CString strTime = timeBegin.Format("%Y-%m-%d");
    str.Format("<td height=\"26\" width=\"50\"><div align=\"center\" class=\"style9\">%s</div></td>\r\n",strTime);
	m_file.Write(str,str.GetLength());

	strTime = timeEnd.Format("%Y-%m-%d");
    str.Format("<td height=\"26\" width=\"50\"><div align=\"center\" class=\"style9\">%s</div></td>\r\n",strTime);
	m_file.Write(str,str.GetLength());
	
	strTime = timePay.Format("%Y-%m-%d");
    str.Format("<td height=\"26\" width=\"50\"><div align=\"center\" class=\"style9\">%s</div></td>\r\n",strTime);
	m_file.Write(str,str.GetLength());
	
	

    str.Format("</tr>\r\n");
	m_file.Write(str,str.GetLength());


	return 1;
}
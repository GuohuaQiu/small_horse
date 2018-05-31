// HtmlRecordSet.cpp : implementation file
//

#include "stdafx.h"
#include "..\SmallHorse.h"
#include "HtmlRecordSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CHtmlRecordSet

IMPLEMENT_DYNAMIC(CHtmlRecordSet, CRecordset)

CHtmlRecordSet::CHtmlRecordSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CHtmlRecordSet)
	m_nFields = 0;
	//}}AFX_FIELD_INIT
//	m_nDefaultType = dynaset;
    m_nDefaultType = snapshot;
}

/////////////////////////////////////////////////////////////////////////////
// CHtmlRecordSet diagnostics

#ifdef _DEBUG
void CHtmlRecordSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CHtmlRecordSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


//<TR>
//    <TD >一　年 </TD>
//    <TD >5.31 </TD>
//</TR>
void CHtmlRecordSet::MakeCurrentRow(CString &strHtml)
{
  CODBCFieldInfo fieldinfo;
  CDBVariant varint;
  CString strValue;
  strHtml = "<TR>\r\n";
  for(short i = 0;i<m_nFields;i++)
  {
    GetODBCFieldInfo(i, fieldinfo);
    GetFieldValue(i,varint,DEFAULT_FIELD_TYPE);

    switch(varint.m_dwType) 
    {
    case DBVT_NULL       :
        strValue =  "";
        break;
    case DBVT_BOOL       :
        strValue.Format("%d",varint.m_chVal);
        break;
    case DBVT_UCHAR      :
        strValue.Format("%d",varint.m_chVal);
        break;
    case DBVT_SHORT      :
        strValue.Format("xxxx x %d",i);
        break;
    case DBVT_LONG       :
        strValue.Format("%d",varint.m_lVal);
        break;
    case DBVT_SINGLE     :
        strValue.Format("%8.2f",varint.m_fltVal);
        break;
   case DBVT_DOUBLE     :
       strValue.Format("%8.2f",varint.m_dblVal);
       break;
    case DBVT_DATE       :
        strValue.Format("%d-%d-%d",varint.m_pdate->year,varint.m_pdate->month,varint.m_pdate->day);
        break;
    case DBVT_STRING     :
        if(*(varint.m_pstring)!="")
        {
            strValue.Format("%s",*(varint.m_pstring));
        }
        else
        {
            strValue = " ";
        }
        break;
    case DBVT_BINARY     :
        strValue =  "";
        break;
    default :
        strValue =  _T("ERROR");
        break;
    }
    strHtml += _T("<TD >");
    strHtml += strValue;
    strHtml += _T("</TD>");
//    TRACE(_T("grid:%s\n"),strHtml);
  }
  strHtml += _T("</TR>\r\n");
}
//  <TR bgColor=#e3f4fb>
//    <TH>各项贷款</TH>
//    <TH>单位：%</TH></TR>

void CHtmlRecordSet::MakeHeader(CString &strHtml)
{
    CODBCFieldInfo fieldinfo;
    strHtml = "<TR bgColor=#e3f4fb>\r\n";
    m_nFields = GetODBCFieldCount();
    if(m_strHeader.GetLength()>0)
    {
        CString strGrid;
        strGrid = m_strHeader;
        strGrid.Replace(";","</TH><TH >");
        strHtml += "<TH >";
        strHtml += strGrid;
        strHtml += "</TH>";
    }
    else
    {
        for(short i = 0;i<m_nFields;i++)
        {
            GetODBCFieldInfo(i, fieldinfo);
            strHtml += "<TH >";
            strHtml += fieldinfo.m_strName;
            strHtml += "</TH>";
        }
        
    }
    strHtml += "</TR>\r\n";
    
}
//<TABLE cellSpacing=1 cellPadding=0 width="100%" bgColor=#cccccc border=0>
//  
// </TBODY></TABLE>
void CHtmlRecordSet::ExportTable(CString &strHtml)
{
  strHtml.Format("<H2>%s</H2> \r\n",m_strTitle);
  strHtml += "<TABLE cellSpacing=1 cellPadding=0 width=\"100%\" bgColor=#cccccc border=0><TBODY bgColor=#ffffff>\r\n";
  CString strRow;
  MakeHeader(strRow);
  strHtml += strRow;
  if(this->GetRecordCount()>0)
  {
      MoveFirst();
      while(!IsEOF())
      {
          MakeCurrentRow(strRow);
          strHtml += strRow;
          MoveNext();
      }
  }
  strHtml += "</TBODY></TABLE>\r\n";
}


/*******************************************
    Function Name : 
    author        : Qiu Guohua
    Date          : 2010-1-21 20:36:36
    Description   : 
    Return type  : 
    Argument      : 
********************************************/
void CHtmlRecordSet::SetHeader(const CString &strHeader)
{
    m_strHeader = strHeader;
}

void CHtmlRecordSet::SetTitle(const CString &strTitle)
{
  m_strTitle = strTitle;

}

// CSVFile.cpp: implementation of the CCSVFile class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CSVFile.h"
#include <io.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define CSV_FILE_OPEND     -1
#define CSV_NOT_REPORTLIST -2
#define CSV_FILE_EXIST     -3
#define CSV_NO_FOLDER      -4
#define CSV_INVALID_HWND   -5
#define CSV_USER_CANCEL    -6

#define CSV_OTHER_ERROR    -10
#define CSV_SUCCESS        0

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#define MAX_SIZE 102400

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CCSVFile::CCSVFile()
{

}

CCSVFile::~CCSVFile()
{

}
CString GetPathFromFullPathName(CString strfilename)
{
	int n=strfilename.ReverseFind('\\');
	return strfilename.Left(n+1);
}


/*******************************************
    Function Name :	
    author        :	Qiu Guohua
    Date          :	2003-12-8 19:15:09
    Description   :	
    Return type	  :	
    Argument      :	
********************************************/
int CCSVFile::Save(CListCtrl *pctrl, CString &strfile, BOOL bFailIfExist)
{
	CFile csvfile;
	if(bFailIfExist&&( (_access((LPSTR)(LPCTSTR)strfile, 0 )) != -1) )
	{
      //( "File ACCESS.C exists\n" );
		return CSV_FILE_EXIST;
	}
	CString strpath=GetPathFromFullPathName(strfile);
	if((_access((LPSTR)(LPCTSTR)strpath, 0 )) == -1)
	{
		return CSV_NO_FOLDER;
	}
    if(!csvfile.Open(strfile,CFile::modeCreate|CFile::modeWrite))
        return CSV_FILE_OPEND;
    LVCOLUMN col;
    
    col.mask = LVCF_TEXT;
    char byStr[MAX_SIZE];
    col.pszText=byStr;
    col.cchTextMax=MAX_SIZE;
	
	// Double the column width of the first column.
	int icn=0;
	if(!(pctrl->GetStyle()&LVS_REPORT ))
	{
		return CSV_NOT_REPORTLIST;
	}
		
	int n=pctrl->GetHeaderCtrl()->GetItemCount();
	for(int ihead=0;ihead<n;ihead++)
	{
		pctrl->GetColumn(ihead, &col);
		WriteAString(&csvfile,col.pszText,ihead==(n-1));
	}
	int linecount=pctrl->GetItemCount();
	for(int line=0;line<linecount;line++)
	{
		for(int col=0;col<n;col++)
		{
			pctrl->GetItemText(line,col,byStr,MAX_SIZE);
			WriteAString(&csvfile,byStr,col==(n-1));
		}
	}
	csvfile.Close();
	return CSV_SUCCESS;

}


/*******************************************
    Function Name :	
    author        :	Qiu Guohua
    Date          :	2003-12-8 19:15:07
    Description   :	
    Return type	  :	
    Argument      :	
********************************************/
void CCSVFile::WriteAString(CFile *pfile, TCHAR* pszStr,BOOL bLineEnd)
{
	BYTE des[MAX_SIZE+1024];
	char pz[]=",\"\r\n";
	CString Str(pszStr);
	
	int n=Str.FindOneOf(pz);

	if(n==-1)
	{
        BOOL bFullDigit = TRUE;
        int nStrLen = Str.GetLength();
        for(int i = 0;i<nStrLen;i++)
        {
            if(pszStr[i]<'0'||pszStr[i]>'9')
            {
                bFullDigit = FALSE;
                break;
            }
        }
        if(bFullDigit)
        {
           pfile->Write("\'",1);
        }
		pfile->Write((LPSTR)(LPCTSTR)Str,Str.GetLength());
	}
	else
	{
		int length=Str.GetLength();
		int i=0;
		des[i++]='"';
		for(int j=0;j<length;j++)
		{
			if(pszStr[j]=='"')
			{
				des[i++]='"';
				des[i++]='"';
			}
			else
			{
				des[i++]=pszStr[j];
			}
		}
		des[i++]='"';
		pfile->Write(des,i);
	}
	if(bLineEnd)
	{
		pfile->Write("\r\n",2);
	}
	else
	{
		pfile->Write(",",1);
	}
}



int CCSVFile::SaveTo(CListCtrl* pctrl,BOOL bFailIfExist)
{
	DWORD dwOFN;
	if(bFailIfExist)
		dwOFN=OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT;
	else
		dwOFN=OFN_HIDEREADONLY;
	CFileDialog dlg(FALSE,"csv","",dwOFN,"(*.csv)|*.csv|");
	if(dlg.DoModal()!=IDOK)
	{
		return CSV_USER_CANCEL;
	}
	return Save(pctrl,dlg.GetPathName(),bFailIfExist);
}


/*******************************************
    Function Name : 
    author        : Qiu Guohua
    Date          : 2009-5-24 22:40:30
    Description   : 
    Return type  : 
    Argument      : 
********************************************/
int CCSVFile::SaveTo(CMailReportCtrl* pctrl,BOOL bFailIfExist)
{
    DWORD dwOFN;
    if(bFailIfExist)
        dwOFN=OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT;
    else
        dwOFN=OFN_HIDEREADONLY;
    CFileDialog dlg(FALSE,_T("csv"),_T(""),dwOFN,_T("(*.csv)|*.csv|"));
    if(dlg.DoModal()!=IDOK)
    {
        return CSV_USER_CANCEL;
    }
    return Save(pctrl,dlg.GetPathName(),bFailIfExist);
}

/*******************************************
    Function Name : 
    author        : Qiu Guohua
    Date          : 2009-5-24 22:16:59
    Description   : 
    Return type   : 
    Argument      : 
********************************************/
int CCSVFile::Save(CMailReportCtrl *pReportCtrl, CString &strfile, BOOL bFailIfExist)
{
    CFile csvfile;
    if(bFailIfExist&&( (_access((LPSTR)(LPCTSTR)strfile, 0 )) != -1) )
    {
        //( "File ACCESS.C exists\n" );
        return CSV_FILE_EXIST;
    }
    CString strpath=GetPathFromFullPathName(strfile);
    if((_access((LPSTR)(LPCTSTR)strpath, 0 )) == -1)
    {
        return CSV_NO_FOLDER;
    }
    if(!csvfile.Open(strfile,CFile::modeCreate|CFile::modeWrite))
        return CSV_FILE_OPEND;
    LVCOLUMN col;
    
    col.mask = LVCF_TEXT;
    char byStr[MAX_SIZE];
    col.pszText=byStr;
    col.cchTextMax=MAX_SIZE;
    
    // Double the column width of the first column.
    int icn=0;
	int count=pReportCtrl->GetColumnCount ();

    for(int iColumn=0;iColumn<count;iColumn++)
    {
		CString strColumn = pReportCtrl->GetColumnName (iColumn);
        WriteAString(&csvfile,(LPSTR)(LPCTSTR)strColumn,iColumn==(count-1));
    }
    int linecount=pReportCtrl->GetRowCount();
    
    for(int line=0;line<linecount;line++)
    {
        for(int col=0;col<count;col++)
        {
            CString strVal = (LPCTSTR) (_bstr_t) (pReportCtrl->GetRow(line)->GetItem(col)->GetValue());
            WriteAString(&csvfile,(LPSTR)(LPCTSTR)strVal,col==(count-1));
        }
    }
    csvfile.Close();
    return CSV_SUCCESS;
}

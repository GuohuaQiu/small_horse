// CSVLoader.cpp: implementation of the CCSVLoader class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "..\SmallHorse.h"
#include "CSVLoader.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCSVLoader::CCSVLoader()
{
	m_pBuffer = NULL;
	m_nBufLen = 0;
	m_pWorkPtr = NULL;
}

CCSVLoader::~CCSVLoader()
{
	if(m_pBuffer)
	{
		delete [] m_pBuffer;
	}
}


/*******************************************
    Function Name :	  GetFirstLineGrid
    Create by     :	  Qiu Guohua
    Input         :   void
    Output        :   grid number.
    Description   :   reterive first line to get grow number per line.
    Date          :   2007-1-12 14:28:42
********************************************/
int CCSVLoader::GetFirstLineGrid()
{
    if(m_pBuffer == NULL)
		return -1;
	m_pWorkPtr = m_pBuffer;
	CString strGet;
	NEXT_TYPE type;
	int nGrid = 1;

	while(1)
	{
		type = GetNextString(strGet);
		TRACE(_T("GRID:%s\n"),strGet);
		if(type == TYPE_LINE)
		{
			break;
		}
		if(type == TYPE_ERROR)
		{
			break;
		}
        nGrid++;
	}
	return nGrid;
}


/*******************************************
    Function Name :	 
    Create by     :	  Qiu Guohua
    Input         :   
    Output        :   
    Description   :   
    Date          :   2007-1-12 14:41:21
********************************************/
BOOL CCSVLoader::Load(const CString &strFile)
{
    CFile file;
	CFileException fileexcption;
	if(strFile.Right(4).CompareNoCase(_T(".csv"))!=0)
	{
		return FALSE;
	}
	if(!file.Open(strFile,CFile::modeRead|CFile::shareDenyNone,&fileexcption))
	{
		fileexcption.ReportError();
		return FALSE;
	}
	m_nBufLen = file.GetLength();
	if(m_pBuffer)
	{
		delete [] m_pBuffer;
	}
	m_pBuffer = new TCHAR[m_nBufLen + 1];
	file.Read(m_pBuffer,m_nBufLen);
	file.Close();
	return TRUE;
}


/*******************************************
    Function Name :	 
    Create by     :	  Qiu Guohua
    Input         :   
    Output        :   
    Description   :   
    Date          :   2007-1-12 15:07:33
********************************************/
NEXT_TYPE CCSVLoader::GetNextString(CString &strGet)
{
    if(m_pWorkPtr == NULL)
		return TYPE_ERROR;
	char* pEnd = FindStringEnd(m_pWorkPtr);
	int nLen = pEnd - m_pWorkPtr;
	char *pDest = strGet.GetBuffer(nLen + 1);
	strncpy(pDest,m_pWorkPtr,nLen);
	pDest[nLen] = 0;
	strGet.ReleaseBuffer();
	//"str" -> str
	if(strGet.Left(1) == "\""&&strGet.Right(1) == "\"")
	{
		strGet = strGet.Mid(1,strGet.GetLength()-2);
	}
	strGet.Replace("\"\"","\"");
	if(*pEnd == ',')
	{
		m_pWorkPtr = pEnd + 1;
		return TYPE_STR;
	}
	if(*pEnd == '\r')
	{
		TRACE("TYPE_LINE");
		m_pWorkPtr = pEnd + 2;
		return TYPE_LINE;
	}
	if(*pEnd == 0)
	{
		m_pWorkPtr = NULL;
		return TYPE_END;
	}
	return TYPE_ERROR;
}


char* CCSVLoader::FindStringEnd(char *pBegin)
{
	char* p = pBegin;
	int nBracket = 0;

	for(;*p;p++)
	{
		if(*p == '\"')
		{
            nBracket++;
			continue;
		}
		if(*p == ',')
		{
			if(nBracket%2 == 1)
			{
				continue;
			}
			else
			{
				break;
			}
		}
		if(*p == '\r')
		{
			break;
		}
		if(*p == 0)
		{
			break;
		}
	}
	return p;
}

void CCSVLoader::MovetoHead()
{
	m_pWorkPtr = m_pBuffer;
}

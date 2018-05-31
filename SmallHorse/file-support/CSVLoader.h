// CSVLoader.h: interface for the CCSVLoader class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CSVLOADER_H__7750724B_EFAB_430B_8394_EB7243DBB236__INCLUDED_)
#define AFX_CSVLOADER_H__7750724B_EFAB_430B_8394_EB7243DBB236__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
enum NEXT_TYPE{TYPE_ERROR,TYPE_STR,TYPE_END,TYPE_LINE};
class CCSVLoader  
{
private:
	int m_nBufLen;
	char* m_pBuffer;
	char* m_pWorkPtr;

public:
	void MovetoHead();
	char* FindStringEnd(char* pBegin);
	NEXT_TYPE GetNextString(CString& strGet);

	BOOL Load(const CString& strFile);
	int GetFirstLineGrid();
	CCSVLoader();
	virtual ~CCSVLoader();

};

#endif // !defined(AFX_CSVLOADER_H__7750724B_EFAB_430B_8394_EB7243DBB236__INCLUDED_)

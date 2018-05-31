// TableLoader.h: interface for the CTableLoader class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TABLELOADER_H__B2F3BE4B_0871_4FF7_94F1_CA3C4DBF3712__INCLUDED_)
#define AFX_TABLELOADER_H__B2F3BE4B_0871_4FF7_94F1_CA3C4DBF3712__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CTableLoader  
{
private:
	char* m_pContent;
	int m_size;
	char m_splitter;
public:
	
	void FillListCtrl(CListCtrl* pCtrl);
	int GetColCount();
	bool GetClipboardTable();
	CTableLoader();

	virtual ~CTableLoader();

};

#endif // !defined(AFX_TABLELOADER_H__B2F3BE4B_0871_4FF7_94F1_CA3C4DBF3712__INCLUDED_)

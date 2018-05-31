// TableLoader.cpp: implementation of the CTableLoader class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TableLoader.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTableLoader::CTableLoader()
{
	m_pContent=NULL;
	
}

CTableLoader::~CTableLoader()
{
	
}
int CTableLoader::GetColCount()
{
	int a = 0;
	int b = 0;
	char *pp ;
	pp=m_pContent;
	while(*pp !=0)
	{
		if(*pp == '\n')
		{
			b++;
			a = max(a,b);
			b = 0;
		}
		else
		{
			if(*pp == m_splitter){
				b++;
			}
		}
		pp++;
	}
	b++;
	return max(a,b);
}

bool CTableLoader::GetClipboardTable()
{
	if(m_pContent!=NULL){
		delete [] m_pContent;
		m_pContent=NULL;
	}
	if (!OpenClipboard(AfxGetMainWnd()->m_hWnd))
	{
		TRACE("failed to OpenClipboard");
		return false;
	}

	HGLOBAL hMem = GetClipboardData(CF_UNICODETEXT);
	if(hMem==NULL)
	{
		return false;
	}
	DWORD dwSize = GlobalSize(hMem);
	LPCWSTR lpStr = (LPCWSTR)::GlobalLock(hMem);
	m_pContent = new char[(dwSize + 1)*2];
	WideCharToMultiByte(CP_ACP,0,lpStr,-1,
		m_pContent,(dwSize + 1)*2,NULL,NULL);
	
	GlobalUnlock(hMem);
	CloseClipboard();

	char * pfirst_t = strchr(m_pContent,'\t');
	m_splitter = '\t';
	if(pfirst_t == NULL)
	{
		m_splitter = ' ';
	}
	return true;
}

void AutoWidthList(CListCtrl *pList)
{
	int nColumnCount = pList->GetHeaderCtrl()->GetItemCount();
	for (int i = 0; i < nColumnCount; i++)
	{
		pList->SetColumnWidth(i, LVSCW_AUTOSIZE);
		int nColumnWidth = pList->GetColumnWidth(i);
		pList->SetColumnWidth(i, LVSCW_AUTOSIZE_USEHEADER);
		int nHeaderWidth = pList->GetColumnWidth(i);
		pList->SetColumnWidth(i, max(nColumnWidth, nHeaderWidth) + 2);
	}
}
void FillText(CListCtrl* pListCtrl,int row, int col,char* p)
{
	if(row == pListCtrl->GetItemCount())
	{
		pListCtrl->InsertItem(row,p);
	}
	else
	{
		pListCtrl->SetItemText(row,col,p);
	}

}
void CTableLoader::FillListCtrl(CListCtrl *pCtrl)
{
	if(m_pContent == NULL)
	{
		return;
	}
	pCtrl->DeleteAllItems();
	char* p =m_pContent;
	int col_num = GetColCount();
	for(int i=0;i<col_num;i++)
	{
		pCtrl->InsertColumn(0,"test",350);
		pCtrl->SetColumnWidth(0,200);
	}
	char temp[2048];
	int row =0;
	bool go = true;
	int c =0;
	while(go)
	{
		char *end = strchr(p,'\n');
		if(end == NULL)
		{
			strcpy(temp,p);
			go = false;
		}
		else
		{
			c = end - p;
			strncpy(temp,p,c);
			temp[c]=0;
		}
		char* pp = temp;
		int col=0; 
		while(true)
		{
			char oh[2048];
			end = strchr(pp,m_splitter);
			if(end == NULL){
				FillText(pCtrl,row,col,pp);
				break;			
			}
			int d = end - pp;
			strncpy(oh,pp,d);
			oh[d]=0;
			pp += d;
			pp ++;
			FillText(pCtrl,row,col,oh);
			col++;
		}
		row++;
		p += c+1;
	}
	AutoWidthList(pCtrl);
}

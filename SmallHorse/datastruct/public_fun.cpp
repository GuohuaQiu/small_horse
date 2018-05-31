// public_fun.cpp: implementation of the public_fun class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "..\SmallHorse.h"
#include "public_fun.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
int GetColumnCount(CListCtrl* pListCtrl)
{
	CHeaderCtrl* pHeaderCtrl = pListCtrl->GetHeaderCtrl();
	return (pHeaderCtrl->GetItemCount());
}

void AdjustColumnWidth(CListCtrl* pListCtrl)
{
	pListCtrl->SetRedraw(FALSE);
	int nColumnCount = GetColumnCount(pListCtrl);
	
	for (int i = 0; i < nColumnCount; i++)
	{
		pListCtrl->SetColumnWidth(i, LVSCW_AUTOSIZE);
		int nColumnWidth = pListCtrl->GetColumnWidth(i);
		pListCtrl->SetColumnWidth(i, LVSCW_AUTOSIZE_USEHEADER);
		int nHeaderWidth = pListCtrl->GetColumnWidth(i); 
		pListCtrl->SetColumnWidth(i, max(nColumnWidth, nHeaderWidth));
	}
	pListCtrl->SetRedraw(TRUE);
} 

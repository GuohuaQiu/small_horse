// WorkspaceBar2.cpp : implementation of the CWorkspaceBar2 class
//

#include "stdafx.h"
#include "..\SmallHorse.h"
#include "WorkspaceBar2.h"
#include "idset.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const int nBorderSize = 1;

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceBar2

BEGIN_MESSAGE_MAP(CWorkspaceBar2, CBCGPDockingControlBar)
	//{{AFX_MSG_MAP(CWorkspaceBar2)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_EN_CHANGE(ID_EDIT_ID_SET, OnIDEditChanged)
	ON_NOTIFY(NM_DBLCLK, ID_LIST_ID_SET, OnDblclkList2)
    ON_NOTIFY(NM_RCLICK, ID_LIST_ID_SET, OnRclickList)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(IDM_RECTIFYINFO, OnRectifyinfo)
	ON_COMMAND(ID_ADD_RETURN_RECORD, OnAddReturnRecord)
	ON_COMMAND(ID_SET_AS_AUTORETURN_CREDIT, OnSetAsAutoreturnCredit)
	ON_COMMAND(ID_TRANSFER_DINGQI, OnTransferDingqi)
	ON_COMMAND(IDM_INFO, OnInfo)
	ON_COMMAND(IDM_ADDRECORD, OnAddrecord)
	ON_COMMAND(ID_OPEN_SUBCOUNT_BY_ID, OnOpenSubcountById)
	ON_COMMAND(ID_ADD_CREDIT_PAY_INFO, OnAddCreditPayInfo)
	ON_COMMAND(ID_MENU_CREDIT_REPORT, OnMenuCreditReport)
	ON_UPDATE_COMMAND_UI(ID_MENU_CREDIT_REPORT, OnUpdateMenuCreditReport)
	ON_COMMAND(ID_COUNT_LOCK, OnCountLock)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceBar2 construction/destruction
#if 0//no need to set a pay card.
extern CString g_strAutoReturnCard;
#endif

extern CString g_strAutoReturnCreditCard;

CWorkspaceBar2::CWorkspaceBar2()
{
	// TODO: add one-time construction code here

}

CWorkspaceBar2::~CWorkspaceBar2()
{
}

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceBar2 message handlers

int CWorkspaceBar2::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CBCGPDockingControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;
	
    if (!m_wndList.Create (WS_CHILD|WS_VISIBLE|LVS_REPORT   , 
		CRect (0, 0, 0, 0), this, ID_LIST_ID_SET))
	{
		TRACE0("CWorkspaceBar2::OnCreate: cannot create LIST control\n");
		return -1;
	}
    m_wndList.InsertColumn(0,"test");
	if (!m_wndIdEdit.Create( WS_CHILD | WS_VISIBLE|ES_AUTOHSCROLL      , 
		CRect (0, 0, 0, 0), this, ID_EDIT_ID_SET ))
	{
		TRACE0("CWorkspaceBar2::OnCreate: cannot create EDIT control\n");
		return -1;
	}
	m_Font.CreateStockObject (DEFAULT_GUI_FONT);
	m_wndIdEdit.SetFont (&m_Font);
	return 0;
}

void CWorkspaceBar2::OnSize(UINT nType, int cx, int cy) 
{
	CBCGPDockingControlBar::OnSize(nType, cx, cy);
#define EDIT_HEIGHT  (20)
#define INTERFACE_EDIT    (1)
	// Tab control should cover a whole client area:
	int x,y,w,h;
	x = nBorderSize;
	y = nBorderSize;
	w = cx - 2 * nBorderSize;
	h = EDIT_HEIGHT;
	m_wndIdEdit.SetWindowPos (NULL, x, y, w, h,
		SWP_NOACTIVATE | SWP_NOZORDER);
	y += h + INTERFACE_EDIT;
	h = cy - 2 * nBorderSize - (h + INTERFACE_EDIT);

	m_wndList.SetWindowPos (NULL, x, y, w, h,
		SWP_NOACTIVATE | SWP_NOZORDER);
    m_wndList.SetColumnWidth(0,cx);
}

void CWorkspaceBar2::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CRect rectEdit;
	CRect rectList;
  CRect rectThisWnd;
	m_wndIdEdit.GetWindowRect (rectEdit);
	m_wndList.GetWindowRect (rectList);
  rectThisWnd = rectEdit;
	rectThisWnd.bottom = rectList.bottom;
	ScreenToClient (rectThisWnd);

	rectThisWnd.InflateRect (nBorderSize, nBorderSize);
	dc.Draw3dRect (rectThisWnd,	::GetSysColor (COLOR_3DSHADOW), 
								::GetSysColor (COLOR_3DSHADOW));

  int y = rectThisWnd.top + rectEdit.Height() +1;

	CPen penred,*oldpen;
	penred.CreatePen(PS_SOLID   ,1,::GetSysColor (COLOR_3DSHADOW));
	oldpen=dc.SelectObject(&penred);

  dc.MoveTo(rectThisWnd.left,y);
  dc.LineTo(rectThisWnd.right,y);
	dc.SelectObject(oldpen);
}

void CWorkspaceBar2::OnIDEditChanged() 
{
  if(m_wndIdEdit.m_bWaiting)
  {
    return;
  }
	CString strID;
	m_wndIdEdit.GetWindowText(strID);
  if(strID.GetLength()==0)
  {
    return;
  }
    CIDSet* pIdSet = new CIDSet();
	pIdSet->Open();
	if(strID.GetLength()>0)
	{
		pIdSet->m_strFilter = "Book_ID LIKE \'%";
		pIdSet->m_strFilter += strID;
		pIdSet->m_strFilter += "%\'";
	}
	else
	{
		pIdSet->m_strFilter = "";

	}
	pIdSet->Requery();
	int nCount = pIdSet->GetRecordCount();
	if(nCount > 0)
	{
		pIdSet->MoveFirst();
		m_wndList.DeleteAllItems();
		int i = 0;
		while(!pIdSet->IsEOF())
		{
			m_wndList.InsertItem(i, pIdSet->m_ID );
            m_wndList.SetItemData(i,(DWORD)pIdSet->m_nType);
			pIdSet->MoveNext();
		}
	}
	pIdSet->Close();
	delete pIdSet;
}


/*******************************************
    Function Name : 
    author        : Qiu Guohua
    Date          : 2009-2-27 22:50:21
    Description   : 
    Return type  : 
    Argument      : 
********************************************/
void CWorkspaceBar2::OnDblclkList2(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LPNMITEMACTIVATE pActive = (LPNMITEMACTIVATE)pNMHDR;
	if(pActive->iItem != -1)
	{
		CString strID = m_wndList.GetItemText(pActive->iItem,0);
		theApp.OpenBankbook(strID);
	}

	*pResult = 0;
}





void CWorkspaceBar2::OnRclickList(NMHDR* pNMHDR, LRESULT* pResult) 
{
    LPNMITEMACTIVATE pActiveStruct = (LPNMITEMACTIVATE)pNMHDR;
    if(pActiveStruct->iItem != -1)
    {
        m_wndList.SetItemState(pActiveStruct->iItem,LVIS_SELECTED,LVIS_SELECTED);
        CPoint point(pActiveStruct->ptAction);
        CMenu menu;
        menu.LoadMenu(IDR_TREEMENU);
        ClientToScreen(&point);
        theApp.ShowPopupMenu (IDR_BANKBOOK_MENU, point, this);
    }
    *pResult = 0;

}




void CWorkspaceBar2::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	// to prevent old bcg menu.
	
}

void CWorkspaceBar2::OnRectifyinfo() 
{
    POSITION pos = m_wndList.GetFirstSelectedItemPosition();
    if(pos)
    {
        int n = m_wndList.GetNextSelectedItem(pos);
        CString strid = m_wndList.GetItemText(n,0);
        theApp.RectifyBookInfo(strid);
    }
}

void CWorkspaceBar2::OnAddReturnRecord() 
{
	// TODO: Add your command handler code here
	
}

#if 0
void CWorkspaceBar2::OnSetAsAutoReturnCard() 
{
#ifdef  LOAD_DATEBASE
    CString strid;
    if(GetSelectedID(strid))
    {
         theApp.SetAutoPayCard(strid);
    }
#endif
    
}
#endif

void CWorkspaceBar2::OnSetAsAutoreturnCredit() 
{
    CString strid;
    if(GetSelectedID(strid))
    {
        theApp.SetAutoReturnCreditCard(strid);
    }
//        ::MessageBox(this->m_hWnd,g_strAutoReturnCreditCard,"CWorkspaceBar2",IDOK);
	
}

void CWorkspaceBar2::OnTransferDingqi() 
{
    CString strid;
    if(GetSelectedID(strid))
    {
        theApp.TransferDingqi(strid);
    }
}




void CWorkspaceBar2::OnInfo() 
{
    CString strid;
    if(GetSelectedID(strid))
    {
        theApp.ShowAccountInfo(strid);
    }
}



/*******************************************
    Function Name : 
    author        : Qiu Guohua
    Date          : 2009-6-27 13:56:33
    Description   : 
    Return type  : 
    Argument      : 
********************************************/
BOOL CWorkspaceBar2::GetSelectedID(CString &strID)
{
    POSITION pos = m_wndList.GetFirstSelectedItemPosition();
    if(pos)
    {
        int n = m_wndList.GetNextSelectedItem(pos);
        strID = m_wndList.GetItemText(n,0);
        return TRUE;
    }
    return FALSE;
    
}

void CWorkspaceBar2::OnAddrecord() 
{
    CString strid;
    if(GetSelectedID(strid))
    {
        theApp.AddNewItem(strid);
    }
    
}


/*******************************************
    Function Name : 
    author        : Qiu Guohua
    Date          : 2010-4-8 17:01:36
    Description   : 
    Return type   : 
    Argument      : 
********************************************/
void CWorkspaceBar2::OnOpenSubcountById() 
{
    CString strid;
    if(GetSelectedID(strid))
    { 
        theApp.OpenSubCountbyId(strid);
    }
}

void CWorkspaceBar2::OnAddCreditPayInfo() 
{
    CString strid;
    if(GetSelectedID(strid))
    { 
        theApp.AddCreditPayInfo(strid);
    }
	
}

COLORREF CMyListCtrl::OnGetCellTextColor (int nRow, int nColum)
{
    DWORD dwData = GetItemData(nRow);
    if(dwData == 1)
    {
        return RGB (128, 37, 0);
    }
    if(dwData == 2)
    {
        return RGB (37, 128, 0);
    }
    if(dwData == 3)
    {
        return RGB (255, 0, 0);
    }
    return CBCGPListCtrl::OnGetCellTextColor (nRow, nColum);
    
}

COLORREF CMyListCtrl::OnGetCellBkColor (int nRow, int nColum)
{
    return CBCGPListCtrl::OnGetCellBkColor (nRow, nColum);
}


void CWorkspaceBar2::OnMenuCreditReport() 
{
    CString strid;
    if(GetSelectedID(strid))
    { 
        theApp.OpenReportView(strid);
    }
}

void CWorkspaceBar2::OnUpdateMenuCreditReport(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CWorkspaceBar2::OnCountLock() 
{
    CString strid;
    if(GetSelectedID(strid))
    { 
        //Simon theApp.LockCount(strid);
    }
}

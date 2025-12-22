// BankbookTree.cpp : implementation file
//

#include "stdafx.h"
#include "..\SmallHorse.h"
#include "BankbookTree.h"
#include "..\mainfrm.h"
#include "NewBook.h"
#include "PassWordDlg.h"


#include "QueryEndDlg.h"
#include "FindBookDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBankbookTree

int arraylength;



CBankbookTree::CBankbookTree()
{
	m_pImageList = NULL;
	m_hBank = NULL;
	m_hPeople = NULL;

}

CBankbookTree::~CBankbookTree()
{
	if(m_pImageList != NULL)
	{
		delete m_pImageList;
	}
}


BEGIN_MESSAGE_MAP(CBankbookTree, CTreeCtrl)
	//{{AFX_MSG_MAP(CBankbookTree)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, OnSelchanged)
	ON_NOTIFY_REFLECT(TVN_ITEMEXPANDING, OnItemexpanding)
	ON_COMMAND(IDM_RECTIFYPASSWORD, OnRectifypassword)
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_RECORD_NEW, OnAddrecord)
	ON_COMMAND(IDM_DELETEBOOK, OnDeletebook)
	ON_COMMAND(IDM_INFO, OnInfo)
	ON_COMMAND(IDM_RECTIFYINFO, OnRectifyinfo)
	ON_COMMAND(ID_BANKBOOK_FREE, OnBankbookFree)
	ON_COMMAND(ID_SET_AS_AUTORETURN_CREDIT, OnSetAsAutoReturnCredit)
	ON_COMMAND(ID_FIND_BOOK, OnFindBook)
	ON_WM_CREATE()
	ON_WM_CONTEXTMENU()
	ON_NOTIFY_REFLECT(NM_DBLCLK, OnDblclk)
	ON_COMMAND(ID_TRANSFER_DINGQI, OnTransferDingqi)
	ON_COMMAND(ID_OPEN_SUBCOUNT_BY_ID, OnOpenSubcountById)
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_ADD_CREDIT_PAY_INFO, OnAddCreditPayInfo)
	ON_UPDATE_COMMAND_UI(ID_ADD_CREDIT_PAY_INFO, OnUpdateAddCreditPayInfo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBankbookTree message handlers

void CBankbookTree::FillEmptyTree()
{
#ifdef  LOAD_DATEBASE
    // form the one and only tree root - the desktop
    TV_INSERTSTRUCT	strInsert;
    // must use a selectedimage even if same
    strInsert.item.mask = TVIF_TEXT |TVIF_IMAGE |TVIF_SELECTEDIMAGE;
    // a root item - so parent is NULL
    strInsert.item.iImage =4;
    strInsert.item.iSelectedImage =4;
    strInsert.item.cChildren =1;
    
    strInsert.hParent = NULL;
    // index of the image in the list
#ifdef _DEBUG
    strInsert.item.pszText = (LPTSTR)_T("存折管理-当前使用的测试数据库");
#else
    strInsert.item.pszText = (LPTSTR)_T("存折管理");
#endif
    HTREEITEM hTop = InsertItem(&strInsert);
//     
     strInsert.hParent = hTop;
//     // index of the image in the list
//     strInsert.item.pszText = (LPTSTR)_T("按顺序");
//     HTREEITEM hSort = InsertItem(&strInsert);
//     pIdSet->m_strFilter=_T("");
//     pIdSet->Requery();
//     if(!pIdSet->IsBOF())
//     {
//         pIdSet->MoveFirst();
//     }
//     
//     while(!pIdSet->IsEOF())
//     {
//         AddTreeItem(hSort,pIdSet->m_ID);
//         pIdSet->MoveNext();
//     }
    // index of the image in the list
    strInsert.item.iImage =8;
    strInsert.item.iSelectedImage =8;
    strInsert.item.pszText = (LPTSTR)_T("按银行");
    strInsert.item.cChildren =1;
    m_hBank = InsertItem(&strInsert);

    AddTreeGroup(m_hBank);
    
    
    // index of the image in the list
    strInsert.hParent = hTop;
    strInsert.item.iImage =5;
    strInsert.item.iSelectedImage =5;
    strInsert.item.pszText = (LPTSTR)_T("持有人");
    m_hPeople = InsertItem(&strInsert);
    
    AddTreeGroup(m_hPeople);
    Expand( hTop, TVE_EXPAND );
#endif
}

void CBankbookTree::AddTreeGroup(HTREEITEM htree)
{
#ifdef  LOAD_DATEBASE
	
    CIDSet idSet;
    idSet.OpenEx();
    CIDSet* pIdSet = &idSet;
    if(pIdSet == NULL)
    {
        return;
    }
	
	CString strname=GetItemText(htree);
	TV_INSERTSTRUCT	strInsert;
	strInsert.item.mask = TVIF_TEXT |TVIF_IMAGE |TVIF_SELECTEDIMAGE;
		// a root item - so parent is NULL
	strInsert.item.iImage =8;
	strInsert.item.iSelectedImage =8;
	strInsert.hParent = htree;
	if(strname==_T("按银行"))
	{
		pIdSet->m_strSort=_T("Book_Bank,Book_Owner,Book_ID");
		pIdSet->Requery();
        if(!pIdSet->IsBOF())
        {
            pIdSet->MoveFirst();
        }
		CString strbank;//=
		HTREEITEM hcurBankTree = NULL;
		while(!pIdSet->IsEOF())
		{
			if(strbank!=pIdSet->m_bank)
			{
				strInsert.item.pszText = (LPTSTR)(LPCTSTR)pIdSet->m_bank;
				hcurBankTree = InsertItem(&strInsert);
				strbank=pIdSet->m_bank;
			}
			AddTreeItem(hcurBankTree,pIdSet->m_ID,pIdSet->m_bExist);
			pIdSet->MoveNext();
		}
	}
	else if(strname==_T("持有人"))
	{
		pIdSet->m_strSort=_T("Book_Owner,Book_Bank,Book_ID");
		pIdSet->Requery();
        if(!pIdSet->IsBOF())
        {
            pIdSet->MoveFirst();
        }
		CString strpeople;//=
		HTREEITEM hcurPeopleTree;
		while(!pIdSet->IsEOF())
		{
				strInsert.item.iImage =6;
				strInsert.item.iSelectedImage =6;
			if(strpeople!=pIdSet->m_name)
			{
				if(pIdSet->m_name==_T("王会军"))
				{
					strInsert.item.iImage =7;
					strInsert.item.iSelectedImage =7;
				}
				strInsert.item.pszText = (LPTSTR)(LPCTSTR)pIdSet->m_name;
				hcurPeopleTree = InsertItem(&strInsert);
				strpeople=pIdSet->m_name;
			}
			AddTreeItem(hcurPeopleTree,pIdSet->m_ID,pIdSet->m_bExist);
			pIdSet->MoveNext();
		}
	}
#endif
}


void CBankbookTree::OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult) 
{
	return;
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
#ifdef  LOAD_DATEBASE
	if(IsBandbook(pNMTreeView->itemNew.hItem))
	{
		CString strID =GetItemText(pNMTreeView->itemNew.hItem);
		theApp.OpenBankbook(strID);
	}
	return;
#endif

	
	*pResult = 0;
}




void CBankbookTree::OnItemexpanding(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	*pResult = 0;
	HTREEITEM hItem=GetRootItem();
	if(pNMTreeView->itemNew.hItem!=hItem)
		return;

	if(pNMTreeView->action==TVE_EXPAND)
	{
		SetItemImage(hItem,0,0);
	}
	else if(pNMTreeView->action==TVE_COLLAPSE )
		SetItemImage(hItem,4,4);
}
void CBankbookTree::DeleteBook()
{
#ifdef  LOAD_DATEBASE
	if(!IsBandbook())
	{
		AfxMessageBox(_T("先选中要删除的存折!"));
		return;
	}
	if(!ValidatePassWord())
		return;

	
	HTREEITEM hItem=GetSelectedItem();
	HTREEITEM hParentItem=GetParentItem(hItem);
	if(hParentItem==NULL)
		return;
	
	CString strid=GetItemText(hItem);
    if(theApp.DeleteBook(strid))
    {
        DeleteAllItems();
        FillEmptyTree();
    }


#endif

}




void CBankbookTree::OnRectifypassword() 
{
#ifdef  LOAD_DATEBASE
	if(!IsBandbook())
    {
        return ;
    }
    CString strID = GetSelectedText();
	theApp.Rectifypassword(strID);
#endif
}

BOOL CBankbookTree::ValidatePassWord()
{
#ifdef  LOAD_DATEBASE
	
	HTREEITEM hItem=GetSelectedItem();
	HTREEITEM hParentItem=GetParentItem(hItem);
	if(hParentItem==NULL)
		return FALSE;
	DWORD dw=GetItemData(hItem);
	if((dw&0x1001)==0x1001)
		return TRUE;
	if((dw&0x0001)!=0x0001)
		return FALSE;
	
	CString strid=GetItemText(hItem);
    CIDSet idSet;
    if(!idSet.FindByID(strid))
    {
        return FALSE;
    }
	do{
		CPassWordDlg pwdlg;
		pwdlg.m_id=_T("ID:")+strid;
		if(pwdlg.DoModal()!=IDOK)
			return FALSE ;
        if(pwdlg.m_password==idSet.m_password)
		{
			SetItemData(hItem,0x1001);
			return TRUE;
		}
		if(IDCANCEL==AfxMessageBox(_T("密码错误!"),MB_RETRYCANCEL))
			return FALSE;
	}while(1);
#endif	
    return FALSE;
}


void CBankbookTree::OnRButtonDown(UINT nFlags, CPoint point) 
{
#ifdef  LOAD_DATEBASE
	HTREEITEM curItem=HitTest(point,&nFlags );
	if(curItem==NULL)
		return;

	SelectItem(curItem);/**/
	
	CMenu menu;
	menu.LoadMenu(IDR_TREEMENU);
	ClientToScreen(&point);
	if(IsBandbook(curItem))
	{
        theApp.ShowPopupMenu (IDR_BANKBOOK_MENU, point, this);
	}
	else
	{
		menu.GetSubMenu(1)->TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON|TPM_RIGHTBUTTON,point.x,point.y,this);
	}
#endif	
}

void CBankbookTree::OnAddrecord() 
{
#ifdef  LOAD_DATEBASE
	HTREEITEM hItem=GetSelectedItem();//GetParentItem(hItem);
	if(hItem == NULL)
		return ;
	if(!IsBandbook( hItem))
		return;
	CString strID=GetItemText(hItem);
	theApp.AddNewItem(strID);
	// TODO: Add your command handler code here
#endif	
}

void CBankbookTree::OnDeletebook() 
{
#ifdef  LOAD_DATEBASE
    DeleteBook();
#endif
}

void CBankbookTree::OnInfo() 
{
#ifdef  LOAD_DATEBASE
    if(IsBandbook(GetSelectedItem()))
    {
        CString strID = GetSelectedText();
        theApp.ShowAccountInfo(strID);
    }
#endif
}	

void CBankbookTree::OnRectifyinfo() 
{
#ifdef  LOAD_DATEBASE
	if(!ValidatePassWord())
		return;

    if(IsBandbook(GetSelectedItem()))
    {
        CString strID = GetSelectedText();
        theApp.RectifyBookInfo(strID);
    }
#endif	
}

//0X1000表示存折已经输过密码了。
//0x0001表示该项为存折.

BOOL CBankbookTree::IsBandbook(HTREEITEM hItem)
{
#ifdef  LOAD_DATEBASE
	
	DWORD dw=GetItemData(hItem);
	if((dw&0X0001)==0X0001)
		return TRUE;
#endif
	return FALSE;
}



BOOL CBankbookTree::IsBandbook()
{
#ifdef  LOAD_DATEBASE
	HTREEITEM hItem=GetSelectedItem();//GetParentItem(hItem);
	if((GetItemData(hItem)&0x0001)==0x0001)
		return TRUE;
#endif
	return FALSE;
}



void CBankbookTree::AddTreeItem(HTREEITEM hparent, const CString& strId, BOOL bExist)
{
#ifdef  LOAD_DATEBASE
    
    TV_INSERTSTRUCT	structthis;
    structthis.item.mask = TVIF_TEXT |TVIF_IMAGE |TVIF_SELECTEDIMAGE;
    structthis.hParent = hparent;
    structthis.item.pszText = (LPTSTR)(LPCTSTR)strId;
    structthis.item.iImage = bExist ? 1 : 3;
    structthis.item.iSelectedImage = 2;
    HTREEITEM hBankBook= InsertItem(&structthis);
    SetItemData(hBankBook,0x0001);
#endif
}

void CBankbookTree::QueryPeople(CString strname, BOOL bDisBill/*=FALSE*/)
{
#ifdef  LOAD_DATEBASE
	
    CIDSet idSet;
    idSet.OpenEx();
	CIDSet* pIdSet = &idSet;
    CListSet* pListSet = theApp.GetListSet();
	
	CString strnamefil=_T("Book_Owner=\'");
	strnamefil+=strname;
	strnamefil+=_T("\'");
	pIdSet->m_strFilter=strnamefil;
	pIdSet->Requery();
	if(pIdSet->GetRecordCount()==0)
		return;
	pIdSet->MoveFirst();
	CString strfil;
	
	while(!pIdSet->IsEOF())
	{
		strfil+=_T("\'")+pIdSet->m_ID+_T("\',");
		pIdSet->MoveNext();
	}
	
	strfil.Delete(strfil.ReverseFind(','));
	if(bDisBill)
	{
		CQueryEndDlg dlg;
		dlg.m_pidset=pIdSet;
		dlg.m_plistset=pListSet;
		dlg.DoModal();
	}
	
	pListSet->m_strFilter =_T("Item_Book_ID IN")+ strfil+_T(") and (Type=1 or Type=2)");// '379 70052992*3'
	pListSet->m_strSort=_T("OperDate,Index");
	pListSet->Requery();
	
	
	
#if 0/*Qiu Simon*/
	CCurveView * pLineView = (CCurveView*)pFWnd->m_wndSplitter.GetPane(1,0);
	ASSERT( pLineView != NULL);
	pLineView->bDraw=TRUE;//Invalidate();
	pLineView->m_curvename=strname;
	
	pLineView->Invalidate();
#else
#endif
	DisplayStaticInfo();
#endif
}

BOOL CBankbookTree::IsPeople(HTREEITEM item)
{
#ifdef  LOAD_DATEBASE
	HTREEITEM newitem=GetParentItem(item);
	if(newitem==NULL)
		return FALSE;
	CString str=GetItemText(newitem);
	if(str==_T("持有人"))
		return TRUE;
#endif
	return FALSE;
}




void CBankbookTree::OnBankbookFree() 
{
#ifdef  LOAD_DATEBASE
	if(!IsBandbook())
	{
		AfxMessageBox(_T("先选中要删除的存折!"));
		return;
	}
	if(!ValidatePassWord())
	{
		AfxMessageBox(_T("您没有足够的权限来执行些操作!"));
		return;
	}
	
    CString strID = GetSelectedText();
    theApp.FreeBook(strID);
#endif
}


void CBankbookTree::DisplayStaticInfo()
{
#if 0/*Qiu Simon*/
	CMainFrame * pFWnd = (CMainFrame *)AfxGetMainWnd();
	CBankBookDoc* pDoc = (CBankBookDoc*)GetDocument();
	ASSERT_VALID(pDoc);
	
	pFWnd->m_wndStatusBar.SetPaneText(0,pDoc->m_IDSet.m_ID);
	pFWnd->m_wndStatusBar.SetPaneText(1,pDoc->m_IDSet.m_bank);
	pFWnd->m_wndStatusBar.SetPaneText(2,pDoc->m_IDSet.m_name);
#else
#endif
}


//to complete 2008-08-23
void CBankbookTree::OnFindBook() 
{
#ifdef LOAD_DATEBASE
    CFindBookDlg dlg;
    if (dlg.DoModal() != IDOK)
    {
        return;
    }
    if (dlg.m_strFind == _T(""))
    {
        return;
    }

    CIDSet idSet;
    idSet.OpenEx();
    CString strID;
    BOOL b = idSet.Find(dlg.m_strFind, strID);
    if (b)
    {
		AfxMessageBox(strID);
	}
	else
	{
		AfxMessageBox(_T("Failed."));
        return;
	}


	// Look at all of the root-level items
	HTREEITEM hCurrent = GetRootItem( );
	HTREEITEM hAllItem = GetChildItem(hCurrent);
	if(hAllItem)
	{
		CString strText;
		hCurrent = GetChildItem(hAllItem);
		while(hCurrent)
		{
			strText = GetItemText(hCurrent);
			TRACE(_T("%s"),strText);
			if(strText == strID)
			{
				SelectItem(hCurrent);
				return;
			}
			hCurrent = GetNextSiblingItem(hCurrent);
		}
	}
#endif
}

#if 0
void CBankbookTree::OnSetAsAutoReturnCard() 
{
#ifdef  LOAD_DATEBASE
    CIDSet* pIdSet = theApp.GetIDSet();
    if(!MovetoSelectedBankbook(pIdSet))
    {
        AfxMessageBox(_T("先选择一个账号!"));
        return ;
    }
    theApp.SetAutoPayCard(pIdSet->m_ID);
#endif
}
#endif
void CBankbookTree::OnSetAsAutoReturnCredit() 
{
#ifdef  LOAD_DATEBASE
    HTREEITEM hItem = GetSelectedItem();
    if(hItem == NULL || !IsBandbook(hItem))
    {
        AfxMessageBox(_T("先选择一个账号!"));
        return;
    }

    CString strID = GetItemText(hItem);
    CIDSet idSet;
    if(!idSet.FindByID(strID))
    {
        AfxMessageBox(_T("先选择一个账号!"));
        return;
    }
    theApp.SetAutoReturnCreditCard(strID);
//    ::MessageBox(this->m_hWnd,g_strAutoReturnCreditCard,"CBankbookTree",IDOK);
#endif	
}



int CBankbookTree::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CTreeCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;
	m_pImageList = new CImageList();
	// 16x16 pixels, 8 of them
	m_pImageList->Create(IDB_BOOK,16,1,RGB(128,128,0));
	SetImageList( m_pImageList, TVSIL_NORMAL );
#ifdef _DEBUG
    m_bmBG.LoadBitmap(IDB_TESTONLY);	
#endif
#ifdef  LOAD_DATEBASE
	// TODO: Add your specialized creation code here
	FillEmptyTree();
#endif
	return 0;
}

void CBankbookTree::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	// Only to prevent the bcg bar menu.
}

CString CBankbookTree::GetSelectedText()
{
	HTREEITEM hItem=GetSelectedItem();
	if(hItem==NULL)
		return _T("");
	
	return GetItemText(hItem);
}

BOOL CBankbookTree::MovetoSelectedBankbook(CIDSet *pIdSet)
{
    if(!IsBandbook())
    {
        return FALSE;
    }
    CString strID = GetSelectedText();
    return pIdSet->MovetoCurID(strID);
}

void CBankbookTree::OnDblclk(NMHDR* pNMHDR, LRESULT* pResult) 
{
	HTREEITEM hItem=GetSelectedItem();
	if(hItem==NULL)
		return ;
#ifdef  LOAD_DATEBASE
    if(hItem == m_hBank || hItem == m_hPeople)
    {
        if(hItem == m_hBank)
        {
            theApp.OpenAllCountOrderbyBank();
        }
        else
        {
            theApp.OpenAllCountOrderbyOwner();
        }
    }
	else if(IsBandbook(hItem))
	{
		CString strID =GetItemText(hItem);
		theApp.OpenBankbook(strID);
	}
	else
	{
		HTREEITEM hParentItem = GetParentItem(hItem);
		if(hParentItem == m_hBank)
		{
			CString strText = GetItemText(hItem);
			theApp.OpenCountsbyBank(strText);
		}
		else if(hParentItem == m_hPeople)
		{
			CString strText = GetItemText(hItem);
			theApp.OpenCountsbyPeople(strText);
		}

	}
#endif

	*pResult = 0;
}


/*******************************************
    Function Name : 
    author        : Qiu Guohua
    Date          : 2009-4-23 22:14:49
    Description   : 
    Return type  : 
    Argument      : 
********************************************/
void CBankbookTree::OnTransferDingqi() 
{
	CString strID = GetSelectedText();
	//Simon theApp.TransferDingqi(strID);
}



/*******************************************
    Function Name : 
    author        : Qiu Guohua
    Date          : 2010-3-10 9:19:04
    Description   : 
    Return type  : 
    Argument      : 
********************************************/
void CBankbookTree::OnOpenSubcountById() 
{
    CString strID = GetSelectedText();
    theApp.OpenSubCountbyId(strID);
}

BOOL CBankbookTree::OnEraseBkgnd(CDC* pDC) 
{
#ifdef _DEBUG
	CBrush hbr,*phbrOld;
	CRect rect;

	hbr.CreatePatternBrush(&m_bmBG);
	phbrOld= pDC->SelectObject(&hbr);
	GetClientRect(&rect);
	pDC->FillRect(&rect,&hbr);
	
	pDC->SelectObject(phbrOld);
	hbr.DeleteObject();
	
	return TRUE;	
#else
	return CTreeCtrl::OnEraseBkgnd(pDC);
#endif
		// TODO: Add your message handler code here and/or call default

}


/*******************************************
    Function Name :	 
    Create by     :	  Qiu Simon
    Input         :   
    Output        :   
    Description   :   
    Date          :   2010-8-26 16:34:46
********************************************/
void CBankbookTree::OnAddCreditPayInfo() 
{
    CString strID = GetSelectedText();
    theApp.AddCreditPayInfo(strID);
}


/*******************************************
    Function Name :	 
    Create by     :	  Qiu Simon
    Input         :   
    Output        :   
    Description   :   
    Date          :   2010-8-26 16:34:54
********************************************/
void CBankbookTree::OnUpdateAddCreditPayInfo(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

/*******************************************
    Function Name :	 
    Create by     :	  Qiu Simon
    Input         :   
    Output        :   
    Description   :   
    Date          :   2018-5-25 13:39:54
********************************************/
void  CBankbookTree::ReloadAll(void)
{
	DeleteAllItems( );
	FillEmptyTree();
}
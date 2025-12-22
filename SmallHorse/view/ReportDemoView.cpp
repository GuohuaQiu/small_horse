// ReportDemoView.cpp : implementation of the CReportDemoView class
//

#include "stdafx.h"
//#include "..\SmallHorse.h"

#include "Bankbookdoc.h"

#include "ImportSheet.h"
#include "CSVFILE.h"
#include <afxadv.h>
#include "public_fun.h"
#include "GridHtmlExporter.h"
#include "ReportDemoView.h"
#include "BCGPGridCtrl.h"
#include "SmartSetDlg.h"
#include "PeriodSetupDlg.h"
#include "CheckCountDateSetup.h"
#include "AddNewItemDlg.h"
#include "GroupRow.h"
#include "DingQiInputDlg.h"
#include "database_setup.h"
#include "CreditPaySet.h"
#include "SmartDate.h"
#include "CopyRecordsDlg.h"
#include "ReplaceStringDlg.h"
#include "DetailSubCountSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

enum 
{
    COLUMN_REPORT_START_TIME,
		COLUMN_REPORT_END_TIME,
		COLUMN_REPORT_EXPENSE,
		COLUMN_REPORT_REPAY,
		COLUMN_REPORT_GAP,
		CLOUMN_REPORT_ACCOUNT_GAP,
		CLOUMN_REPORT_COLOUMN_COUNT
};
enum
{
	COLUMN_LINE__ ,
		COLUMN_DATE__ ,
		COLUMN_CHANGE ,
		COLUMN_ID____ ,
		COLUMN_REASON ,
		COLUMN_TYPE__ ,
		COLUMN_SITE__ ,
		COLUMN_SUBCOUNT,
		COLUMN_BASE_NUMBER
};

enum COLUMN_QUERY
{
	COLUMN_BOOK_ID = COLUMN_BASE_NUMBER,
	COLUMN_BOOK_BANK,
	COLUMN_QUERY_NUMBER
};


enum COLUMN_TODO
{
    COLUMN_TODO_ID,
    COLUMN_TODO_BODY,
    COLUMN_TODO_NUMBER
};

enum COLUMN_SIMPLE_SUBCOUNT
{
	COLUMN_SIMPLE_SUBCOUNT_NAME,
	COLUMN_SIMPLE_SUBCOUNT_REMAIN,
	COLUMN_SIMPLE_SUBCOUNT_NUMBER
};

enum COLUMN_DETAIL_SUBCOUNT
{
    COLUMN_DETAIL_SUBCOUNT_BANK,
    COLUMN_DETAIL_SUBCOUNT_OWNER,
    COLUMN_DETAIL_SUBCOUNT_ID,
    COLUMN_DETAIL_SUBCOUNT_VALUE,
    COLUMN_DETAIL_SUBCOUNT_START_DATE,
    COLUMN_DETAIL_SUBCOUNT_END_DATE,
    COLUMN_DETAIL_SUBCOUNT_RATE,
    COLUMN_DETAIL_SUBCOUNT_TIMESPAN,
    COLUMN_DETAIL_SUBCOUNT_COMMENT,
    COLUMN_DETAIL_SUBCOUNT_STATUS,
    COLUMN_DETAIL_SUBCOUNT__COUNT,
};

enum COLUMN_ONE_BOOK
{
	COLUMN_REMAIN  = COLUMN_BASE_NUMBER,
		COLUMN_ONE_BOOK_NUMBER
};

enum
{
	COLUMN_MAINCOUNT_MAINCOUNT   ,
		COLUMN_MAINCOUNT_BANK        ,
		COLUMN_MAINCOUNT_OWNER       ,
		COLUMN_MAINCOUNT_VALUE       ,
		COLUMN_MAINCOUNT_NUMBER
};



enum
{
	COLUMN_SUBCOUNT_MAINCOUNT   , //_T("CountID"),
	COLUMN_SUBCOUNT_SUBCOUNT	,   //_T("SubCountID"),
	COLUMN_SUBCOUNT_BANK		,     //_T("Book_Bank"),
	COLUMN_SUBCOUNT_OWNER		,     //_T("Book_Owner"),
	COLUMN_SUBCOUNT_VALUE		,     //_T("BeginValue"),
	COLUMN_SUBCOUNT_DATE_START	, //_T("StartDate"),
	COLUMN_SUBCOUNT_DATE_END	,   //_T("EndDate"),
	COLUMN_SUBCOUNT_RATE		,     //_T("YearRate"),
	COLUMN_SUBCOUNT_PERIOD		,   //_T("TimeSpan"),
	COLUMN_SUBCOUNT_COMMENT		,   //_T("Comment"),
	COLUMN_SUBCOUNT_NUMBER
};

const TCHAR cSubCountFieldName[COLUMN_SUBCOUNT_NUMBER][32] =
{
	_T("Book_ID"),
		_T("SubCountID"),
		_T("Book_Bank"),
		_T("Book_Owner"),
		_T("Total"),
		_T("StartDate"),
		_T("EndDate"),
		_T("YearRate"),
		_T("TimeSpan"),
		_T("Comment")
};


#if 0
extern CString g_strAutoReturnCard;
#endif
extern CString g_strAutoReturnCreditCard;

/////////////////////////////////////////////////////////////////////////////
// CFlagItem class

CFlagItem::CFlagItem(
    CBCGPToolBarImages &icons,
    int nSelectedIcon,
    DWORD dwData) : m_Icons(icons)
{
	m_varValue = (long) nSelectedIcon;
	AllowEdit (FALSE);
}

BOOL CFlagItem::OnClickValue (UINT uiMsg, CPoint point)
{
	if (CBCGPGridItem::OnClickValue (uiMsg, point))
	{
		return TRUE;
	}
	
	if (uiMsg == WM_LBUTTONDOWN)
	{
		int nIndex = (long) m_varValue;
		
		if (nIndex < 0)
		{
			return FALSE;
		}
		
		if (nIndex > m_Icons.GetCount ())
		{
			return FALSE;
		}
		
		// shift nIndex
		nIndex++;
		nIndex %= m_Icons.GetCount ();
		
		m_varValue = (long) nIndex;
		
		CBCGPGridItemID id = GetGridItemID ();
		m_pGridRow->OnItemChanged (this, id.m_nRow, id.m_nColumn);
		Redraw ();
		
		return TRUE;
	}
	
	return FALSE;
}

void CFlagItem::OnDrawValue (CDC* pDC, CRect rect)
{
	int nIndex = (long) m_varValue;
	
	// fill background
	CRect rectFill = rect;
	rectFill.top++;
	rectFill.right++;
	pDC->FillRect (rectFill, &globalData.brLight);
	
	if (nIndex < 0)
	{
		return;
	}
	
	if (nIndex > m_Icons.GetCount ())
	{
		return;
	}
	
	IMAGEINFO imageInfo;
	memset (&imageInfo, 0, sizeof (IMAGEINFO));
	
	CPoint pt = rect.TopLeft ();
	CSize sizeIcon = m_Icons.GetImageSize ();
	
	int xOffset = (rect.Width () - sizeIcon.cx) / 2;
	int yOffset = (rect.Height () - sizeIcon.cy) / 2;
	pt.Offset (max (0, xOffset), max (0, yOffset));
	
	CBCGPDrawState ds;
	m_Icons.PrepareDrawImage (ds);
	m_Icons.Draw (pDC, pt.x, pt.y, nIndex);
	m_Icons.EndDrawImage (ds);
}

/////////////////////////////////////////////////////////////////////////////
// CReportDemoView

IMPLEMENT_DYNCREATE(CReportDemoView, CBCGPReportView)

BEGIN_MESSAGE_MAP(CReportDemoView, CBCGPReportView)
//{{AFX_MSG_MAP(CReportDemoView)
ON_WM_CREATE()
ON_WM_DESTROY()
#if 0//Simon do need?
ON_COMMAND(ID_VIEW_COLUMNSSELECTOR, OnViewColumnsselector)
ON_UPDATE_COMMAND_UI(ID_VIEW_COLUMNSSELECTOR, OnUpdateViewColumnsselector)
ON_COMMAND(ID_VIEW_GROUPBOX, OnViewGroupbox)
ON_UPDATE_COMMAND_UI(ID_VIEW_GROUPBOX, OnUpdateViewGroupbox)
ON_COMMAND(ID_VIEW_COLUMN_AUTO_RESIZE, OnViewColumnAutoResize)
ON_UPDATE_COMMAND_UI(ID_VIEW_COLUMN_AUTO_RESIZE, OnUpdateViewColumnAutoResize)
ON_COMMAND(ID_REPORT_EXPAND_ALL, OnReportExpandAll)
ON_COMMAND(ID_REPORT_COLLAPSE_ALL, OnReportCollapseAll)
#endif
ON_COMMAND(ID_EDIT_CAL_SUM, OnCalsum)
ON_COMMAND(ID_QUERY_ONE_DAY, OnQueryThisDay)
ON_COMMAND(ID_RECORD_EXPORT, OnExportCsv)
ON_COMMAND(ID_RECORD_IMPORT, OnLoadCsv)
ON_COMMAND(ID_RECORD_NEW, OnAddRecord)
ON_COMMAND(IDM_RECTIFYPASSWORD, OnRectifyPassword)
ON_COMMAND(ID_RECORD_DEL_SELECTED, OnDeleteRecord)
ON_COMMAND(ID_RECORD_MODIFY, OnEditRecord)
ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
ON_COMMAND(ID_CAL_CREDIT, OnCalCredit)
ON_COMMAND(ID_EDIT_CREDIT_PERIOD, OnCreditPeroid)
ON_COMMAND(ID_EDIT_SMART_TYPE, OnSmartSetType)
ON_COMMAND(ID_EDIT_REPLACE_COMMENT, OnReplaceComment)
ON_COMMAND(ID_EDIT_TEST, OnEditTest)
ON_COMMAND(ID_ADD_RETURN_RECORD, OnAddReturnRecord)
ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditCopy)
ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdateEditPaste)
ON_COMMAND(IDM_DELETEBOOK, OnDeletebook)
ON_UPDATE_COMMAND_UI(IDM_DELETEBOOK, OnUpdateDeletebook)
ON_COMMAND(IDM_RECTIFYINFO, OnRectifyinfo)
ON_UPDATE_COMMAND_UI(IDM_RECTIFYINFO, OnUpdateRectifyinfo)
ON_COMMAND(IDM_INFO, OnInfo)
ON_UPDATE_COMMAND_UI(IDM_INFO, OnUpdateInfo)
ON_COMMAND(ID_BANKBOOK_FREE, OnBankbookFree)
ON_COMMAND(ID_SET_AS_AUTORETURN_CREDIT, OnSetAsAutoreturnCredit)
ON_COMMAND(ID_TRANSFER_DINGQI, OnTransferDingqi)
ON_COMMAND(ID_FIND_BOOK, OnFindBook)
ON_COMMAND(IDM_MODIFY_SUBCOUNT, OnModifySubcount)
ON_COMMAND(IDM_RENEW_SUBCOUNT, OnRenewSubcount)
ON_COMMAND(ID_OPEN_SUBCOUNT_BY_ID, OnOpenSubcountById)
ON_UPDATE_COMMAND_UI(ID_OPEN_SUBCOUNT_BY_ID, OnUpdateOpenSubcountById)
ON_COMMAND(ID_SUBCOUNT_CLOSE, OnSubcountClose)
ON_UPDATE_COMMAND_UI(ID_SUBCOUNT_CLOSE, OnUpdateSubcountClose)
ON_COMMAND(ID_SUBCOUNT_EXPAND_ACTIVE, OnExpandActiveItem)
ON_COMMAND(ID_SUBCOUNT_EXPAND_ALL, OnExpandAllItem)
ON_COMMAND(ID_SUBCOUNT_SHRINK_ALL, OnCollapseAllItem)
ON_COMMAND(ID_SUBCOUNT_SHRINK_CLOSED, OnCollapseInactiveInactive)
ON_COMMAND_RANGE(ID_THIS_YEAR, ID_THIS_YEAR_7,OnBrowseYear)
ON_UPDATE_COMMAND_UI(ID_ADD_RETURN_RECORD, OnUpdateAddReturnRecord)
ON_UPDATE_COMMAND_UI(ID_TRANSFER_DINGQI, OnUpdateTransferDingqi)
ON_UPDATE_COMMAND_UI(ID_CAL_CREDIT, OnUpdateCalCredit)
ON_COMMAND(ID_CHECK_BILL, OnCheckBill)
ON_COMMAND_RANGE(IDM_COPY_RECORDS_TO, IDM_COPY_RECORDS_TO_END,OnCopyRecordsTo)
ON_COMMAND_RANGE(IDM_MOVE_RECORDS_TO, IDM_MOVE_RECORDS_TO_END,OnMoveRecordsTo)
//}}AFX_MSG_MAP
ON_WM_CONTEXTMENU()
// Standard printing commands
ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
ON_COMMAND(ID_FILE_PRINT_PREVIEW, OnFilePrintPreview)
ON_WM_DROPFILES()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReportDemoView construction/destruction

CReportDemoView::CReportDemoView()
{
	m_bFirst = TRUE;
	// TODO: add construction code here
	
}

CReportDemoView::~CReportDemoView()
{
}

BOOL CReportDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	
	return CBCGPReportView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CReportDemoView drawing

void CReportDemoView::OnDraw(CDC* pDC)
{
	CBCGPReportView::OnDraw (pDC);
}

/////////////////////////////////////////////////////////////////////////////
// CReportDemoView printing

void CReportDemoView::OnFilePrintPreview() 
{
	BCGPPrintPreview (this);
}

BOOL CReportDemoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CReportDemoView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	CBCGPReportView::OnBeginPrinting (pDC, pInfo);
}

void CReportDemoView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	CBCGPReportView::OnEndPrinting (pDC, pInfo);
}

void CReportDemoView::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
	ASSERT_VALID (pDC);
	ASSERT (pInfo != NULL);
	
	// Page margins:
	double dLeftOffset = 0.5;
	double dTopOffset = 0.5;
	double dRightOffset = 0.5;
	double dBottomOffset = 0.5;
	pInfo->m_rectDraw.DeflateRect(
		(int)(pDC->GetDeviceCaps(LOGPIXELSX) * dLeftOffset),
		(int)(pDC->GetDeviceCaps(LOGPIXELSY) * dTopOffset),
		(int)(pDC->GetDeviceCaps(LOGPIXELSX) * dRightOffset),
		(int)(pDC->GetDeviceCaps(LOGPIXELSY) * dBottomOffset));
	
	CBCGPReportView::OnPrint(pDC, pInfo);
}

/////////////////////////////////////////////////////////////////////////////
// CReportDemoView diagnostics

#ifdef _DEBUG
void CReportDemoView::AssertValid() const
{
	CBCGPReportView::AssertValid();
}

void CReportDemoView::Dump(CDumpContext& dc) const
{
	CBCGPReportView::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CReportDemoView message handlers
CStringList g_CountIdList;
void CReportDemoView::OnContextMenu(CWnd*, CPoint point)
{
    CBCGPGridRow* pSel = GetReportCtrl ()->GetCurSel ();
    if (pSel != NULL)
    {
        if (point == CPoint (-1, -1))
        {
            CRect rect = pSel->GetRect ();
            ClientToScreen (&rect);
            
            point.x = rect.left;
            point.y = rect.bottom;
        }
        if(IS_RECORD(m_pParent->m_ViewType))
        {
            if(!pSel->IsGroup())
            {
				CMenu menu;
				menu.LoadMenu(IDR_RECORD_MENU);
				CMenu* pMenu = &menu;
				//To find the menu.
				int n = pMenu->GetMenuItemCount();
				
				theApp.GetAllOpendCount(g_CountIdList);
				if(g_CountIdList.GetCount()>0)
				{

					CMenu sMenu;
					sMenu.CreatePopupMenu();

					CMenu moveMenu;
					moveMenu.CreatePopupMenu();

					POSITION pos = g_CountIdList.GetHeadPosition();
					int n = 0;
                    while (pos)
                    {
						CString strId = g_CountIdList.GetNext(pos);
						sMenu.AppendMenu(MF_STRING,IDM_COPY_RECORDS_TO + n,(LPCTSTR)strId);
						moveMenu.AppendMenu(MF_STRING,IDM_MOVE_RECORDS_TO + n,(LPCTSTR)strId);
						n++;
					}
					HMENU hMenu = sMenu.Detach();


					pMenu->InsertMenu(n,MF_BYPOSITION|MF_POPUP|MF_STRING,
						(UINT)hMenu,"拷贝选定记录到");

					hMenu = moveMenu.Detach();

					pMenu->AppendMenu(MF_BYPOSITION|MF_POPUP|MF_STRING,
						(UINT)hMenu,"移动选定记录到");


					
				}
				
				HMENU hmenu = pMenu->Detach();
                theApp.ShowPopupMenu (hmenu, point, this);
            }
            else
            {
                theApp.ShowPopupMenu (IDR_SUBCOUNT_MENU, point, this);
            }
        }
        else if(VIEW_TYPE_MAIN_COUNTS == m_pParent->m_ViewType)
        {
            theApp.ShowPopupMenu (IDR_BANKBOOK_MENU, point, this);
        }
        else if(VIEW_TYPE_SUB_COUNTS == m_pParent->m_ViewType)
        {
            theApp.ShowPopupMenu (IDR_SUBCOUNT_MENU, point, this);
        }
        else if(VIEW_TYPE_SUB_COUNTS_DETAIL == m_pParent->m_ViewType)
        {
            theApp.ShowPopupMenu (IDR_SUBCOUNT_MANAGER_MENU, point, this);
        }
    }
}

inline int Rand (int nMax)
{
	int nRes = rand () % nMax;
	return min (nRes, nMax - 1);
}

void CReportDemoView::OnInitialUpdate() 
{
	CBCGPReportView::OnInitialUpdate();
#ifdef  LOAD_DATEBASE
	
	
#endif
}

int CReportDemoView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CBCGPReportView::OnCreate(lpCreateStruct) == -1)
		return -1;
	m_pParent = (CReportFrame*)GetParent();
	CBCGPReportCtrl* pReportCtrl = GetReportCtrl ();
	pReportCtrl->SetSingleSel(FALSE);
	//TODO_TODO only single card can accept imported items.
   	DragAcceptFiles(TRUE);
	
	return 0;
}

float CReportDemoView::AddMembertoList(CListSet* pSet,int index,BOOL bCalSum,float sum1)
{
	float sum=sum1;
	
	
	CBCGPReportCtrl* pReportCtrl = GetReportCtrl ();
	
	int count=pReportCtrl->GetColumnCount ();
	CBCGPGridRow* pRow = pReportCtrl->CreateRow (count);
	
	pRow->GetItem (COLUMN_LINE__)->SetImage (pSet->GetAddorSubValue()<0 ? 1 : 0, FALSE);
	pRow->GetItem (COLUMN_LINE__)->SetValue ((long)index, FALSE);
	pRow->GetItem (COLUMN_DATE__)->SetValue (_variant_t((DATE)pSet->m_day,VT_DATE), FALSE);
	pRow->GetItem (COLUMN_CHANGE)->SetValue (atof((LPSTR)(LPCTSTR)pSet->GetAddorSub()), FALSE);
	pRow->GetItem (COLUMN_ID____)->SetValue ((LONG)pSet->m_arraynumber, FALSE);
	pRow->GetItem (COLUMN_REASON)->SetValue ((LPCTSTR)pSet->m_remain, FALSE);
	pRow->GetItem (COLUMN_REASON)->AllowEdit();
	pRow->GetItem (COLUMN_TYPE__)->SetValue ((LPCTSTR)theApp.m_cType[pSet->m_bType], FALSE);
	if(pSet->m_bType == 0)
	{
		CMailReportCtrl::SetRowBackColor(pRow, RGB(191,200,191));
	}
    pRow->GetItem (COLUMN_SITE__)->SetValue ((LPCTSTR)pSet->m_strSite, FALSE);
    pRow->GetItem (COLUMN_SUBCOUNT)->SetValue ((LPCTSTR)pSet->m_strSubCount, FALSE);
	
    pRow->SetData( (DWORD)pSet->m_arraynumber);
	
    if(IS_QUERY(m_ViewType))
    {
        pRow->GetItem (COLUMN_BOOK_ID)->SetValue ((LPCTSTR)pSet->m_ID, FALSE);
        CIDSet idset;
        idset.Open();
        BOOL ret = idset.FindByID(pSet->m_ID);
        //CIDSet * pIdset = theApp.GetIDSet();
        if (ret)
        {
            pRow->GetItem(COLUMN_BOOK_BANK)->SetValue((LPCTSTR)idset.m_bank, FALSE);
        }
        pReportCtrl->AddRow (pRow, FALSE);
        return 0;
		
    }
    if(m_ViewType == VIEW_TYPE_RECORD_IN_ONE_COUNT)
    {
		if(bCalSum)
		{
            //only for query list.
			CString strtrace;
			CString strsum;
			strtrace.Format(_T("\n%9.4f"),sum);
			sum+=pSet->GetAddorSubValue();
			strtrace.Format(_T("+%9.4f=%9.4f"),pSet->GetAddorSubValue(),sum);
			strsum.Format(_T("%8.2f"),sum);
			pRow->GetItem (COLUMN_REMAIN)->SetValue ((LPCTSTR)strsum, FALSE);
			pReportCtrl->AddRow (pRow, FALSE);
			return sum;
		}
        else
        {
            //only for one book list.
            pRow->GetItem (COLUMN_REMAIN)->SetValue ((LPCTSTR)pSet->GetSum(), FALSE);
            pReportCtrl->AddRow (pRow, FALSE);
            return 0;
        }
		
    }
    return 0;
	
	
	
}

void CReportDemoView::OnViewColumnsselector() 
{
	GetReportCtrl ()->ShowColumnsChooser (
		!GetReportCtrl ()->IsColumnsChooserVisible ());
}

void CReportDemoView::OnUpdateViewColumnsselector(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck (GetReportCtrl ()->IsColumnsChooserVisible ());
}

void CReportDemoView::OnDestroy() 
{
	CBCGPReportCtrl* pReportCtrl = GetReportCtrl ();
	ASSERT_VALID (pReportCtrl);
	
	pReportCtrl->SaveState (NULL);
	
	CBCGPReportView::OnDestroy();
}

void CReportDemoView::OnViewGroupbox() 
{
	GetReportCtrl ()->EnableGroupByBox (!GetReportCtrl ()->IsGroupByBox ());
}

void CReportDemoView::OnUpdateViewGroupbox(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck (GetReportCtrl ()->IsGroupByBox ());
}

void CReportDemoView::OnViewColumnAutoResize() 
{
	GetReportCtrl ()->EnableColumnAutoSize (!GetReportCtrl ()->IsColumnAutoSizeEnabled ());
}

void CReportDemoView::OnUpdateViewColumnAutoResize(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck (GetReportCtrl ()->IsColumnAutoSizeEnabled ());
}

void CReportDemoView::OnReportExpandAll() 
{
	GetReportCtrl ()->ExpandAll ();
}

void CReportDemoView::OnReportCollapseAll() 
{
	GetReportCtrl ()->ExpandAll (FALSE);
}

void CReportDemoView::DisplayRecord()
{
#ifdef  LOAD_DATEBASE
	
	TRACE(_T("\nCReportDemoView::DisplayRecord()\n"));
	TRACE("\n ");
    if(m_pParent->m_strFilter.GetLength()<500)
    {
        TRACE(_T("\nthis filter %s\n"),m_pParent->m_strFilter);
    }
	
	CBCGPReportCtrl* pReportCtrl = GetReportCtrl ();
	pReportCtrl->RemoveAll ();
	
    CListSet* pListSet = theApp.GetListSet();
	if(pListSet->m_strFilter != m_pParent->m_strFilter)
	{
        TRACE("oH, refresh me..........\n");
		pListSet->m_strFilter = m_pParent->m_strFilter;
		pListSet->m_strSort = m_pParent->m_strSort;
		pListSet->Requery();
        pListSet->GetGenerationInfo(&(m_pParent->mInformation));
	}
	
	if(pListSet->GetRecordCount()==0)
    {
        TRACE(_T("\npListSet count is 0 return.\n"));
        return;
    }
	pListSet->MoveFirst();
	float sum=0.0;
	int index = 1;
	BOOL bHasSubCount = FALSE;
	while(!pListSet->IsEOF())
	{
		if(VIEW_TYPE_RECORD_IN_ONE_COUNT != m_ViewType)
		{
			sum=AddMembertoList(pListSet,index,TRUE,sum);
		}
		else
		{
			if(pListSet->m_strSubCount.GetLength()>0)
			{
				bHasSubCount = TRUE;
			}
			AddMembertoList(pListSet,index);
		}
		pListSet->MoveNext();
		index++;
	}
	if(VIEW_TYPE_RECORD_IN_ONE_COUNT == m_ViewType)
	{
		if(!bHasSubCount)
		{
			pReportCtrl->RemoveGroupColumn(0);
		}
	}
	
	AdjustColumnWidth();
	pReportCtrl->AdjustLayout ();
	TRACE(_T("\nCReportDemoView::DisplayRecord()  end"));
#endif
}

void CReportDemoView::OnAddRecord() 
{
	if(m_pParent->m_strID.GetLength()>0)
	{
		theApp.AddNewItem(m_pParent->m_strID);
	}
}

void CReportDemoView::OnCalsum() 
{
	if(m_pParent->m_strID!="")
	{
		theApp.CalSum(m_pParent->m_strID);
	}
}

//2018-6-26 17:27
void CReportDemoView::OnQueryThisDay() 
{
	CDWordArray  RowArray;
	CMailReportCtrl* pReportCtrl = (CMailReportCtrl*)GetReportCtrl ();
	int nSelectedCount = pReportCtrl->GetSelectedRows(RowArray);
	if(nSelectedCount != 1)
	{
		return;
	}
	CBCGPGridRow* pRow = pReportCtrl->GetFirstSelectedRow();
	CBCGPGridItem* pItem = pRow->GetItem (COLUMN_DATE__);
	COleDateTime date = (DATE)pItem->GetValue();
	theApp.QueryOneDay(date);
}

void CReportDemoView::OnRectifyPassword() 
{
    if(m_pParent->m_ViewType == VIEW_TYPE_RECORD_IN_ONE_COUNT)
    {
        if(m_pParent->m_strID!="")
        {
            theApp.Rectifypassword(m_pParent->m_strID);
        }
    }
    else if(m_pParent->m_ViewType == VIEW_TYPE_MAIN_COUNTS)
    {
        CBCGPGridRow* pSel = GetReportCtrl ()->GetCurSel ();
        
        if(pSel != NULL)
        {
            theApp.Rectifypassword((LPCTSTR) (_bstr_t)pSel->GetItem(VALUE_MAINCOUNT_TYPE_MAINCOUNT)->GetValue());
        }
    }
}

void CReportDemoView::OnDeleteRecord() 
{
    if(m_pParent->m_ViewType != VIEW_TYPE_RECORD_IN_ONE_COUNT)
    {
        AfxMessageBox("只能在主账户里删除记录！");
        return;
    }
    if(theApp.IsAccountLocked(m_pParent->m_strID))
    {
        return ;
    }

    CMailReportCtrl* pReportCtrl = (CMailReportCtrl*)GetReportCtrl();
    CDWordArray dbAry;
    pReportCtrl->GetSelectedRows(dbAry);
    if(dbAry.GetSize()>0)
    {
        theApp.DeleteRecords(dbAry);
    }
}

void CReportDemoView::OnEditRecord() 
{
	if(IS_RECORD(m_pParent->m_ViewType))
	{
		CBCGPReportCtrl* pReportCtrl = GetReportCtrl();
		CBCGPGridRow* pRow = pReportCtrl->GetCurSel();
		if(pRow != NULL)
		{
			DWORD dwRecordID = pRow->GetData();
    //cant use app default CListSet to edit. when CCurveView update, 
    //the object editMode change to noMode, this made the Update fail.
    //2012-06-04
//#ifdef USE_APP_LIST_SET
#if  1
			CListSet* pListSet = theApp.GetListSet();
#else
            CListSet setEdit;
            setEdit.Open();
			CListSet* pListSet = &setEdit;
#endif
			
			if(pListSet->MoveToID(dwRecordID,m_pParent->m_strFilter))
			{
                if(theApp.IsAccountLocked(pListSet->m_ID))
                {
                    return;
                }
				CAddNewItemDlg dlg;
				dlg.m_bNewItem=FALSE;
				dlg.m_date=pListSet->m_day;
				dlg.m_id=pListSet->m_ID;
				dlg.m_sum=pListSet->m_addorsub;
				dlg.m_remain=pListSet->m_remain;
				dlg.m_nType=pListSet->m_bType;
                dlg.m_strSubCount = pListSet->m_strSubCount;
                dlg.m_strSite = pListSet->m_strSite;
				if(dlg.DoModal()!=IDOK)
					return;
				CListSet listData;
//				pListSet->Edit();
				listData.m_day=dlg.m_date;
				listData.m_addorsub=dlg.m_sum;
				listData.m_remain=dlg.m_remain;
				listData.m_bType=dlg.m_nType;
                listData.m_strSite =dlg.m_strSite;
                listData.m_strSubCount = dlg.m_strSubCount;
				listData.m_ID = pListSet->m_ID;
				BOOL b = pListSet->Modify_Record(&listData);
//				BOOL b = pListSet->Update();
                if(!b)
                {
                    ::MessageBox(this->GetSafeHwnd(),"提交失败！","Edit Mode",MB_OK);
                }
                else
                {
                    theApp.ForceUpdateViews();
                }
				SetSelectedRow(dwRecordID);
			}
		}
	}
}


/*******************************************
    Function Name : 
    author        : Qiu Guohua
    Date          : 2009-2-14 18:11:27
    Description   : 
    Return type  : 
    Argument      : 
********************************************/
void CReportDemoView::OnEditPaste() 
{
	if(m_pParent->m_strID == _T(""))
	{
		AfxMessageBox(_T("当前窗口不是存折窗口，不能粘贴！"));
		return;
	}
    if(theApp.IsAccountLocked(m_pParent->m_strID))
    {
		AfxMessageBox(_T("当前账户已经锁定，不能粘贴！"));
        return ;
    }
	
	UINT uFormat=NULL;
	TRACE("OUR FORMAT IS %d\n",CSmallHorseApp::m_DataFormat);
	OpenClipboard();
    do
    {
		uFormat = EnumClipboardFormats(uFormat);
		TRACE("clip format :%d\n",uFormat);
	}while(uFormat!=NULL);
	CloseClipboard();
	
	if(IsClipboardFormatAvailable(CSmallHorseApp::m_DataFormat))
	{
		//cant use app default CListSet to edit. when CCurveView update, 
		//the object editMode change to noMode, this made the AddNew fail.
		//2012-06-04
		if (OpenClipboard())
		{
			// CListSet* pListSet = theApp.GetListSet();
			HANDLE hData = ::GetClipboardData(CSmallHorseApp::m_DataFormat);
			CloseClipboard();
			
			if (hData != NULL)
			{
				CSharedFile memFile;
				memFile.SetHandle(hData,FALSE);
				CArchive ar(&memFile, CArchive::load);
				// Serialize data to document
				// if(pListSet->GetRecordCount())
				// {
				// 	pListSet->Requery();
				// 	pListSet->MoveLast();
				// }
				//	        pListSet->AddNew();
				CListSet listData;
				DoSerialize(ar,&listData,TRUE);
				TRACE(_T("before save    %s\n"),listData.m_remain);
				ar.Close();
#if _MFC_VER <= 0x0420
				::GlobalUnlock(memFile.Detach());
#else
				memFile.Detach();
#endif
				
				CAddNewItemDlg dlg;
				dlg.m_bNewItem = FALSE;
				dlg.m_date = listData.m_day;
				dlg.m_id = m_pParent->m_strID;
				dlg.m_sum = listData.m_addorsub;
				dlg.m_remain = listData.m_remain;
				dlg.m_nType = listData.m_bType;
				dlg.m_strSubCount = listData.m_strSubCount;
				dlg.m_strSite = listData.m_strSite;
#ifdef SUBMIT_DATA_IN_DIALOG
				dlg.m_pSet = &listData;
				listData.StartEdit();
#endif
				if (dlg.DoModal() == IDOK)
				{
#ifndef SUBMIT_DATA_IN_DIALOG
					listData.StartEdit();
					listData.AddNew();
					listData.m_day=dlg.m_date;
					listData.m_addorsub=dlg.m_sum;
					listData.m_remain=dlg.m_remain;
					listData.m_bType=dlg.m_nType;
					listData.m_strSite =dlg.m_strSite;
					listData.m_strSubCount = dlg.m_strSubCount;
					listData.m_ID = dlg.m_id;
					int ret = listData.SubmitNew();
					listData.EndEdit();
					//BOOL b = pListSet->New_Item(&listData);
					if(ret)
					{
						::MessageBox(this->GetSafeHwnd(),"提交失败！","EditPaste Mode",MB_OK);
					}
#endif

					SelectMaxIndexItem();
				}
#ifdef SUBMIT_DATA_IN_DIALOG
				listData.EndEdit();
#endif
			}
			else
			{
				AfxMessageBox(_T("Couldn't get clipboard data"));
			}
			CloseClipboard();
		}
		else
		{
			AfxMessageBox(_T("Couldn't open clipboard!"));
		}
	}
	else if(IsClipboardFormatAvailable(CF_UNICODETEXT) )
	{
		CImportSheet sheet(theApp.GetListSet(),m_pParent->m_strID);
		sheet.DoModal();
		theApp.ForceUpdateViews();
	}
	
}


/*******************************************
    Function Name : 
    author        : Qiu Guohua
    Date          : 2009-2-14 18:09:54
    Description   : 
    Return type  : 
    Argument      : 
********************************************/
void CReportDemoView::OnEditCopy() 
{
    if(m_pParent->m_strID == _T(""))
    {
        AfxMessageBox(_T("当前窗口不是存折窗口，不能复制！"));
        return;
    }
    CMailReportCtrl* pReportCtrl = (CMailReportCtrl*)GetReportCtrl();
	CBCGPGridRow* pRow = pReportCtrl->GetCurSel();
	if(pRow != NULL)
	{
		DWORD dwRecordID = pRow->GetData();
		CListSet* pSet = theApp.GetListSet();
		if(pSet->MoveToID(dwRecordID,m_pParent->m_strFilter))
		{
			CSharedFile memFile;
			CArchive ar(&memFile, CArchive::store|CArchive::bNoFlushOnDelete);
			DoSerialize(ar,pSet,FALSE);
			ar.Flush();
			HGLOBAL hData = memFile.Detach();
#if _MFC_VER <= 0x0420
			::GlobalUnlock(hData);
#endif
			if (OpenClipboard())
			{
				::SetClipboardData(CSmallHorseApp::m_DataFormat, hData);
				CloseClipboard();
			}
			else
			{
				AfxMessageBox(_T("Couldn't open clipboard!"));
			}
		}
	}
}

void CReportDemoView::OnExportCsv() 
{
    CMailReportCtrl* pReportCtrl = (CMailReportCtrl*)GetReportCtrl();
    CCSVFile csv;
    csv.SaveTo(pReportCtrl,TRUE);
    
}

void CReportDemoView::OnLoadCsv() 
{
	if(m_pParent->m_strID != _T(""))
	{
        if(theApp.IsAccountLocked(m_pParent->m_strID))
        {
            return ;
        }


		TRACE("Will load to %s",m_pParent->m_strID);
		CListSet* pSet = theApp.GetListSet();
		pSet->m_strFilter = m_pParent->m_strFilter;
		pSet->Requery();
		CImportSheet sheet(_T(""),pSet,m_pParent->m_strID);
		sheet.DoModal();
        theApp.ForceUpdateViews();
	}
	else
	{
		AfxMessageBox(_T("只能加入到一个存折中,请先选择一个存折!"));
		return;
	}
}


// /*******************************************
//     Function Name : 
//     author        : Qiu Guohua
//     Date          : 2009-4-27 22:41:41
//     Description   : 
//     Return type  : 
//     Argument      : 
// ********************************************/
// void CReportDemoView::OnLoadSubCountCsv() 
// {
// 	if(m_pParent->m_strID != _T(""))
// 	{
// 		CImportSheet sheet(_T(""),theApp.GetSubCountSet(),IMPORT_TYPE_SUBCONT);
// 		sheet.m_strMainCount = m_pParent->m_strID;
// 		sheet.DoModal();
// 		theApp.ForceUpdateViews();
// 	}
// 	else
// 	{
// 		AfxMessageBox(_T("只能加入到一个账户中,请先选择一个账户!"));
// 		return;
// 	}
// }

void CReportDemoView::OnCalCredit() 
{
	if(IS_RECORD(m_pParent->m_ViewType))
	{
		CMailReportCtrl* pReportCtrl = (CMailReportCtrl*)GetReportCtrl();
		CBCGPGridRow * prow = pReportCtrl->GetFirstSelectedRow();
		COleDateTime time;
		if(prow)
		{
			time = (DATE)prow->GetItem(COLUMN_DATE__)->GetValue();
		}
		else
		{
			time = COleDateTime::GetCurrentTime();
		}
		DisplayCreditDetail(time.GetYear(),time.GetMonth());
	}
}




void CReportDemoView::OnCreditPeroid() 
{
	CCheckCountDateSetup dlg;
	if(dlg.DoModal() == IDOK)
	{
		CString str;
		str.Format(_T("%d %d"),dlg.m_dateEnd,dlg.m_datePay);
		AfxMessageBox(str);
	}
	
}

void CReportDemoView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
  TRACE(_T("CReportDemoView::OnUpdate begin.\n"));
	if((m_pParent->m_strFilter == _T(""))&&(IS_RECORD(m_pParent->m_ViewType)))
	{//dont show all records.
        TRACE(_T("FILTER IS NULL... UPDATE FAILED.\n"));
//		return ;
	}
	if(m_bFirst)
	{
		CreateListCtrl();
		if(IS_RECORD(m_pParent->m_ViewType))
		{
			m_pParent->CreateCurveView();
		}
		m_bFirst = FALSE;
	}
    TRACE(_T("CReportDemoView::OnUpdate begin %s.\n"),m_pParent->m_strFilter);
	FillItems();
}

#define SERIALIZE(oper) \
ar oper pList->m_day; \
ar oper pList->m_addorsub; \
ar oper pList->m_remain; \
ar oper pList->m_bType; \
ar oper pList->m_strSubCount; \
ar oper pList->m_strSite;

void CReportDemoView::DoSerialize(CArchive &ar, CListSet *pList, BOOL bToList)
{
	if(bToList)
	{
         SERIALIZE(>>);
         TRACE(_T("aaaaa    %s\n"),pList->m_strSite);
         TRACE(_T("aaaaa    %s\n"),pList->m_remain);
	}
	else
	{
		SERIALIZE(<<);
        TRACE(_T("bbbbb    %s\n"),pList->m_strSite);
        TRACE(_T("bbbbb    %s\n"),pList->m_remain);
	}
}

/*******************************************
    Function Name :	 
    Create by     :	  Qiu Guohua
    Input         :   
    Output        :   
    Description   :   
    Date          :   2007-1-11
********************************************/

void CReportDemoView::SelectMaxIndexItem()
{
	CBCGPReportCtrl* pReportCtrl = GetReportCtrl();
	CBCGPGridRow* pRow = NULL;
	int nCount = pReportCtrl->GetRowCount();

	int nMax = -1;
	int nMaxIndex = 0;
	for(int index = 0;index < nCount;index++)
	{
		pRow = pReportCtrl->GetRow(index);
		DWORD dw = pRow->GetData();
		if(nMax <= (int)dw)
		{
			nMaxIndex = index;
			nMax = (int)dw;
		}
	}
	pRow = pReportCtrl->GetRow(nMaxIndex);
	pReportCtrl->SetCurSel(pRow);
}


/*******************************************
    Function Name : 
    author        : Qiu Guohua
    Date          : 2009-2-14 20:35:08
    Description   : 
    Return type  : 
    Argument      : 
********************************************/
void CReportDemoView::SetSelectedRow(const int nRecordArray)
{
	CBCGPReportCtrl* pReportCtrl = GetReportCtrl();
	CBCGPGridRow* pRow = NULL;
	int nCount = pReportCtrl->GetRowCount();

	for(int index = 0;index < nCount;index++)
	{
		pRow = pReportCtrl->GetRow(index);
		DWORD dw = pRow->GetData();
		if(nRecordArray == (int)dw)
		{
			pReportCtrl->SetCurSel(pRow);
			return;
		}
	}
}


/*******************************************
    Function Name : 
    author        : Qiu Guohua
    Date          : 2009-2-14 22:53:00
    Description   : 
    Return type  : no used. to get max width for every column.
    Argument      : 
********************************************/
void CReportDemoView::AdjustColumnWidth()
{
	CBCGPReportCtrl* pReportCtrl = GetReportCtrl();
	pReportCtrl->EnableColumnAutoSize();

}



/*******************************************
    Function Name : 
    author        : Qiu Guohua
    Date          : 2009-4-24 21:49:20
    Description   : 
    Return type  : 
    Argument      : 
********************************************/
void CReportDemoView::CreateListCtrl()
{
	CMailReportCtrl* pReportCtrl = (CMailReportCtrl*)GetReportCtrl ();
	ASSERT_VALID (pReportCtrl);
	pReportCtrl->ModifyStyle(LVS_SINGLESEL   , 0);   
	m_ViewType = m_pParent->GetViewType();
	//------------------
	// Load grid images:
	//------------------
	CBitmap bmp;
	bmp.LoadBitmap (IDB_LIST_IMAGES);

	m_Images.Create (16, 16, ILC_COLOR24 | ILC_MASK, 0, 0);
	m_Images.Add (&bmp, RGB (255, 0, 255));

	pReportCtrl->SetImageList (&m_Images);
#if 0 //Simon no need
	//------------------------------
	// Load images for "flag" items:
	//------------------------------
	m_Flags.SetImageSize (CSize (14, 14));
	m_Flags.SetTransparentColor (RGB (255, 0, 255));
	m_Flags.Load (IDB_FLAGS256);
#endif
	//----------------
	// Insert columns:
	//----------------

    if(IS_REPORT(m_pParent->m_ViewType))
    {
		pReportCtrl->InsertColumn (COLUMN_REPORT_START_TIME, _T("开始"), 50);
		pReportCtrl->InsertColumn (COLUMN_REPORT_END_TIME, _T("结束"), 50);
		pReportCtrl->InsertColumn (COLUMN_REPORT_EXPENSE, _T("花费"), 50);
  		pReportCtrl->InsertColumn (COLUMN_REPORT_REPAY, _T("还款"), 50);
  		pReportCtrl->InsertColumn (COLUMN_REPORT_GAP, _T("差"), 50);
  		pReportCtrl->InsertColumn (CLOUMN_REPORT_ACCOUNT_GAP, _T("积差"), 50);
    }
	else if(IS_RECORD(m_pParent->m_ViewType))
	{
		pReportCtrl->InsertColumn (COLUMN_LINE__, _T("顺序"), 15);
		pReportCtrl->InsertColumn (COLUMN_DATE__, _T("日期"), 30);
		pReportCtrl->InsertColumn (COLUMN_CHANGE, _T("收支"), 30);
		pReportCtrl->InsertColumn (COLUMN_ID____, _T("序号"), 15);
		pReportCtrl->InsertColumn (COLUMN_REASON, _T("事由"), 120);
		pReportCtrl->InsertColumn (COLUMN_TYPE__, _T("类型"), 20);
		pReportCtrl->InsertColumn (COLUMN_SITE__, _T("地点"), 30);
		pReportCtrl->InsertColumn (COLUMN_SUBCOUNT, _T("子账号"), 1);

		if(m_ViewType == VIEW_TYPE_RECORD_IN_ONE_COUNT)
		{
			pReportCtrl->InsertColumn (COLUMN_REMAIN, _T("余额"), 30);
			pReportCtrl->SetColumnVisible (COLUMN_SUBCOUNT, FALSE);
			pReportCtrl->InsertGroupColumn (0, COLUMN_SUBCOUNT );
		}
		else if(IS_QUERY(m_ViewType))
		{
			pReportCtrl->InsertColumn (COLUMN_BOOK_ID, _T("账户"), 40);
			pReportCtrl->InsertColumn (COLUMN_BOOK_BANK, _T("银行"), 30);
		}
	}
    else if(IS_TODO(m_pParent->m_ViewType))
    {
        pReportCtrl->InsertColumn (COLUMN_TODO_ID, _T("序号"), 15);
        pReportCtrl->InsertColumn (COLUMN_TODO_BODY, _T("内容"), 30);
    }
	else if(IS_SIMPLE_SUBCOUNT(m_pParent->m_ViewType))
	{
		pReportCtrl->InsertColumn (COLUMN_SIMPLE_SUBCOUNT_NAME, _T("子账户名"), 50);
		pReportCtrl->InsertColumn (COLUMN_SIMPLE_SUBCOUNT_REMAIN, _T("余额"), 30);
	}
	else if(IS_DETAIL_SUBCOUNT(m_pParent->m_ViewType))
	{
        pReportCtrl->InsertColumn(COLUMN_DETAIL_SUBCOUNT_BANK, _T("银行"), 60);          
        pReportCtrl->InsertColumn(COLUMN_DETAIL_SUBCOUNT_OWNER, _T("户主"), 30);         
        pReportCtrl->InsertColumn(COLUMN_DETAIL_SUBCOUNT_ID, _T("账号"), 40);            
        pReportCtrl->InsertColumn(COLUMN_DETAIL_SUBCOUNT_VALUE, _T("金额"), 20);         
        pReportCtrl->InsertColumn(COLUMN_DETAIL_SUBCOUNT_START_DATE, _T("开户日"), 25);  
        pReportCtrl->InsertColumn(COLUMN_DETAIL_SUBCOUNT_END_DATE, _T("到期日"), 30);    
        pReportCtrl->InsertColumn(COLUMN_DETAIL_SUBCOUNT_RATE, _T("利率"), 30);          
        pReportCtrl->InsertColumn(COLUMN_DETAIL_SUBCOUNT_TIMESPAN, _T("存期"), 20);      
        pReportCtrl->InsertColumn(COLUMN_DETAIL_SUBCOUNT_COMMENT, _T("注释"), 20);       
        pReportCtrl->InsertColumn(COLUMN_DETAIL_SUBCOUNT_STATUS, _T("状态"), 20);
	}
	else
	{
		if(m_ViewType == VIEW_TYPE_MAIN_COUNTS)
		{
			pReportCtrl->InsertColumn (VALUE_MAINCOUNT_TYPE_MAINCOUNT, cMainCountRegionName[VALUE_MAINCOUNT_TYPE_MAINCOUNT], 25);
			pReportCtrl->InsertColumn (VALUE_MAINCOUNT_TYPE_BANK, cMainCountRegionName[VALUE_MAINCOUNT_TYPE_BANK], 20);
			pReportCtrl->InsertColumn (VALUE_MAINCOUNT_TYPE_OWNER, cMainCountRegionName[VALUE_MAINCOUNT_TYPE_OWNER], 8);
			pReportCtrl->InsertColumn (VALUE_MAINCOUNT_TYPE_VALUE, cMainCountRegionName[VALUE_MAINCOUNT_TYPE_VALUE], 12);
			pReportCtrl->InsertColumn (VALUE_MAINCOUNT_TYPE_COMMENT, cMainCountRegionName[VALUE_MAINCOUNT_TYPE_COMMENT], 65);
			pReportCtrl->SetDbClkCBFunc(Callback_OnItemDbClk);
		}
		else
		{
			pReportCtrl->InsertColumn (COLUMN_SUBCOUNT_MAINCOUNT, _T("账号"), 60);
			pReportCtrl->InsertColumn (COLUMN_SUBCOUNT_SUBCOUNT	, _T("子账号"), 30);
			pReportCtrl->InsertColumn (COLUMN_SUBCOUNT_BANK		, _T("银行"), 40);
			pReportCtrl->InsertColumn (COLUMN_SUBCOUNT_OWNER	, _T("户主"), 20);
			pReportCtrl->InsertColumn (COLUMN_SUBCOUNT_VALUE	, _T("余额"), 25);
			pReportCtrl->InsertColumn (COLUMN_SUBCOUNT_DATE_START, _T("开户日"), 30);
			pReportCtrl->InsertColumn (COLUMN_SUBCOUNT_DATE_END	, _T("到期日"), 30);
			pReportCtrl->InsertColumn (COLUMN_SUBCOUNT_RATE		, _T("利率"), 20);
			pReportCtrl->InsertColumn (COLUMN_SUBCOUNT_PERIOD	, _T("存期"), 20);
			pReportCtrl->InsertColumn (COLUMN_SUBCOUNT_COMMENT	, _T("备注"), 70);
		}
	}

//	pReportCtrl->SetColumnAlign (1, HDF_RIGHT);	// Icon
//	pReportCtrl->SetColumnAlign (9, HDF_RIGHT);	// Size
/*
	pReportCtrl->SetColumnLocked (0);

	pReportCtrl->SetColumnVisible (5, FALSE);
*/
	//-------------------
	// Set group columns:
	//-------------------

	//--------------------------
	// Create header image list:
	//--------------------------
#if 0 //Simon no need
	const int nImageWidth = 12;
	m_ImagesHeader.Create (IDB_HEADER_IMAGES, nImageWidth, 0, RGB (255, 0, 255));

	pReportCtrl->SetHeaderImageList (&m_ImagesHeader);
#endif
	pReportCtrl->EnableHeader ();
	pReportCtrl->EnableColumnAutoSize (TRUE);

	pReportCtrl->SetWholeRowSel (TRUE);
	pReportCtrl->EnableMarkSortedColumn (TRUE);

//	pReportCtrl->EnableGroupByBox (TRUE);
	
//	pReportCtrl->LoadState (NULL);

}

#define	DB_DATE_TIME(v) _variant_t((DATE)COleDateTime(v.m_pdate->year,\
                                     v.m_pdate->month,\
                                     v.m_pdate->day,\
                                     v.m_pdate->hour,\
                                     v.m_pdate->minute,\
                                     v.m_pdate->second),VT_DATE)

void CReportDemoView::AddSubCount2List(int index,CRecordset* pSet)
{
	CBCGPReportCtrl* pReportCtrl = GetReportCtrl ();

	int count=pReportCtrl->GetColumnCount ();
	CBCGPGridRow* pRow = pReportCtrl->CreateRow (count);

	CDBVariant varint;


		CString strValue;

    for(int i=0;i<COLUMN_SUBCOUNT_NUMBER;i++)
    {
      switch(i)
      {
      case COLUMN_SUBCOUNT_MAINCOUNT:
      case COLUMN_SUBCOUNT_SUBCOUNT:
      case COLUMN_SUBCOUNT_BANK:
      case COLUMN_SUBCOUNT_OWNER:
      case COLUMN_SUBCOUNT_COMMENT:
		  pSet->GetFieldValue(cSubCountFieldName[i],strValue);
	      pRow->GetItem (i)->SetValue ((LPCTSTR)strValue, FALSE);
        break;
      case COLUMN_SUBCOUNT_VALUE:
          pSet->GetFieldValue(cSubCountFieldName[i],strValue);

          pRow->GetItem (i)->SetValue (atof((LPCTSTR)strValue), FALSE);
          break;
      case COLUMN_SUBCOUNT_RATE:
      case COLUMN_SUBCOUNT_DATE_START:
      case COLUMN_SUBCOUNT_DATE_END:
      case COLUMN_SUBCOUNT_PERIOD:
        pSet->GetFieldValue(cSubCountFieldName[i],varint);
//        TRACE("type %d %d\n",i,varint.m_dwType);
        if(varint.m_dwType == DBVT_DATE)
        {
          pRow->GetItem (i)->SetValue (DB_DATE_TIME(varint), FALSE);
        }
        else if(varint.m_dwType == DBVT_SINGLE)
        {
          pRow->GetItem (i)->SetValue (_variant_t(varint.m_fltVal), FALSE);
        }
        else if(varint.m_dwType == DBVT_LONG)
        {
          pRow->GetItem (i)->SetValue (varint.m_iVal, FALSE);
        }
        break;
      }
    }
	pReportCtrl->AddRow (pRow, FALSE);

}


typedef enum 
{
    COUNT_ORDER_BY_NONE,
    COUNT_ORDER_BY_BANK,
    COUNT_ORDER_BY_PEOPLE
}Order_Count_Enum;
void CReportDemoView::DisplayCount()
{
    m_total = 0.0f;
    m_nStaticCount = 0;
#ifdef  LOAD_DATEBASE
    TRACE(_T("\nbegin DisplayRecord"));
    TRACE(_T("\n "));
    if (m_pParent->m_strFilter.GetLength() < 500)
        TRACE(_T("\n %s"), m_pParent->m_strFilter);
    Order_Count_Enum order = COUNT_ORDER_BY_NONE;
    if (m_pParent->m_strFilter.Find(SQL_ORDER_BY_BANK, 0) >= 0)
    {
        order = COUNT_ORDER_BY_BANK;

    }
    else if (m_pParent->m_strFilter.Find(SQL_ORDER_BY_OWNER, 0) >= 0)
    {
        order = COUNT_ORDER_BY_PEOPLE;
    }

    CBCGPReportCtrl* pReportCtrl = GetReportCtrl();
    pReportCtrl->RemoveAll();

    CDatabase dtbs;
    BOOL b = dtbs.OpenEx(DATA_SOURCE_NAME, CDatabase::openReadOnly | CDatabase::noOdbcDialog);
    CRecordset set(&dtbs);

    b = set.Open(CRecordset::snapshot, m_pParent->m_strFilter);
    TRACE("\nfilter: %s\n", m_pParent->m_strFilter);
    int n = set.GetRecordCount();
    TRACE("\ntotal count %d %d.......\n", n, set.GetODBCFieldCount());
    if (m_pParent->m_ViewType == VIEW_TYPE_MAIN_COUNTS)
    {
        int index = 1;
        while (!set.IsEOF())
        {
            static CString strBank;
            static BOOL bbb = TRUE;
            CDBVariant varint;
            CBCGPGridRow* pRow = pReportCtrl->CreateRow(VALUE_MAINCOUNT_TYPE_number);
            CString strValue;
            set.GetFieldValue((short)0, strValue);
            pRow->GetItem(VALUE_MAINCOUNT_TYPE_MAINCOUNT)->SetValue((LPCTSTR)strValue, FALSE);


            set.GetFieldValue((short)1, strValue);
            if (order == COUNT_ORDER_BY_BANK)
            {
                if (strValue != strBank)
                {
                    strBank = strValue;
                    bbb = !bbb;
                }
                if (bbb)
                {
                    CMailReportCtrl::SetRowBackColor(pRow, RGB(192, 255, 255));
                }
                else
                {
                    CMailReportCtrl::SetRowBackColor(pRow, RGB(211, 255, 211));
                }
            }
            pRow->GetItem(VALUE_MAINCOUNT_TYPE_BANK)->SetValue((LPCTSTR)strValue, FALSE);
            set.GetFieldValue((short)2, strValue);
            if (order == COUNT_ORDER_BY_PEOPLE)
            {
                if (strValue != strBank)
                {
                    strBank = strValue;
                    bbb = !bbb;
                }
                if (bbb)
                {
                    CMailReportCtrl::SetRowBackColor(pRow, RGB(122, 212, 255));
                }
                else
                {
                    CMailReportCtrl::SetRowBackColor(pRow, RGB(211, 255, 221));
                }

            }
            pRow->GetItem(VALUE_MAINCOUNT_TYPE_OWNER)->SetValue((LPCTSTR)strValue, FALSE);
            set.GetFieldValue((short)3, varint, SQL_REAL);
            pRow->GetItem(VALUE_MAINCOUNT_TYPE_VALUE)->SetValue(varint.m_fltVal, FALSE);
            //todo
            m_total += varint.m_fltVal;
            m_nStaticCount++;
            set.GetFieldValue((short)4, strValue);
            pRow->GetItem(VALUE_MAINCOUNT_TYPE_COMMENT)->SetValue((LPCTSTR)strValue, FALSE);
            set.GetFieldValue((short)5, varint, SQL_C_BIT);

            pRow->GetItem(VALUE_MAINCOUNT_TYPE_MAINCOUNT)->SetImage(varint.m_boolVal ? 2 : 3, FALSE);

            pReportCtrl->AddRow(pRow, FALSE);
            set.MoveNext();
            index++;
        }
    }
    else if (m_pParent->m_ViewType == VIEW_TYPE_SUB_COUNTS)
    {
        int index = 1;
        while (!set.IsEOF())
        {
            AddSubCount2List(index, &set);
            set.MoveNext();
            index++;
        }
    }
    set.Close();
    dtbs.Close();



    AdjustColumnWidth();
    pReportCtrl->AdjustLayout();
#endif
}





void CReportDemoView::Callback_OnItemDbClk(LPVOID pThis,CBCGPGridRow* pRow)
{
	if(pRow != NULL)
	{
		theApp.OpenBankbook((LPCTSTR) (_bstr_t)pRow->GetItem(VALUE_MAINCOUNT_TYPE_MAINCOUNT)->GetValue());
	}
}

void CReportDemoView::OnSmartSetType() 
{
	CDWordArray  RowArray;
	CMailReportCtrl* pReportCtrl = (CMailReportCtrl*)GetReportCtrl ();
	int nSelectedCount = pReportCtrl->GetSelectedRows(RowArray);
	if(nSelectedCount == 0)
	{
		return;
	}
	
    CSmartSetDlg dlg;
	if(dlg.DoModal() ==IDOK)
	{
		CListSet* pListSet = theApp.GetListSet();
		if(dlg.m_bActiveSite)
		{
			pListSet->Modify_Site_ByComment(dlg.m_strSite,dlg.m_strNoString,dlg.m_strYesString,RowArray,nSelectedCount);
		}
		if(dlg.m_bActiveType)
		{
			pListSet->Modify_Type_ByComment(dlg.m_nTypeIndex,dlg.m_strNoString,dlg.m_strYesString,RowArray,nSelectedCount);
		}
        theApp.ForceUpdateViews();
	}
}
void CReportDemoView::OnEditTest() 
{
/*	CListSet* pListSet = theApp.GetListSet();


	CString strSQL="update Items set Oper=0-Oper where Index between 9945 and 10016";

	TRACE("%s\n",strSQL);
	pListSet->m_pDatabase->ExecuteSQL(strSQL);

	theApp.ForceUpdateViews();*/
}

void CReportDemoView::OnReplaceComment() 
{
	CDWordArray  RowArray;
	CMailReportCtrl* pReportCtrl = (CMailReportCtrl*)GetReportCtrl ();
	int nSelectedCount = pReportCtrl->GetSelectedRows(RowArray);
	if(nSelectedCount == 0)
	{
		return;
	}
	
    CReplaceStringDlg dlg;
	if(dlg.DoModal() ==IDOK)
	{
		CListSet* pListSet = theApp.GetListSet();
		pListSet->Replace_Comment(dlg.m_strOldString,dlg.m_strNewString,RowArray,nSelectedCount);
        theApp.ForceUpdateViews();
	}
}


void CReportDemoView::DisplayCreditDetail(int nYear, int nMonth)
{
	if( VIEW_TYPE_RECORD_IN_ONE_COUNT!=m_pParent->m_ViewType)
	{
		AfxMessageBox(_T("只能统计一个卡,请先选择一个!"));
		return;
	}
	CPeriodSetupDlg dlg;
    COleDateTime timeBegin;
	COleDateTime timeEnd;
	COleDateTime timePay;

    CCreditPaySet set;
    BOOL b = set.GetPayInfo(m_pParent->m_strID,nYear,nMonth,timeBegin,timeEnd,timePay);
    if(b)
    {
        dlg.m_timeBegin = timeBegin;
        dlg.m_timeEnd = timeEnd;
        dlg.m_timePay = timePay;
    }
    else
    {
        int premonth = nMonth - 1;
        int preyear = nYear;
        int endmonth = nMonth + 1;
        int endyear = nYear;
        if(premonth == 0)
        {
            premonth = 12;
            preyear -= 1;
        }
        if(endmonth > 12)
        {
            endmonth = 1;
            endyear += 1;
        }
        COleDateTime time(preyear,premonth,25,0,0,0);
        COleDateTime end_time(nYear,nMonth,24,23,59,59);
        COleDateTime timepay(endyear,endmonth,13,12,0,0);
        dlg.m_timeBegin = time;
        dlg.m_timeEnd = end_time;
        dlg.m_timePay = timepay;
    }


	if(dlg.DoModal() != IDOK)
	{
		return;
	}
	ExportCreditRecord(dlg.m_timeBegin,dlg.m_timeEnd,dlg.m_timePay);
}

void CReportDemoView::ExportCreditRecord(const COleDateTime &timeBegin, const COleDateTime &timeEnd,const COleDateTime& timePay)
{
	CString strFile(_T("C:\\test.htm"));
	CGridHtmlExporter exporter;
//exporter.SetExportFile(strFile);
    CListSet* pListSet = theApp.GetListSet();   
    pListSet->m_strFilter = m_pParent->m_strFilter;
    pListSet->Requery();
    if(!pListSet->IsBOF())
    {
        pListSet->MoveFirst();
    }
	float fSum = 0.0;
	float fThisSum;
	CString str,str1;
	UINT uColor = 0x6eb0ff;
	while(!pListSet->IsEOF())
	{
		if(pListSet->m_day >= timeBegin && pListSet->m_day <= timeEnd)
		{
			fThisSum = pListSet->GetAddorSubValue();
			if(fThisSum<0)
			{
				fSum += fThisSum;
			//exporter.ExportLine(pListSet->GetDate(),pListSet->m_addorsub,pListSet->m_remain,uColor);
			}
		}
		pListSet->MoveNext();
	}
	str = timePay.Format("%Y-%m-%d");
	str1.Format("%8.2f",-fSum);
//exporter.ExportLine(str,str1,"Bankbook自动生成还款额.",0x3591ff);
//exporter.ExportTail();
//exporter.CloseFile();
	ShellExecute( AfxGetMainWnd()->m_hWnd, "open", strFile, NULL, NULL, SW_SHOWNORMAL );
}

void CReportDemoView::OnAddReturnRecord() 
{
	if( VIEW_TYPE_RECORD_IN_ONE_COUNT!=m_pParent->m_ViewType)
	{
		AfxMessageBox(_T("只能统计一个卡,请先选择一个!"));
		return;
	}
	
	CMailReportCtrl* pReportCtrl = (CMailReportCtrl*)GetReportCtrl ();
    CListSet* pListSet = theApp.GetListSet();
#if 0//no need to set a pay card.
    if(m_pParent->m_strID != g_strAutoReturnCard)
    {
        AfxMessageBox(_T("当前账号没有绑定信用卡，请设置后再做。!"));
        return;
    }
#endif
    if(g_strAutoReturnCreditCard == _T(""))
    {
        AfxMessageBox(_T("没有绑定的信用卡，请设置后再做。!"));
        return;
    }
	
	CBCGPGridRow* pRow = pReportCtrl->GetFirstSelectedRow();
	if(pRow == NULL)
	{
        AfxMessageBox(_T("先选择一条你要转的记录!"));
        return;
	}
    DWORD thisIndex = pRow->GetData();
	
	BOOL b = pListSet->MoveToID(thisIndex);
	
    if(!b)
    {
        AfxMessageBox(_T("记录有误!"));
        return;
    }
	
    CString	addorsub = pListSet->m_addorsub;
    if(addorsub.Left(1) != _T("-"))
    {
        AfxMessageBox(_T("必须为负数才可以!"));
        return;
    }
	
    addorsub.Delete(0,1);
    COleDateTime  day = pListSet->m_day;
    CString	strRemain = pListSet->m_remain;
	CString strSite = pListSet->m_strSite;
	
    CString strTo;
    strTo.Format(_T("To %s"),g_strAutoReturnCreditCard);
	
    if(pListSet->m_remain.Left(3) != _T("To "))
    {
		CString strPayId = pListSet->m_ID;
		BOOL b = pListSet->Modify_Transfer(g_strAutoReturnCreditCard);
		//        pListSet->Edit();
		//        pListSet->m_remain = strTo + ";" + pListSet->m_remain;
		//        pListSet->m_bType = bType;    
		//        pListSet->Update();
		if(!b)
		{
			AfxMessageBox(_T("转出修改失败！"));
			return;			
		}
        
        pListSet->m_strFilter = "";
        pListSet->Requery();
		
		CListSet listData;
		listData.StartEdit();
		listData.AddNew();
		

        listData.m_remain.Format("From %s",strPayId) ; 
        listData.m_day = day; 
        listData.m_bType = theApp.GetTypeIndex(_T("转存"));    
        listData.m_addorsub = addorsub;   
        listData.m_ID = g_strAutoReturnCreditCard;
		listData.m_strSite = strSite;
		int ret = listData.SubmitNew();
		listData.EndEdit();
        
        CString str;
        str.Format("%s ->%s \n%s\n%s",strPayId,listData.m_ID,listData.m_addorsub,listData.m_remain);
		//b = pListSet->New_Item(&listData);
		
		if(ret == 0)
		{
			str += "\nOK";
		}
		else
		{
			str += "\nFailed";
		}
		AfxMessageBox(str);
    }
    else if(pListSet->m_remain.Left(strTo.GetLength()) != strTo)
    {
        AfxMessageBox(_T("请确认是不是一条记录转到了两个账号里！"));
    }
	else
	{
        AfxMessageBox(_T("已经转到此卡里了，请确认！"));
	}
}

void CReportDemoView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
{
    if(bActivate)
    {
        if (m_pParent)
        {
            if (m_pParent->m_strID != _T(""))
            {

                theApp.ShowAccountInfo(m_pParent->m_strID);
                TRACE(_T("OnActivateView %s,%d,%s,%s\n"), m_pParent->m_strTitle, bActivate, pActivateView == this ? _T("Active this") : _T(""), pDeactiveView == this ? _T("DeActive this") : _T(""));
            }
            else if (m_pParent->m_ViewType == VIEW_TYPE_MAIN_COUNTS)
            {
                CStringList sl;
                CString total;
                total.Format("Total:%.2f", m_total);
                sl.AddHead(total);
                total.Format("项目数：%d", m_nStaticCount);
                sl.AddHead(total);
                theApp.ShowStaticInfo(sl);
            }
        }
    }
	CBCGPReportView::OnActivateView(bActivate, pActivateView, pDeactiveView);
}

void CReportDemoView::OnUpdateEditCopy(CCmdUI* pCmdUI) 
{
    if(IS_RECORD(m_pParent->m_ViewType))
    {
        CMailReportCtrl* pReportCtrl = (CMailReportCtrl*)GetReportCtrl ();
        CBCGPGridRow* pRow = pReportCtrl->GetCurSel();
        
        pCmdUI->Enable(pRow != NULL && !pRow->IsGroup());
    }
    else
    {
        pCmdUI->Enable(FALSE);
    }
}

void CReportDemoView::OnUpdateEditPaste(CCmdUI* pCmdUI) 
{
    if(m_pParent->m_ViewType == VIEW_TYPE_RECORD_IN_ONE_COUNT)
    {
        pCmdUI->Enable(IsClipboardFormatAvailable(theApp.m_DataFormat)||IsClipboardFormatAvailable(CF_UNICODETEXT));
    }
    else
    {
        pCmdUI->Enable(FALSE);
    }
}

// 
// 
// /*******************************************
//     Function Name : 
//     author        : Qiu Guohua
//     Date          : 2009-5-30 22:15:55
//     Description   : 
//     Return type  : 
//     Argument      : 
// ********************************************/
// void CReportDemoView::OnEditOnline() 
// {
//     CMailReportCtrl* pReportCtrl = (CMailReportCtrl*)GetReportCtrl ();
//     pReportCtrl->ToggleEditInPlace();
// }

void CReportDemoView::OnDeletebook() 
{
    CBCGPGridRow* pSel = GetReportCtrl ()->GetCurSel ();

    if(pSel != NULL)
    {
        BOOL b = theApp.DeleteBook((LPCTSTR) (_bstr_t)pSel->GetItem(VALUE_MAINCOUNT_TYPE_MAINCOUNT)->GetValue());
    }
}

void CReportDemoView::OnUpdateDeletebook(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CReportDemoView::OnRectifyinfo() 
{
    CBCGPGridRow* pSel = GetReportCtrl ()->GetCurSel ();
    
    if(pSel != NULL)
    {
        BOOL b = theApp.RectifyBookInfo((LPCTSTR) (_bstr_t)pSel->GetItem(VALUE_MAINCOUNT_TYPE_MAINCOUNT)->GetValue());
    }
}

void CReportDemoView::OnUpdateRectifyinfo(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CReportDemoView::OnInfo() 
{
    CBCGPGridRow* pSel = GetReportCtrl ()->GetCurSel ();
    
    if(pSel != NULL)
    {
        theApp.ShowAccountInfo((LPCTSTR) (_bstr_t)pSel->GetItem(VALUE_MAINCOUNT_TYPE_MAINCOUNT)->GetValue());
    }

}

void CReportDemoView::OnUpdateInfo(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CReportDemoView::OnBankbookFree() 
{
    CBCGPGridRow* pSel = GetReportCtrl ()->GetCurSel ();
    
    if(pSel != NULL)
    {
        BOOL b = theApp.FreeBook((LPCTSTR) (_bstr_t)pSel->GetItem(VALUE_MAINCOUNT_TYPE_MAINCOUNT)->GetValue());
    }
}
#if 0//no need to set a pay card.
void CReportDemoView::OnSetAsAutoReturnCard() 
{

    if(m_pParent->m_ViewType == VIEW_TYPE_RECORD_IN_ONE_COUNT)
    {
         theApp.SetAutoPayCard(m_pParent->m_strID);
    }
    else if(m_pParent->m_ViewType == VIEW_TYPE_MAIN_COUNTS)
    {
		CBCGPGridRow* pSel = GetReportCtrl ()->GetCurSel ();
        theApp.SetAutoPayCard((LPCTSTR) (_bstr_t)pSel->GetItem(VALUE_MAINCOUNT_TYPE_MAINCOUNT)->GetValue());
	}

	MessageBox("设置为还贷款卡",g_strAutoReturnCard);

}
#endif

void CReportDemoView::OnSetAsAutoreturnCredit() 
{

    if(m_pParent->m_ViewType == VIEW_TYPE_RECORD_IN_ONE_COUNT)
    {
        theApp.SetAutoReturnCreditCard(m_pParent->m_strID);
    }
    else if(m_pParent->m_ViewType == VIEW_TYPE_MAIN_COUNTS)
    {
		CBCGPGridRow* pSel = GetReportCtrl ()->GetCurSel ();
        theApp.SetAutoReturnCreditCard((LPCTSTR) (_bstr_t)pSel->GetItem(VALUE_MAINCOUNT_TYPE_MAINCOUNT)->GetValue());
	}
//    ::MessageBox(this->m_hWnd,g_strAutoReturnCreditCard,"CReportDemoView",IDOK);
}

void CReportDemoView::OnTransferDingqi() 
{
    CBCGPGridRow* pSel = GetReportCtrl ()->GetCurSel ();
    if(m_pParent->m_ViewType == VIEW_TYPE_RECORD_IN_ONE_COUNT)
    {

        CMailReportCtrl* pReportCtrl = (CMailReportCtrl*)GetReportCtrl();
        CBCGPGridRow* pRow = pReportCtrl->GetCurSel();
        if (pSel != NULL)
        {
            DWORD dwRecordID = pRow->GetData();
            theApp.ManageDingqi(dwRecordID);
            //CListSet* pSet = theApp.GetListSet();
            //if (pSet->MoveToID(dwRecordID, m_pParent->m_strFilter))
            //{

            //}
        }

    	//theApp.TransferDingqi(m_pParent->m_strID);
    }
    else if(m_pParent->m_ViewType == VIEW_TYPE_MAIN_COUNTS)
    {
        if(pSel != NULL)
        {
    	    theApp.TransferDingqi((LPCTSTR) (_bstr_t)pSel->GetItem(VALUE_MAINCOUNT_TYPE_MAINCOUNT)->GetValue());
        }
    }
}

void CReportDemoView::OnFindBook() 
{
	// TODO: Add your command handler code here
	
}

void CReportDemoView::OnModifySubcount() 
{
    CBCGPGridRow* pSel = GetReportCtrl ()->GetCurSel ();
    
    if(pSel != NULL)
    {
        if(IS_RECORD(m_pParent->m_ViewType ) && pSel->IsGroup())
        {
            CString strSubCount = ((CGroupRow*)pSel)->GetText();
            if(_T("活期") != strSubCount)
            {
                ((CGroupRow*)pSel)->m_bNeedUpdateTip = TRUE;
				CBCGPGridRow* pSubRow = pSel->GetSubItem(0);
				CBCGPGridItem* pItemDate = pSubRow->GetItem(1);
				COleDateTime date = (DATE) pItemDate->GetValue ();
				
				
				CBCGPGridItem* pItemValue = pSubRow->GetItem(2);
				TRACE("%s,%f",date.Format("%Y-%m-%d"),(float)pItemValue->GetValue());
				float beginValue = (float)pItemValue->GetValue();
				theApp.ModifySubCount(
                    m_pParent->m_strID,
                    strSubCount,&date,&beginValue);
				
				
            }
        }
        else if(m_pParent->m_ViewType == VIEW_TYPE_SUB_COUNTS)
        {
            theApp.ModifySubCount(
                (LPCTSTR) (_bstr_t)pSel->GetItem(COLUMN_SUBCOUNT_MAINCOUNT)->GetValue(),
                (LPCTSTR) (_bstr_t)pSel->GetItem(COLUMN_SUBCOUNT_SUBCOUNT)->GetValue());
        }
        else if (m_pParent->m_ViewType == VIEW_TYPE_SUB_COUNTS_DETAIL)
        {
            if (pSel != NULL)
            {
                DWORD dwRecordID = pSel->GetData();
                theApp.ModifyDingqi(dwRecordID);
            }
        }
    }
}

void CReportDemoView::OnRenewSubcount() 
{
    CBCGPGridRow* pSel = GetReportCtrl ()->GetCurSel ();
    
    if(pSel != NULL)
    {
        if(m_pParent->m_ViewType == VIEW_TYPE_SUB_COUNTS)
        {
            
            BOOL b = theApp.RenewSubCount((LPCTSTR) (_bstr_t)pSel->GetItem(COLUMN_SUBCOUNT_MAINCOUNT)->GetValue(),(LPCTSTR) (_bstr_t)pSel->GetItem(COLUMN_SUBCOUNT_SUBCOUNT)->GetValue());
            if(b)
            {
                theApp.ForceUpdateViews();
            }
        }
        else if (IS_RECORD(m_pParent->m_ViewType)&&pSel->IsGroup())
        {
            CString strSubCount = ((CGroupRow*)pSel)->GetText();
            BOOL b = theApp.RenewSubCount(m_pParent->m_strID,strSubCount);
            if(b)
            {
                theApp.ForceUpdateViews();
            }
            
        }
    }
}


/*******************************************
    Function Name : 
    author        : Qiu Guohua
    Date          : 2010-4-8 17:01:53
    Description   : 
    Return type   : 
    Argument      : 
********************************************/
void CReportDemoView::OnOpenSubcountById() 
{
	if(m_pParent->m_ViewType == VIEW_TYPE_MAIN_COUNTS)
    {
        CBCGPReportCtrl* pReportCtrl = GetReportCtrl();
        CBCGPGridRow* pRow = pReportCtrl->GetCurSel();
        if(pRow)
        {
            theApp.OpenSubCountbyId((LPCTSTR) (_bstr_t)pRow->GetItem(VALUE_MAINCOUNT_TYPE_MAINCOUNT)->GetValue());
        }
    }
}

void CReportDemoView::OnUpdateOpenSubcountById(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_pParent->m_ViewType == VIEW_TYPE_MAIN_COUNTS);
}

void CReportDemoView::OnDropFiles(HDROP hDropInfo)
{
    // 被拖拽的文件的文件名
    char szFileName[MAX_PATH + 1];
    // 得到被拖拽的文件名
    DragQueryFile(hDropInfo, 0, szFileName, MAX_PATH);
	if(m_pParent->m_strID == _T(""))
	{
		AfxMessageBox("只能加入到一个存折中,请先选择一个存折!");
		return;
	}
	//	CImportSheet sheet("C:\\Documents and Settings\\guohua.qiu\\Desktop\\Book1.csv",&pDoc->m_listset);
    CImportSheet sheet(szFileName,theApp.GetListSet(),m_pParent->m_strID);
    sheet.DoModal();
    theApp.ForceUpdateViews();
}


/*******************************************
    Function Name : 
    author        : Qiu Guohua
    Date          : 2010-12-20 20:10:44
    Description   : 
    Return type   : 
    Argument      : 
********************************************/
void CReportDemoView::OnSubcountClose() 
{
    CBCGPGridRow* pSel = GetReportCtrl ()->GetCurSel ();
    
    if(pSel != NULL)
    {
        if(m_pParent->m_ViewType == VIEW_TYPE_SUB_COUNTS)
        {
            
            BOOL b = theApp.CloseSubCount((LPCTSTR) (_bstr_t)pSel->GetItem(COLUMN_SUBCOUNT_MAINCOUNT)->GetValue(),
                (LPCTSTR) (_bstr_t)pSel->GetItem(COLUMN_SUBCOUNT_SUBCOUNT)->GetValue());
            if (b)
            {
                theApp.ForceUpdateViews();
            }
        }
        else if (m_pParent->m_ViewType == VIEW_TYPE_SUB_COUNTS_DETAIL)
        {
            DWORD dwRecordID = pSel->GetData();
            BOOL b = theApp.CloseDingqiRecord(dwRecordID);
            if(b)
            {
                theApp.ForceUpdateViews();
            }
        }
        else if (IS_RECORD(m_pParent->m_ViewType)&&pSel->IsGroup())
        {
            CString strSubCount = ((CGroupRow*)pSel)->GetText();
            BOOL b = theApp.CloseSubCount(m_pParent->m_strID,strSubCount);
            if(b)
            {
                theApp.ForceUpdateViews();
            }
            
        }
    }
}

void CReportDemoView::OnUpdateSubcountClose(CCmdUI* pCmdUI)
{
    CBCGPGridRow* pSel = GetReportCtrl ()->GetCurSel ();
    BOOL bEnable = FALSE;
    
    if(pSel != NULL)
    {
        if(m_pParent->m_ViewType == VIEW_TYPE_SUB_COUNTS)
        {
            bEnable = theApp.IsSubcountActive((LPCTSTR) (_bstr_t)pSel->GetItem(COLUMN_SUBCOUNT_MAINCOUNT)->GetValue(),
                (LPCTSTR) (_bstr_t)pSel->GetItem(COLUMN_SUBCOUNT_SUBCOUNT)->GetValue());
        }
        else if (m_pParent->m_ViewType == VIEW_TYPE_SUB_COUNTS_DETAIL)
        {
            bEnable = TRUE;
        }
        else if (IS_RECORD(m_pParent->m_ViewType)&&pSel->IsGroup())
        {
            CString strSubCount = ((CGroupRow*)pSel)->GetText();
            bEnable = theApp.IsSubcountActive(m_pParent->m_strID,strSubCount);
        }
    }
    pCmdUI->Enable(bEnable);
}

void CReportDemoView::OnExpandActiveItem() 
{
	CMailReportCtrl* pReportCtrl = (CMailReportCtrl*)GetReportCtrl();
    
    pReportCtrl->ExpandAllActiveGroup();
}

void CReportDemoView::OnExpandAllItem() 
{
    CMailReportCtrl* pReportCtrl = (CMailReportCtrl*)GetReportCtrl();
    
    pReportCtrl->ExpandAllGroup();
	// TODO: Add your command handler code here
	
}

void CReportDemoView::OnCollapseAllItem() 
{
    CMailReportCtrl* pReportCtrl = (CMailReportCtrl*)GetReportCtrl();
    
    pReportCtrl->CollapseAllGroup();
	// TODO: Add your command handler code here
	
}

void CReportDemoView::OnCollapseInactiveInactive() 
{
    CMailReportCtrl* pReportCtrl = (CMailReportCtrl*)GetReportCtrl();
    
    pReportCtrl->CollapseAllInactiveGroup();
}
void CReportDemoView::BrowseToBackYear(int backYear) 
{
    COleDateTime now = COleDateTime::GetCurrentTime();
    int year = now.GetYear();
    year -= backYear;

    CMailReportCtrl* pReportCtrl = (CMailReportCtrl*)GetReportCtrl();
    CBCGPGridRow* targetRow = NULL;
    int nCount = pReportCtrl->GetRowCount();

    int last_diff = 1000;

    for(int index = 0;index < nCount;index++)
    {
        CBCGPGridRow* pRow = pReportCtrl->GetRow(index);
        if(pRow->IsGroup())
        {
            continue;
        }
        CBCGPGridItem* pItem = pRow->GetItem(COLUMN_DATE__);
        COleDateTime date = (DATE)pItem->GetValue();


        int thisyear = date.GetYear();
        int this_diff = thisyear > year? thisyear-year:year-thisyear;
        if(this_diff > last_diff )
        {
            break;
        }
        targetRow = pRow;
        TRACE("Browse year is %d\n", thisyear);
        last_diff = this_diff;
    }
    pReportCtrl->EnsureVisible(targetRow);
}

void CReportDemoView::OnBrowseYear(UINT nID) 
{
    BrowseToBackYear(nID - ID_THIS_YEAR);
}



void CReportDemoView::OnCopyRecordsTo(UINT nID)
{
	int nIndex = nID - IDM_COPY_RECORDS_TO;
	CStringList list;

	POSITION pos= g_CountIdList.GetHeadPosition();
	CString strId;
	while(nIndex >= 0 && pos)
	{
       strId = g_CountIdList.GetNext(pos);
	   nIndex--;
	}
	if(strId.GetLength()>0)
	{
		CopyRecordsTo(strId);
	}
	g_CountIdList.RemoveAll();


}

void CReportDemoView::OnUpdateAddReturnRecord(CCmdUI* pCmdUI) 
{
#if 0//no need to set a pay card.
	//必须是储蓄卡

    BOOL b = m_pParent->m_ViewType == VIEW_TYPE_RECORD_IN_ONE_COUNT;
    b= b&&(m_pParent->m_strID == g_strAutoReturnCard);
    pCmdUI->Enable(b);
#else
    pCmdUI->Enable(TRUE);
#endif
}

void CReportDemoView::OnUpdateTransferDingqi(CCmdUI* pCmdUI) 
{
    //必须是储蓄卡
    BOOL b = m_pParent->m_ViewType == VIEW_TYPE_RECORD_IN_ONE_COUNT;
    b &= (theApp.GetBookType(m_pParent->m_strID) != 3);//not credit card.
    pCmdUI->Enable(b);
}

void CReportDemoView::OnUpdateCalCredit(CCmdUI* pCmdUI) 
{
    //必须是信用卡
    BOOL b = m_pParent->m_ViewType == VIEW_TYPE_RECORD_IN_ONE_COUNT;
    b &= (theApp.GetBookType(m_pParent->m_strID) == 3);
    pCmdUI->Enable(b);
}

void CReportDemoView::FillItems()
{
    if(IS_REPORT(m_pParent->m_ViewType))
    {
        DisplayReport();
    }
	else if(IS_RECORD(m_pParent->m_ViewType))
	{
		DisplayRecord();
	}
	else if(IS_TODO(m_pParent->m_ViewType))
	{
		DisplayTodo();
	}
	else if(IS_SIMPLE_SUBCOUNT(m_pParent->m_ViewType))
	{
		DisplaySimpleSubCount();
	}
	else if(IS_DETAIL_SUBCOUNT(m_pParent->m_ViewType))
	{
		DisplayDetailSubCount();
	}
	else
	{
        DisplayCount();
	}
}


#if 0
void CReportDemoView::CheckBill(const COleDateTime &timeBegin, const COleDateTime &timeEnd,const COleDateTime& timePay)
{
	CString strFile(_T("C:\\Check.htm"));
	CGridHtmlExporter exporter;
	exporter.SetExportFile(strFile);
    CListSet* pListSet = theApp.GetListSet();   
    pListSet->m_strFilter = m_pParent->m_strFilter;
    pListSet->Requery();
    if(!pListSet->IsBOF())
    {
        pListSet->MoveFirst();
    }
	float fSum = 0.0;
	float fPaySum = 0.0;
	float fThisSum,fThisPaySum;
	CString str,str1;
	UINT uColor = 0x6eb0ff;
	COleDateTime timePaylocal = timePay;
	timePaylocal.SetDateTime(timePay.GetYear(),timePay.GetMonth(),timePay.GetDay(),23,59,59);
	while(!pListSet->IsEOF())
	{
		if(pListSet->m_day >= timeBegin && pListSet->m_day <= timeEnd)
		{
			fThisSum = pListSet->GetAddorSubValue();
			if(fThisSum<0)
			{
				fSum += fThisSum;
//				exporter.ExportLine(pListSet->GetDate(),pListSet->m_addorsub,pListSet->m_remain,uColor);
			}
		}
		else if(pListSet->m_day > timeEnd && pListSet->m_day <= timePaylocal)
		{
			fThisPaySum = pListSet->GetAddorSubValue();
			if(fThisPaySum>0)
			{
				fPaySum += fThisPaySum;
//				exporter.ExportLine(pListSet->GetDate(),pListSet->m_addorsub,pListSet->m_remain,uColor);
			}

		}

		pListSet->MoveNext();
	}
	str = timePay.Format("%Y-%m-%d");
	str1.Format("%8.2f",-fSum);
	exporter.ExportLine(timeEnd.GetYear(),timeEnd.GetMonth(),fSum,fPaySum);
	exporter.ExportLine(str,str1,"Bankbook自动生成还款额.",0x3591ff);
	exporter.ExportTail();
	exporter.CloseFile();
	ShellExecute( AfxGetMainWnd()->m_hWnd, "open", strFile, NULL, NULL, SW_SHOWNORMAL );
}
#endif
void CReportDemoView::OnCheckBill() 
{
	CString strFile(_T("C:\\test.htm"));
	CGridHtmlExporter exporter;
	exporter.SetExportFile(strFile);

	int nYear = 2005;
	int nMonth = 1;
	COleDateTime date;
	COleDateTime today;
	COleDateTime tmBegin,tmEnd,tmPay;
	float fUse, fPay;
	today = COleDateTime::GetCurrentTime();
    do
    {
		CheckBill(nYear,nMonth,tmBegin,tmEnd,tmPay, fUse,fPay);
		exporter.ExportCheckLine(nYear,nMonth,tmBegin,tmEnd,tmPay, fUse,fPay);

		nMonth++;
		if(nMonth>12)
		{
			nYear++;
			nMonth = 1;
		}

		date.SetDate(nYear,nMonth,1);
	} while(date<today);

	exporter.ExportTail();
	exporter.CloseFile();
	ShellExecute( AfxGetMainWnd()->m_hWnd, "open", strFile, NULL, NULL, SW_SHOWNORMAL );

}

BOOL CReportDemoView::CheckBill(int nYear, int nMonth, COleDateTime &timeBegin, COleDateTime &timeEnd, COleDateTime &timePay,float& fUse,float& fPay)
{
    CCreditPaySet set;
    BOOL b = set.GetPayInfo(m_pParent->m_strID,nYear,nMonth,timeBegin,timeEnd,timePay);
	if(!b)
	{
		return FALSE;
	}


    CListSet* pListSet = theApp.GetListSet();   
    pListSet->m_strFilter = m_pParent->m_strFilter;
    pListSet->Requery();
    if(!pListSet->IsBOF())
    {
        pListSet->MoveFirst();
    }
	float fThisSum,fThisPaySum;
	fUse = 0.0;
	fPay = 0.0;
	COleDateTime timePaylocal = timePay;
	timePaylocal.SetDateTime(timePay.GetYear(),timePay.GetMonth(),timePay.GetDay(),23,59,59);
	while(!pListSet->IsEOF())
	{
		if(pListSet->m_day >= timeBegin && pListSet->m_day <= timeEnd)
		{
			fThisSum = pListSet->GetAddorSubValue();
			if(fThisSum<0)
			{
				fUse += fThisSum;
			}
		}
		else if(pListSet->m_day > timeEnd && pListSet->m_day <= timePaylocal)
		{
			fThisPaySum = pListSet->GetAddorSubValue();
			if(fThisPaySum>0)
			{
				fPay += fThisPaySum;
			}
		}
		pListSet->MoveNext();
	}
	return TRUE;
}


BOOL CReportDemoView::DisplayTodo()
{
    CMailReportCtrl* pReportCtrl = (CMailReportCtrl*)GetReportCtrl();
    pReportCtrl->RemoveAll ();

    CTodoSet* pSet = theApp.GetTodoSet();
    pSet->Requery();
    pSet->MoveFirst();
    while(!pSet->IsEOF())
    {
        CBCGPGridRow* pRow = pReportCtrl->CreateRow (COLUMN_TODO_NUMBER);
        pRow->GetItem (COLUMN_TODO_ID)->SetValue (pSet->m_id, FALSE);
        pRow->GetItem (COLUMN_TODO_BODY)->SetValue ((LPCTSTR)pSet->m_body, FALSE);
        pReportCtrl->AddRow (pRow, FALSE);
        pSet->MoveNext();
    }

    AdjustColumnWidth();
    pReportCtrl->AdjustLayout ();
    return TRUE;
}

BOOL CReportDemoView::DisplayReport()
{
    CMailReportCtrl* pReportCtrl = (CMailReportCtrl*)GetReportCtrl();
	pReportCtrl->RemoveAll ();
	
	CListSet* pListSet = theApp.GetListSet();
	theApp.SetBookFilter(m_pParent->m_strID);
//	int start_y,start_m,start_d;
//	int end_y,end_m,end_d;
	CSmartDate start_date;
	CSmartDate end_date;
	
	if(!pListSet->GetFirstDate(start_date))
	{
		return FALSE;
	}
	
	if(!pListSet->GetLastDate(end_date))
	{
		return FALSE;
	}
	
    COleDateTime timeB, timeE;
    CString str,stre;
	CString strPay;
	float fpay,frepay;

	int month_first,month_last;

	float account_gap = 0.0;

    for(int j=start_date.year;j<=end_date.year;j++)
    {
		month_first = (j==start_date.year)?start_date.month:1;
		month_last = (j==end_date.year)?end_date.month:12;
		for(int i = month_first;i<=month_last;i++)
		{
			if(GetPeriod(m_pParent->m_strID,j,i,timeB,timeE))
			{
				CBCGPGridRow* pRow = pReportCtrl->CreateRow (CLOUMN_REPORT_COLOUMN_COUNT);
				
				str = timeB.Format("%Y-%m-%d");
				pRow->GetItem (COLUMN_REPORT_START_TIME)->SetValue ((LPCTSTR)str, FALSE);
				
				stre = timeE.Format("%Y-%m-%d");
				pRow->GetItem (COLUMN_REPORT_END_TIME)->SetValue ((LPCTSTR)stre, FALSE);
				
				fpay = theApp.GetPay(pListSet,m_pParent->m_strID,timeB,timeE);
				strPay.Format("%8.2f",fpay);
				pRow->GetItem (COLUMN_REPORT_EXPENSE)->SetValue ((LPCTSTR)strPay, FALSE);
				
				frepay = theApp.GetRepay(pListSet,m_pParent->m_strID,timeE);
				strPay.Format("%8.2f",frepay);
				pRow->GetItem (COLUMN_REPORT_REPAY)->SetValue ((LPCTSTR)strPay, FALSE);
				
				float f = fpay+frepay;
				strPay.Format("%8.2f",f);
				pRow->GetItem (COLUMN_REPORT_GAP)->SetValue ((LPCTSTR)strPay, FALSE);

				account_gap += f;
				
				strPay.Format("%8.2f", account_gap);
				pRow->GetItem (CLOUMN_REPORT_ACCOUNT_GAP)->SetValue ((LPCTSTR)strPay, FALSE);
				if(f >0.001)
				{
					pReportCtrl->SetRowBackColor(pRow,RGB(255,200,200));
				}
				else if(f <-0.001)
				{
					pReportCtrl->SetRowBackColor(pRow,RGB(128,128,255));
				}
				else
				{
					pReportCtrl->SetRowBackColor(pRow,RGB(211,255,211));
				}
				
				pReportCtrl->AddRow (pRow, FALSE);
				TRACE("ADD NEW LINE: %s-> %s\n",str,stre);
			}
		}
    }
	
	AdjustColumnWidth();
	pReportCtrl->AdjustLayout ();
	return TRUE;
}
BOOL CReportDemoView::GetPeriod(CString strid,int nYear, int nMonth,COleDateTime& timeBegin,COleDateTime& timeEnd)
{
	COleDateTime timePay;

    CCreditPaySet set;
    BOOL b = set.GetPayInfo(strid,nYear,nMonth,timeBegin,timeEnd,timePay);
    if(b)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}


/*******************************************
    Function Name : 
    author        : Qiu Guohua
    Date          : 2017/8/8 22:27:10
    Description   : 
    Return type   : 
    Argument      : 
********************************************/
void CReportDemoView::CopyRecordsTo(const CString &strCount)
{
	CCopyRecordsDlg dlg;
	dlg.m_mainCount = strCount;
	if(dlg.DoModal() == IDOK)
	{
		CMailReportCtrl* pReportCtrl = (CMailReportCtrl*)GetReportCtrl();
		CDWordArray dbAry;
		pReportCtrl->GetSelectedRows(dbAry);
		if(dbAry.GetSize()>0)
		{
			theApp.CopyRecordsTo(dbAry,strCount,dlg.m_SubCount,dlg.m_bTransfer);
		}
	}
}


/*******************************************
    Function Name : 
    author        : Qiu Guohua
    Date          : 2017/8/8 22:27:10
    Description   : 
    Return type   : 
    Argument      : 
********************************************/
void CReportDemoView::MoveRecordsTo(const CString &strCount)
{
	CCopyRecordsDlg dlg;
	dlg.m_mainCount = strCount;
	if(dlg.DoModal() != IDOK)
	{
		return;
	}
	CMailReportCtrl* pReportCtrl = (CMailReportCtrl*)GetReportCtrl();
	CDWordArray dbAry;
	int count = pReportCtrl->GetSelectedRows(dbAry);
	if(count>0)
	{
		CListSet* pListSet = theApp.GetListSet();
		pListSet->MoveRecordsTo(strCount, dlg.m_SubCount,dbAry, count);
	}
}


void CReportDemoView::OnMoveRecordsTo(UINT nID)
{
	int nIndex = nID - IDM_MOVE_RECORDS_TO;
	CStringList list;

	POSITION pos= g_CountIdList.GetHeadPosition();
	CString strId;
	while(nIndex >= 0 && pos)
	{
		strId = g_CountIdList.GetNext(pos);
		nIndex--;
	}
	if(strId.GetLength()>0)
	{
		MoveRecordsTo(strId);
	}
	g_CountIdList.RemoveAll();
}

void CReportDemoView::ForceUpdate()
{
	OnUpdate(NULL,0,NULL);
}

void CReportDemoView::DisplaySimpleSubCount()
{
	CSubCountInOneCountSet sub_set(m_pParent->m_strFilter,FALSE);

	if(!sub_set.Open())
	{
		AfxMessageBox(_T("sub_set 数据库装载错误(type)!"));
		return ;
	};
	sub_set.Requery();
	sub_set.MoveFirst();
	while(!sub_set.IsEOF())
	{
		AddSimpleSubCount2List(&sub_set);
		TRACE("subid:%s %s\n", sub_set.m_Sub_Count_ID,sub_set.m_Remains);
		sub_set.MoveNext();
	}
	sub_set.Close();
}

void CReportDemoView::DisplayDetailSubCount()
{
#if 0
    CString sql = "DELETE FROM FixedDeposit WHERE PERIOD IS NULL OR PERIOD = \'\';";

    try {
        CDatabase db;
        db.OpenEx(CDbConfigure::GetDataSource());
        db.ExecuteSQL(sql);
        db.Close();
    }
    catch (CDBException* e) {
        CString errMsg = _T("数据库错误: ") + e->m_strError;
        AfxMessageBox(errMsg);
        e->Delete();
    }

#endif

	CDetailSubCountSet sub_set(m_pParent->m_strFilter);

	if(!sub_set.Open())
	{
		AfxMessageBox(_T("DetailSubCountSet 数据库装载错误(type)!"));
		return ;
	};
    sub_set.Requery();
    if (sub_set.GetRecordCount() > 0)
    {
        sub_set.MoveFirst();
        while (!sub_set.IsEOF())
        {
            AddDetailSubCount2List(&sub_set);

            sub_set.MoveNext();
        }
    }
	sub_set.Close();
}
void CReportDemoView::AddSimpleSubCount2List(CSubCountInOneCountSet* pSet)
{
	CBCGPReportCtrl* pReportCtrl = GetReportCtrl ();

	int count=pReportCtrl->GetColumnCount ();
	CBCGPGridRow* pRow = pReportCtrl->CreateRow (count);
	pRow->GetItem (COLUMN_SIMPLE_SUBCOUNT_NAME)->SetValue ((LPCTSTR)pSet->m_Sub_Count_ID, FALSE);
	pRow->GetItem (COLUMN_SIMPLE_SUBCOUNT_REMAIN)->SetValue ((LPCTSTR)pSet->m_Remains, FALSE);
	pReportCtrl->AddRow (pRow, FALSE);

}

void CReportDemoView::AddDetailSubCount2List(CDetailSubCountSet* pSet)
{
    CBCGPReportCtrl* pReportCtrl = GetReportCtrl();

    int count = pReportCtrl->GetColumnCount();
    CBCGPGridRow* pRow = pReportCtrl->CreateRow(count);

    pRow->GetItem(COLUMN_DETAIL_SUBCOUNT_BANK         )->SetValue((LPCTSTR)pSet->m_strBank, FALSE);
    pRow->GetItem(COLUMN_DETAIL_SUBCOUNT_OWNER        )->SetValue((LPCTSTR)pSet->m_strOwner, FALSE);
    pRow->GetItem(COLUMN_DETAIL_SUBCOUNT_ID           )->SetValue((LPCTSTR)pSet->m_strBookId, FALSE);
    pRow->GetItem(COLUMN_DETAIL_SUBCOUNT_VALUE        )->SetValue(pSet->m_fValue, FALSE);
    pRow->GetItem(COLUMN_DETAIL_SUBCOUNT_START_DATE   )->SetValue(_variant_t((DATE)pSet->m_dateStart, VT_DATE), FALSE);

    pRow->GetItem(COLUMN_DETAIL_SUBCOUNT_END_DATE     )->SetValue(_variant_t((DATE)pSet->m_dateEnd, VT_DATE), FALSE);

    pRow->GetItem(COLUMN_DETAIL_SUBCOUNT_RATE         )->SetValue(pSet->m_fRate, FALSE);
    pRow->GetItem(COLUMN_DETAIL_SUBCOUNT_TIMESPAN     )->SetValue((LPCTSTR)pSet->m_strTimeSpan, FALSE);
    pRow->GetItem(COLUMN_DETAIL_SUBCOUNT_COMMENT      )->SetValue((LPCTSTR)pSet->m_strComment, FALSE);
    if (pSet->m_bClosed)
    {
        CMailReportCtrl::SetRowBackColor(pRow, RGB(209, 200, 192));

        pRow->GetItem(COLUMN_DETAIL_SUBCOUNT_STATUS)->SetValue(_T("已结"), FALSE);
    }
    else
    {
        CMailReportCtrl::SetRowBackColor(pRow, RGB(245, 255, 245));
        pRow->GetItem(COLUMN_DETAIL_SUBCOUNT_STATUS)->SetValue(_T("未结"), FALSE);
    }

    pReportCtrl->AddRow(pRow, FALSE);

    pRow->SetData((DWORD)pSet->m_nId);
}
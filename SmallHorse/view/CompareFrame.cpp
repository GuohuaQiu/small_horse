// ChildFrm.cpp : implementation of the CCompareFrame class
//

#include "stdafx.h"
#include "..\SmallHorse.h"
#include "CompareFrame.h"
#include "CompareListCtrl.h"
#include "CompareDetailCtrl.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CCompareFrame

IMPLEMENT_DYNCREATE(CCompareFrame, CBCGPMDIChildWnd)

BEGIN_MESSAGE_MAP(CCompareFrame, CBCGPMDIChildWnd)
	//{{AFX_MSG_MAP(CCompareFrame)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	ON_UPDATE_COMMAND_UI_RANGE(AFX_ID_VIEW_MINIMUM, AFX_ID_VIEW_MAXIMUM, OnUpdateViewStyles)
	ON_COMMAND_RANGE(AFX_ID_VIEW_MINIMUM, AFX_ID_VIEW_MAXIMUM, OnViewStyle)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCompareFrame construction/destruction




CCompareFrame::CCompareFrame()
{
	// TODO: add member initialization code here
	
}

CCompareFrame::~CCompareFrame()
{
}

BOOL CCompareFrame::OnCreateClient( LPCREATESTRUCT /*lpcs*/,
	CCreateContext* pContext)
{
	// create splitter window
	if (!m_wndSplitter.CreateStatic(this, 2, 1))
		return FALSE;

	if (!m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CCompareListCtrl), CSize(100, 100), pContext) ||
		!m_wndSplitter.CreateView(1, 0, RUNTIME_CLASS(CCompareDetailCtrl), CSize(100, 100), pContext))
	{
		m_wndSplitter.DestroyWindow();
		return FALSE;
	}
    m_pListCtrl = GetTopPane();
    m_pDetailCtrl = GetBottomPane();
    m_pListCtrl->m_pDetailCtrl = m_pDetailCtrl;

    m_pListCtrl->InitCompareCtrl(Callback_OnItemDbClk,&m_listCmp);
    m_pDetailCtrl->Setup();
    LoadData();
    m_pListCtrl->AdjustLayout();

    int n = m_pListCtrl->GetRowCount();
    TRACE("\nleft ctrl has %d items.\n",n);

	return TRUE;
}

BOOL CCompareFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	if( !CBCGPMDIChildWnd::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CCompareFrame diagnostics

#ifdef _DEBUG
void CCompareFrame::AssertValid() const
{
	CBCGPMDIChildWnd::AssertValid();
}

void CCompareFrame::Dump(CDumpContext& dc) const
{
	CBCGPMDIChildWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCompareFrame message handlers

CCompareListCtrl* CCompareFrame::GetTopPane()
{
	CWnd* pWnd = m_wndSplitter.GetPane(0, 0);
	CCompareListCtrl* pView = DYNAMIC_DOWNCAST(CCompareListCtrl, pWnd);
	return pView;
}


CCompareDetailCtrl* CCompareFrame::GetBottomPane()
{
	CWnd* pWnd = m_wndSplitter.GetPane(1, 0);
	CCompareDetailCtrl* pView = DYNAMIC_DOWNCAST(CCompareDetailCtrl, pWnd);
	return pView;
}


#if 0
void CCompareFrame::InitListCtrl(CCompareListCtrl* pCtrl)
{
    pCtrl->InsertColumn (COLUMN_ID____, _T("序号"), 15);
    pCtrl->InsertColumn (COLUMN_DATE__, _T("日期"), 30);
    pCtrl->InsertColumn (COLUMN_CHANGE, _T("收支"), 30);
    pCtrl->InsertColumn (COLUMN_REASON, _T("事由"), 120);
    pCtrl->InsertColumn (COLUMN_TYPE__, _T("类型"), 20);
    pCtrl->InsertColumn (COLUMN_SITE__, _T("地点"), 30);
    pCtrl->InsertColumn (COLUMN_SUBCOUNT, _T("子账号"), 1);

    pCtrl->InsertColumn(COLUMN_BASE_NUMBER,"  ",20);

    pCtrl->InsertColumn (COLUMN_ID____ + COLUMN_RIGHT_BASE, _T("序号"), 15);
    pCtrl->InsertColumn (COLUMN_DATE__+ COLUMN_RIGHT_BASE, _T("日期"), 30);
    pCtrl->InsertColumn (COLUMN_CHANGE+ COLUMN_RIGHT_BASE, _T("收支"), 30);
    pCtrl->InsertColumn (COLUMN_REASON+ COLUMN_RIGHT_BASE, _T("事由"), 120);
    pCtrl->InsertColumn (COLUMN_TYPE__+ COLUMN_RIGHT_BASE, _T("类型"), 20);
    pCtrl->InsertColumn (COLUMN_SITE__+ COLUMN_RIGHT_BASE, _T("地点"), 30);
    pCtrl->InsertColumn (COLUMN_SUBCOUNT+ COLUMN_RIGHT_BASE, _T("子账号"), 1);


    pCtrl->EnableColumnAutoSize (TRUE);
    pCtrl->SetDbClkCBFunc(Callback_OnItemDbClk);
    //	pReportCtrl->SetWholeRowSel (TRUE);
}
#endif

void CCompareFrame::OnUpdateViewStyles(CCmdUI* pCmdUI)
{
	// TODO: customize or extend this code to handle choices on the
	// View menu.
#if 0
	CTestonly2View* pView = GetRightPane(); 

	// if the right-hand pane hasn't been created or isn't a view,
	// disable commands in our range

	if (pView == NULL)
		pCmdUI->Enable(FALSE);
	else
	{
		DWORD dwStyle = pView->GetStyle() & LVS_TYPEMASK;

		// if the command is ID_VIEW_LINEUP, only enable command
		// when we're in LVS_ICON or LVS_SMALLICON mode

		if (pCmdUI->m_nID == ID_VIEW_LINEUP)
		{
			if (dwStyle == LVS_ICON || dwStyle == LVS_SMALLICON)
				pCmdUI->Enable();
			else
				pCmdUI->Enable(FALSE);
		}
		else
		{
			// otherwise, use dots to reflect the style of the view
			pCmdUI->Enable();
			BOOL bChecked = FALSE;

			switch (pCmdUI->m_nID)
			{
			case ID_VIEW_DETAILS:
				bChecked = (dwStyle == LVS_REPORT);
				break;

			case ID_VIEW_SMALLICON:
				bChecked = (dwStyle == LVS_SMALLICON);
				break;

			case ID_VIEW_LARGEICON:
				bChecked = (dwStyle == LVS_ICON);
				break;

			case ID_VIEW_LIST:
				bChecked = (dwStyle == LVS_LIST);
				break;

			default:
				bChecked = FALSE;
				break;
			}

			pCmdUI->SetRadio(bChecked ? 1 : 0);
		}
	}
#endif
}


void CCompareFrame::OnViewStyle(UINT nCommandID)
{
	// TODO: customize or extend this code to handle choices on the
	// View menu.
#if 0
	CTestonly2View* pView = GetRightPane();

	// if the right-hand pane has been created and is a CTestonly2View,
	// process the menu commands...
	if (pView != NULL)
	{
		DWORD dwStyle = -1;

		switch (nCommandID)
		{
		case ID_VIEW_LINEUP:
			{
				// ask the list control to snap to grid
				CListCtrl& refListCtrl = pView->GetListCtrl();
				refListCtrl.Arrange(LVA_SNAPTOGRID);
			}
			break;

		// other commands change the style on the list control
		case ID_VIEW_DETAILS:
			dwStyle = LVS_REPORT;
			break;

		case ID_VIEW_SMALLICON:
			dwStyle = LVS_SMALLICON;
			break;

		case ID_VIEW_LARGEICON:
			dwStyle = LVS_ICON;
			break;

		case ID_VIEW_LIST:
			dwStyle = LVS_LIST;
			break;
		}

		// change the style; window will repaint automatically
		if (dwStyle != -1)
			pView->ModifyStyle(LVS_TYPEMASK, dwStyle);
	}
#endif
}

void CCompareFrame::LoadData()
{
    m_listCmp.Load2Set();
    
    TRACE("\nLOAD COMPLETE.");
//    cmp.OutputGeneralInformation();
    m_listCmp.ClearAllSameRecords();
    TRACE("\nCLEAR SAME COMPLETE.");
//    cmp.OutputGeneralInformation();
    m_listCmp.FindAlikeRecords();
    TRACE("\nFIND ALIKE COMPLETE.");
//    cmp.OutputGeneralInformation();
//    cmp.Output();

    m_listCmp.m_lstJoin.HandleAllItem(AddAlike,(DWORD)(void *)this);
    
}


void CCompareFrame::AddAlike(Alike2 *palike)
{
	m_pListCtrl->AddAlike(palike);
#if 0
    CBCGPGridRow* pRow = m_pListCtrl->CreateRow (COLUMN_COUNT);
    if(pRow!=NULL)
    {

        if(palike->m_pRecordA)
        {
            pRow->GetItem (COLUMN_ID____)->SetValue ((LONG)palike->m_pRecordA->m_arraynumber, FALSE);
            pRow->GetItem (COLUMN_SUBCOUNT)->SetValue ((LPCTSTR)palike->m_pRecordA->m_strSubCount, FALSE);
            pRow->GetItem (COLUMN_DATE__)->SetValue (_variant_t((DATE)palike->m_pRecordA->m_day,VT_DATE), FALSE);
            pRow->GetItem (COLUMN_CHANGE)->SetValue (atof((LPSTR)(LPCTSTR)palike->m_pRecordA->m_addorsub), FALSE);
            
            pRow->GetItem (COLUMN_REASON)->SetValue ((LPCTSTR)palike->m_pRecordA->m_remain, FALSE);
            //	pRow->GetItem (COLUMN_REASON)->AllowEdit();
            pRow->GetItem (COLUMN_TYPE__)->SetValue ((LPCTSTR)theApp.m_cType[palike->m_pRecordA->m_bType], FALSE);
            pRow->GetItem (COLUMN_SITE__)->SetValue ((LPCTSTR)palike->m_pRecordA->m_strSite, FALSE);
			for(int i = COLUMN_ID____;i<COLUMN_BASE_NUMBER;i++)
			{
				if(palike->IsNewA())
				{
					pRow->GetItem(i)->SetTextColor(RGB(0,255,0),FALSE);
				}
				else
				{
					pRow->GetItem(i)->SetTextColor(RGB(77,34,14),FALSE);
				}
			}
            
        }
        if(palike->m_pRecordB)
        {
            pRow->GetItem (COLUMN_DATE__ + COLUMN_RIGHT_BASE)->SetValue (_variant_t((DATE)palike->m_pRecordB->m_day,VT_DATE), FALSE);
            pRow->GetItem (COLUMN_CHANGE + COLUMN_RIGHT_BASE)->SetValue (atof((LPSTR)(LPCTSTR)palike->m_pRecordB->m_addorsub), FALSE);
            pRow->GetItem (COLUMN_ID____ + COLUMN_RIGHT_BASE)->SetValue ((LONG)palike->m_pRecordB->m_arraynumber, FALSE);
            pRow->GetItem (COLUMN_REASON + COLUMN_RIGHT_BASE)->SetValue ((LPCTSTR)palike->m_pRecordB->m_remain, FALSE);
            //	pRow->GetItem (COLUMN_REASON)->AllowEdit();
            pRow->GetItem (COLUMN_TYPE__ + COLUMN_RIGHT_BASE)->SetValue ((LPCTSTR)theApp.m_cType[palike->m_pRecordB->m_bType], FALSE);
            pRow->GetItem (COLUMN_SITE__ + COLUMN_RIGHT_BASE)->SetValue ((LPCTSTR)palike->m_pRecordB->m_strSite, FALSE);
            pRow->GetItem (COLUMN_SUBCOUNT + COLUMN_RIGHT_BASE)->SetValue ((LPCTSTR)palike->m_pRecordB->m_strSubCount, FALSE);
			for(int i = COLUMN_ID____;i<COLUMN_BASE_NUMBER;i++)
			{
				if(palike->IsNewB())
				{
					pRow->GetItem(i+COLUMN_RIGHT_BASE)->SetTextColor(RGB(0,255,0),FALSE);
				}
				else
				{
					pRow->GetItem(i+COLUMN_RIGHT_BASE)->SetTextColor(RGB(25,34,14),FALSE);
				}
			}
        }

        
        if(!(palike->m_dwSameFields & FIELD_COMMENT))
        {
            pRow->GetItem (COLUMN_REASON)->SetTextColor(RGB(255,0,0),FALSE);
            pRow->GetItem (COLUMN_REASON+ COLUMN_RIGHT_BASE)->SetTextColor(RGB(255,0,0),FALSE);
        }
        if(!(palike->m_dwSameFields & FIELD_TYPE))
        {
            pRow->GetItem (COLUMN_TYPE__)->SetTextColor(RGB(255,0,0),FALSE);
            pRow->GetItem (COLUMN_TYPE__+ COLUMN_RIGHT_BASE)->SetTextColor(RGB(255,0,0),FALSE);
        }
        if(!(palike->m_dwSameFields & FIELD_SITE))
        {
            pRow->GetItem (COLUMN_SITE__)->SetTextColor(RGB(255,0,0),FALSE);
            pRow->GetItem (COLUMN_SITE__+ COLUMN_RIGHT_BASE)->SetTextColor(RGB(255,0,0),FALSE);
        }
        pRow->SetData( (DWORD)palike);
    }
    m_pListCtrl->AddRow(pRow,FALSE);
#endif
}


void CCompareFrame::AddAlike(DWORD pThis, void *pRecord)
{
    ((CCompareFrame *)pThis)->AddAlike((Alike2*)pRecord);

}

int CCompareFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CBCGPMDIChildWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	
	return 0;
}


/*******************************************
    Function Name :	 
    Create by     :	  Qiu Simon
    Input         :   
    Output        :   
    Description   :   
    Date          :   1/14/2011 10:22:56 AM
********************************************/
void CCompareFrame::Callback_OnItemDbClk(LPVOID pThis,CBCGPGridRow *pRow)
{
    CMailReportCtrl* pCtrl = (CMailReportCtrl*)pThis;

    CCompareDetailCtrl* pDetailCtrl = pCtrl->m_pDetailCtrl;
    pDetailCtrl->ShowDetail(pRow);
}




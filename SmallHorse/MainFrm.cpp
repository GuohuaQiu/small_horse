// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "SmallHorse.h"

#include "MainFrm.h"
#include "BankbookTree.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CBCGPMDIFrameWnd)

const int  iMaxUserToolbars		= 10;
const UINT uiFirstUserToolBarId	= AFX_IDW_CONTROLBAR_FIRST + 40;
const UINT uiLastUserToolBarId	= uiFirstUserToolBarId + iMaxUserToolbars - 1;

BEGIN_MESSAGE_MAP(CMainFrame, CBCGPMDIFrameWnd)
	ON_WM_CREATE()
	ON_COMMAND(ID_FILE_CLOSE, OnFileClose)
	ON_COMMAND(ID_VIEW_CUSTOMIZE, OnViewCustomize)
	ON_REGISTERED_MESSAGE(BCGM_RESETTOOLBAR, OnToolbarReset)
	ON_REGISTERED_MESSAGE(BCGM_TOOLBARMENU, OnToolbarContextMenu)
	ON_REGISTERED_MESSAGE(BCGM_CUSTOMIZEHELP, OnHelpCustomizeToolbars)
	ON_COMMAND_RANGE(ID_VIEW_APPLOOK_2000, ID_VIEW_APPLOOK_2007, OnAppLook)
	ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_APPLOOK_2000, ID_VIEW_APPLOOK_2007, OnUpdateAppLook)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};


// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{

	m_nAppLook = theApp.GetInt (_T("ApplicationLook"), ID_VIEW_APPLOOK_2003);
	// TODO: add member initialization code here
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CBCGPMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	OnAppLook (m_nAppLook);

//  Begin tab support
	CBCGPMDITabParams mdiTabParams;
	mdiTabParams.m_bTabIcons = TRUE;
	mdiTabParams.m_style = CBCGPTabWnd::STYLE_3D_SCROLLED;

	EnableMDITabbedGroups (TRUE, mdiTabParams);

	CBCGPDockManager::SetDockMode (DT_SMART);
//  End tab support

	CBCGPToolBar::EnableQuickCustomization ();

	//---------------------------------
	// Set toolbar and menu image size:
	//---------------------------------
	CBCGPToolBar::SetSizes (CSize (28, 28), CSize (22, 22));
	CBCGPToolBar::SetMenuSizes (CSize (22, 22), CSize (16, 16));

	// TODO: Define your own basic commands. Be sure, that each pulldown 
	// menu have at least one basic command.

	CList<UINT, UINT>	lstBasicCommands;

	lstBasicCommands.AddTail (ID_VIEW_TOOLBARS);
	lstBasicCommands.AddTail (ID_APP_EXIT);
	lstBasicCommands.AddTail (ID_APP_ABOUT);
	lstBasicCommands.AddTail (ID_VIEW_TOOLBAR);
	lstBasicCommands.AddTail (ID_VIEW_CUSTOMIZE);
	lstBasicCommands.AddTail (ID_COMMAND_HISTORY);
	lstBasicCommands.AddTail (ID_VIEW_LARGEICON);
	lstBasicCommands.AddTail (ID_VIEW_SMALLICON);
	lstBasicCommands.AddTail (ID_VIEW_LIST);
	lstBasicCommands.AddTail (ID_VIEW_DETAILS);
	lstBasicCommands.AddTail (ID_EDIT_CUT);
	lstBasicCommands.AddTail (ID_EDIT_COPY);
	lstBasicCommands.AddTail (ID_EDIT_PASTE);

	CBCGPToolBar::SetBasicCommands (lstBasicCommands);

	if (!m_wndMenuBar.Create (this))
	{
		TRACE0("Failed to create menubar\n");
		return -1;      // fail to create
	}

	m_wndMenuBar.SetBarStyle(m_wndMenuBar.GetBarStyle() | CBRS_SIZE_DYNAMIC);

	// Remove menubar gripper and borders:
	m_wndMenuBar.SetBarStyle (m_wndMenuBar.GetBarStyle() &
		~(CBRS_GRIPPER | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));
	// Detect color depth. 256 color toolbars can be used in the
	// high or true color modes only (bits per pixel is > 8):
	CClientDC dc (this);
	BOOL bIsHighColor = dc.GetDeviceCaps (BITSPIXEL) > 8;

	UINT uiToolbarHotID = bIsHighColor ? IDB_TOOLBAR256 : 0;
	UINT uiToolbarColdID = bIsHighColor ? IDB_TOOLBARCOLD256 : 0;
	UINT uiMenuID = bIsHighColor ? IDB_MENU256 : IDB_MENU16;

	if (!m_wndToolBar.CreateEx(this) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME, uiToolbarColdID, uiMenuID, FALSE, 0, 0, uiToolbarHotID))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	// Remove toolbar gripper and borders:
	m_wndToolBar.SetBarStyle (m_wndToolBar.GetBarStyle() &
		~(CBRS_GRIPPER | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));

	// Each rebar pane will ocupy its own row:
	DWORD dwStyle = RBBS_GRIPPERALWAYS | RBBS_FIXEDBMP | RBBS_BREAK;

	if (!m_wndReBar.Create(this) ||
		!m_wndReBar.AddBar (&m_wndMenuBar) ||
		!m_wndReBar.AddBar (&m_wndToolBar, NULL, NULL, dwStyle))
	{
		TRACE0("Failed to create rebar\n");
		return -1;      // fail to create
	}

	m_wndMenuBar.AdjustLayout ();
	m_wndToolBar.AdjustLayout ();

	//--------------------------------------------------------------
	// Set up min/max sizes and ideal sizes for pieces of the rebar:
	//--------------------------------------------------------------
	REBARBANDINFO rbbi;

	CRect rectToolBar;
	m_wndToolBar.GetItemRect(0, &rectToolBar);

	rbbi.cbSize = sizeof(rbbi);
	rbbi.fMask = RBBIM_CHILDSIZE | RBBIM_IDEALSIZE | RBBIM_SIZE;
	rbbi.cxMinChild = rectToolBar.Width();
	rbbi.cyMinChild = rectToolBar.Height();
	rbbi.cx = rbbi.cxIdeal = rectToolBar.Width() * m_wndToolBar.GetCount ();
	m_wndReBar.GetReBarCtrl().SetBandInfo (1, &rbbi);
	// TODO: Remove this if you don't want chevrons:
	m_wndMenuBar.EnableCustomizeButton (TRUE, -1, _T(""));
	m_wndToolBar.EnableCustomizeButton (TRUE, -1, _T(""));

	if (!m_wndStatusBar.Create(this) ||

		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// Load control bar icons:
	CBCGPToolBarImages imagesWorkspace;
	imagesWorkspace.SetImageSize (CSize (16, 16));
	imagesWorkspace.SetTransparentColor (RGB (255, 0, 255));
	imagesWorkspace.Load (IDB_WORKSPACE);

	if (!m_wndWorkSpace.Create (_T("ÕË»§"), this, CRect (0, 0, 200, 200),
		TRUE, ID_VIEW_WORKSPACE,
		WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT | CBRS_FLOAT_MULTI))
	{
		TRACE0("Failed to create Workspace bar\n");
		return FALSE;      // fail to create
	}

	m_wndWorkSpace.SetIcon (imagesWorkspace.ExtractIcon (0), FALSE);

	if (!m_wndWorkSpace2.Create (_T("¼ìË÷"), this, CRect (0, 0, 200, 200),
		TRUE, ID_VIEW_WORKSPACE2,
		WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT | CBRS_FLOAT_MULTI))
	{
		TRACE0("Failed to create Workspace bar 2\n");
		return FALSE;      // fail to create
	}

	m_wndWorkSpace2.SetIcon (imagesWorkspace.ExtractIcon (1), FALSE);


	if (!CreateTaskPane ())
	{
		TRACE0("Failed to create tasks pane\n");
		return -1;      // fail to create
	}




	if (!m_wndOutput.Create (_T("Output"), this, CSize (150, 150),
		TRUE /* Has gripper */, ID_VIEW_OUTPUT,
		WS_CHILD | WS_VISIBLE | CBRS_BOTTOM))
	{
		TRACE0("Failed to create output bar\n");
		return -1;      // fail to create
	}

	CString strMainToolbarTitle;
	strMainToolbarTitle.LoadString (IDS_MAIN_TOOLBAR);
	m_wndToolBar.SetWindowText (strMainToolbarTitle);

	// TODO: Delete these three lines if you don't want the toolbar to be dockable

	m_wndWorkSpace.EnableDocking(CBRS_ALIGN_ANY);
	m_wndWorkSpace2.EnableDocking(CBRS_ALIGN_ANY);
	m_wndOutput.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);

	m_wndReBar.EnableDocking (CBRS_TOP);
	DockControlBar (&m_wndReBar);
	
	

	DockControlBar(&m_wndWorkSpace);
  //  Comment by Qiu Simon 2010-2-24 15:43:54 */
  //  must add this temp bar , otherwise the docktowindow will not work.
  //  old code is: 
  //  m_wndTaskPane.DockToWindow(&m_wndWorkSpace,CBRS_ALIGN_BOTTOM);
	CBCGPDockingControlBar* pTabbedBar = NULL; 

	m_wndWorkSpace2.AttachToTabWnd (&m_wndWorkSpace, DM_SHOW, TRUE, &pTabbedBar);

	m_wndTaskPane.EnableDocking(CBRS_ALIGN_ANY);

	DockControlBar(&m_wndTaskPane);

    m_wndTaskPane.DockToWindow(pTabbedBar,CBRS_ALIGN_BOTTOM);
	DockControlBar(&m_wndOutput);


	m_wndToolBar.EnableCustomizeButton (TRUE, ID_VIEW_CUSTOMIZE, _T("Customize..."));

	// Allow user-defined toolbars operations:
//	InitUserToobars (NULL,
//					uiFirstUserToolBarId,
//					uiLastUserToolBarId);

	// Enable control bar context menu (list of bars + customize command):
//	EnableControlBarMenu (	
//		TRUE,				// Enable
//		ID_VIEW_CUSTOMIZE, 	// Customize command ID
//		_T("Customize..."),	// Customize command text
//		ID_VIEW_TOOLBARS);	// Menu items with this ID will be replaced by
							// toolbars menu


	// TODO: Remove this if you don't want tool tips
	m_wndMenuBar.SetBarStyle(m_wndMenuBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY);
	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CBCGPMDIFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}


// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CBCGPMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CBCGPMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG


// CMainFrame message handlers




BOOL CMainFrame::CreateTaskPane ()
{
	CRect rectDummy(0, 0, 200, 400);
	if (!m_wndTaskPane.Create(_T("Tasks Pane"), this, rectDummy, TRUE, ID_VIEW_TASKPANE,
		WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_RIGHT | CBRS_BCGP_CLOSE | CBRS_BCGP_FLOAT))
	{
		TRACE0("Failed to create task pane\n");
		return FALSE;      // fail to create
	}

	return TRUE;
}

BOOL CMainFrame::LoadFrame(UINT nIDResource, DWORD dwDefaultStyle, CWnd* pParentWnd, CCreateContext* pContext) 
{
	// base class does the real work

	if (!CBCGPMDIFrameWnd::LoadFrame(nIDResource, dwDefaultStyle, pParentWnd, pContext))
	{
		return FALSE;
	}

	CWinApp* pApp = AfxGetApp();
	if (pApp->m_pMainWnd == NULL)
		pApp->m_pMainWnd = this;

	return TRUE;
}

void CMainFrame::OnFileClose()
{
   //DestroyWindow();
}

void CMainFrame::OnViewCustomize()
{
	//------------------------------------
	// Create a customize toolbars dialog:
	//------------------------------------
	CBCGPToolbarCustomize* pDlgCust = new CBCGPToolbarCustomize (this,
		TRUE /* Automatic menus scaning */,
		BCGCUSTOMIZE_MENU_SHADOWS | BCGCUSTOMIZE_TEXT_LABELS | 
		BCGCUSTOMIZE_LOOK_2000 | BCGCUSTOMIZE_MENU_ANIMATIONS | BCGCUSTOMIZE_CONTEXT_HELP);

	pDlgCust->EnableUserDefinedToolbars ();
	pDlgCust->Create ();
}

LRESULT CMainFrame::OnToolbarContextMenu(WPARAM,LPARAM lp)
{
	CPoint point (BCG_GET_X_LPARAM(lp), BCG_GET_Y_LPARAM(lp));

	CMenu menu;
	VERIFY(menu.LoadMenu (IDR_POPUP_TOOLBAR));

	CMenu* pPopup = menu.GetSubMenu(0);
	ASSERT(pPopup != NULL);

	CBCGPPopupMenu* pPopupMenu = new CBCGPPopupMenu;
	pPopupMenu->Create (this, point.x, point.y, pPopup->Detach ());

	return 0;
}

afx_msg LRESULT CMainFrame::OnToolbarReset(WPARAM wp, LPARAM)
{
	UINT uiToolBarId = (UINT) wp;
	if (uiToolBarId != IDR_MAINFRAME)
	{
		return 0;
	}

	// Replace "Back" and "Forward" buttons by the menu buttons
	// with the history lists:

// 	CMenu menuHistory;
// 	menuHistory.LoadMenu (IDR_HISTORY_POPUP);
// 
// 	CBCGPToolbarMenuButton btnBack (ID_GO_BACK, menuHistory, 
// 					CImageHash::GetImageOfCommand (ID_GO_BACK), _T("Back"));
// 	btnBack.m_bText = TRUE;
// 	m_wndToolBar.ReplaceButton (ID_GO_BACK, btnBack);
// 
// 	m_wndToolBar.ReplaceButton (ID_GO_FORWARD,
// 		CBCGPToolbarMenuButton (ID_GO_FORWARD, menuHistory, 
// 					CImageHash::GetImageOfCommand (ID_GO_FORWARD), _T("Forward")));

	// "Folders" button has a text label:
	m_wndToolBar.SetToolBarBtnText (m_wndToolBar.CommandToIndex (ID_RECORD_NEW),
		_T("ÐÂ½¨¼ÇÂ¼"));
	// "Folders" button has a text label:
	m_wndToolBar.SetToolBarBtnText (m_wndToolBar.CommandToIndex (ID_RECORD_DEL_SELECTED),
		_T("É¾³ý¼ÇÂ¼"));
	// "Folders" button has a text label:
	m_wndToolBar.SetToolBarBtnText (m_wndToolBar.CommandToIndex (ID_RECORD_MODIFY),
		_T("ÐÞ¸Ä¼ÇÂ¼"));
	// "Folders" button has a text label:
	m_wndToolBar.SetToolBarBtnText (m_wndToolBar.CommandToIndex (ID_RECORD_COPY),
		_T("¿½±´"));
	// "Folders" button has a text label:
	m_wndToolBar.SetToolBarBtnText (m_wndToolBar.CommandToIndex (ID_RECORD_PASTE),
		_T("Õ³Ìù"));
	// "Folders" button has a text label:
	m_wndToolBar.SetToolBarBtnText (m_wndToolBar.CommandToIndex (ID_SUBCOUNT_EXPAND_ALL),
		_T("Õ¹¿ª"));
	// "Folders" button has a text label:
	m_wndToolBar.SetToolBarBtnText (m_wndToolBar.CommandToIndex (ID_QUERY),
		_T("²éÑ¯"));
	// "Folders" button has a text label:
	m_wndToolBar.SetToolBarBtnText (m_wndToolBar.CommandToIndex (ID_EDIT_CAL_SUM),
		_T("¼ÆËãÓà¶î"));

	// Replace "Views" button by the menu button:
// 	CMenu menuViews;
// 	menuViews.LoadMenu (IDR_VIEWS_POPUP);
// 
// 	m_wndToolBar.ReplaceButton (ID_VIEW_VIEWS,
// 		CBCGPToolbarMenuButton (-1, menuViews, 
// 					CImageHash::GetImageOfCommand (ID_VIEW_VIEWS), _T("Views")));

	return 0;
}

LRESULT CMainFrame::OnHelpCustomizeToolbars(WPARAM wp, LPARAM lp)
{
	int iPageNum = (int) wp;

	CBCGPToolbarCustomize* pDlg = (CBCGPToolbarCustomize*) lp;
	ASSERT_VALID (pDlg);

	// TODO: show help about page number iPageNum

	return 0;
}

void CMainFrame::OnAppLook(UINT id)
{
	CBCGPDockManager::SetDockMode (DT_SMART);

	m_nAppLook = id;

	CBCGPTabbedControlBar::m_StyleTabWnd = CBCGPTabWnd::STYLE_3D;

	switch (m_nAppLook)
	{
	case ID_VIEW_APPLOOK_2000:
		// enable Office 2000 look:
		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManager));
		break;

	case ID_VIEW_APPLOOK_XP:
		// enable Office XP look:
		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManagerXP));
		break;

	case ID_VIEW_APPLOOK_WIN_XP:
		// enable Windows XP look (in other OS Office XP look will be used):
		CBCGPWinXPVisualManager::m_b3DTabsXPTheme = TRUE;
		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPWinXPVisualManager));
		break;

	case ID_VIEW_APPLOOK_2003:
		// enable Office 2003 look:
		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManager2003));
		CBCGPDockManager::SetDockMode (DT_SMART);
		break;

	case ID_VIEW_APPLOOK_2007:
		// enable Office 2007 look:
		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManager2007));
		CBCGPDockManager::SetDockMode (DT_SMART);
		break;

	case ID_VIEW_APPLOOK_VS2005:
		// enable VS.NET 2005 look:
		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManagerVS2005));
		CBCGPDockManager::SetDockMode (DT_SMART);
		break;

	default:
		ASSERT (FALSE);
	}

	CBCGPDockManager* pDockManager = GetDockManager ();
	if (pDockManager != NULL)
	{
		ASSERT_VALID (pDockManager);
		pDockManager->AdjustBarFrames ();
	}

	CBCGPTabbedControlBar::ResetTabs ();

	RecalcLayout ();
	RedrawWindow (NULL, NULL, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE);

	theApp.WriteInt (_T("ApplicationLook"), m_nAppLook);
}


/*******************************************
    Function Name :	 
    Create by     :	  Qiu Simon
    Input         :   
    Output        :   
    Description   :   
    Date          :   2009-2-4 12:32:04
********************************************/
CBankbookTree* CMainFrame::GetBookTree()
{
    return &(m_wndWorkSpace.m_wndTree);
}

void CMainFrame::OnUpdateAppLook(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio (m_nAppLook == pCmdUI->m_nID);
}



/*******************************************
    Function Name : 
    author        : Qiu Guohua
    Date          : 2009-2-14 14:19:00
    Description   : 
    Return type  : 
    Argument      : 
********************************************/
BOOL CMainFrame::ShowAccountInfo(CIDSet *pSet)
{
	return m_wndTaskPane.ShowAccountInfo(pSet);
}

void CMainFrame::UpdateQueryList()
{
	m_wndTaskPane.UpdateMRUFilesList();

}

// ChildFrm.cpp : implementation of the CReportFrame class
//

#include "stdafx.h"
#include "..\SmallHorse.h"

#include "reportframe.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CReportFrame

IMPLEMENT_DYNCREATE(CReportFrame, CBCGPMDIChildWnd)

BEGIN_MESSAGE_MAP(CReportFrame, CBCGPMDIChildWnd)
	//{{AFX_MSG_MAP(CReportFrame)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_COMMAND(ID_EDIT_PASTE_SPECIAL, OnEditPasteSpecial)
	ON_WM_CREATE()
	ON_COMMAND(ID_VIEW_OUTPUT, OnViewOutput)
	ON_UPDATE_COMMAND_UI(ID_VIEW_OUTPUT, OnUpdateViewOutput)
#if 0
	ON_COMMAND(ID_VIEW_FILTER, OnViewFilter)
#endif
	ON_COMMAND(ID_SET_AS_AUTORETURN_CREDIT, OnSetAsAutoreturnCredit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReportFrame construction/destruction

CReportFrame::CReportFrame()
{
	// TODO: add member initialization code here
	
}

CReportFrame::~CReportFrame()
{
}

BOOL CReportFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	if( !CBCGPMDIChildWnd::PreCreateWindow(cs) )
		return FALSE;

	cs.style &= ~WS_SYSMENU;

	return TRUE;
}

void CReportFrame::ActivateFrame(int nCmdShow)
{
	// TODO: Modify this function to change how the frame is activated.

	nCmdShow = SW_SHOWMAXIMIZED;
	CBCGPMDIChildWnd::ActivateFrame(nCmdShow);
}


/////////////////////////////////////////////////////////////////////////////
// CReportFrame diagnostics

#ifdef _DEBUG
void CReportFrame::AssertValid() const
{
	CBCGPMDIChildWnd::AssertValid();
}

void CReportFrame::Dump(CDumpContext& dc) const
{
	CBCGPMDIChildWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CReportFrame message handlers

void CReportFrame::OnEditCopy() 
{
	// TODO: Add your command handler code here
}
void CReportFrame::OnUpdateFrameTitle(BOOL bAddToTitle)
{
///		CMDIChildWnd::OnUpdateFrameTitle(bAddToTitle);
	if(m_strID != _T(""))
	{
		SetWindowText(m_strID);
	}
	else
	{
		SetWindowText(m_strTitle);
	}
}


void CReportFrame::OnEditCut() 
{
	// TODO: Add your command handler code here
	
}

void CReportFrame::OnEditPaste() 
{
	// TODO: Add your command handler code here
	
}

void CReportFrame::OnEditPasteSpecial() 
{
	// TODO: Add your command handler code here
	
}

int CReportFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CBCGPMDIChildWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	return 0;
}

void CReportFrame::OnViewOutput() 
{
	ShowControlBar (&m_wndOutput,
					!(m_wndOutput.IsVisible ()),
					FALSE, TRUE);
	RecalcLayout ();
}

void CReportFrame::OnUpdateViewOutput(CCmdUI* pCmdUI) 
{

	pCmdUI->Enable(m_wndOutput.m_hWnd != NULL);
	if(m_wndOutput.m_hWnd != NULL)
	{
		pCmdUI->SetCheck (m_wndOutput.IsVisible ());
	}
	else
	{
		pCmdUI->SetCheck (FALSE);
	}
}


/*******************************************
    Function Name : 
    author        : Qiu Guohua
    Date          : 2009-3-5 22:52:20
    Description   : 
    Return type  : 
    Argument      : 
********************************************/
void CReportFrame::SetFilter(const CString &strFilter, const CString &strSort)
{
	m_strFilter = strFilter;
	m_strSort = strSort;
	int n = m_strFilter.Find(_T("Item_Book_ID=\'"),0);
	if(n!=-1)
	{
		m_strID = m_strFilter.Mid(14,m_strFilter.GetLength()-15);
		m_ViewType = VIEW_TYPE_RECORD_IN_ONE_COUNT;
	}
	else
	{
		m_ViewType = VIEW_TYPE_RECORD_QUERY;
	}

}

void CReportFrame::SetTodoType()
{
    m_ViewType = VIEW_TYPE_TODO;
    m_strTitle = "TODO LIST";
}

void CReportFrame::OnViewFilter() 
{
	AfxMessageBox(m_strFilter);
}


/*******************************************
    Function Name : 
    author        : Qiu Guohua
    Date          : 2009-4-24 21:24:20
    Description   : 
    Return type  : 
    Argument      : 
********************************************/
VIEW_TYPE CReportFrame::GetViewType()
{
	return m_ViewType;
}


/*******************************************
    Function Name : 
    author        : Qiu Guohua
    Date          : 2009-4-29 22:17:07
    Description   : 
    Return type  : 
    Argument      : 
********************************************/
void CReportFrame::SetCountsFilter(const CString &strFilter,VIEW_TYPE view_Type, LPCTSTR lpStrName)
{
	m_ViewType = view_Type;
	m_strFilter = strFilter;
	if(lpStrName)
	{
		m_strTitle = lpStrName;
	}
}

/*******************************************
    Function Name : 
    author        : Qiu Guohua
    Date          : 2009-4-29 22:17:07
    Description   : This function is a function similar to SetCountsFilter
                    to set entry information used to display.
    Return type  : 
    Argument      : 
********************************************/
void CReportFrame::SetReportInfo(const CString &strID)
{
	m_ViewType = VIEW_TYPE_CREDIT_REPORT;
	m_strID = strID;
}

void CReportFrame::CreateCurveView()
{
	if (!m_wndOutput.Create (_T("Output"), this, CRect (0, 0, 150, 150),
		TRUE /* Has gripper */, ID_VIEW_OUTPUT,
		WS_CHILD | WS_VISIBLE | CBRS_BOTTOM | CBRS_FLOAT_MULTI))
	{
		TRACE0("Failed to create output bar\n");
		return;
	}

	m_wndOutput.EnableDocking(CBRS_ALIGN_BOTTOM);
	EnableDocking(CBRS_ALIGN_BOTTOM);
	DockControlBar(&m_wndOutput);
}

void CReportFrame::SetPage(LPCTSTR lpPagePath)
{
    if(lpPagePath != NULL)
    {
        m_strPagePath = lpPagePath;
    }
    else
    {
        m_strPagePath = _T("");
    }

}
void CReportFrame::OnSetAsAutoreturnCredit() 
{
    CString strid;
	if(m_strID != _T(""))
	{
        theApp.SetAutoReturnCreditCard(m_strID);
	}
	else
	{
		AfxMessageBox("Not a credit card.");
	}
	
}

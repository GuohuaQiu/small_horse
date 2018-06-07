// TaskPane.cpp : implementation of the CTaskPane class
//

#include "stdafx.h"
#include "..\SmallHorse.h"
#include "TaskPane.h"
#include "idset.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTaskPane

BEGIN_MESSAGE_MAP(CTaskPane, CBCGPTasksPane)
	//{{AFX_MSG_MAP(CTaskPane)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTaskPane construction/destruction

CTaskPane::CTaskPane()
{
	m_nDocumentsGroup = -1;
	// TODO: add one-time construction code here

}

CTaskPane::~CTaskPane()
{
}

/////////////////////////////////////////////////////////////////////////////
// CTaskPane message handlers

int CTaskPane::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CBCGPTasksPane::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	SetCaption (_T("Tasks Pane"));

	SetIconsList (IDB_TASKS, 16);
	EnableNavigationToolbar (TRUE);

	m_nDocumentsGroup = AddGroup (_T("最近查询"), FALSE, TRUE);

	// Add MRU list:
//	AddTask (m_nDocumentsGroup, _T("导入记录"), 0, IDC_LOAD_CSV);
//	AddTask (m_nDocumentsGroup, _T("导入子账户"), 0, IDC_LOAD_SUBCOUNT_CSV);
//	AddTask (m_nDocumentsGroup, _T("打开所有子账户"), 0, IDC_OPEN_SUB_COUNTS);
	AddQueryList(m_nDocumentsGroup);

	m_nAccountGroup = AddGroup (_T("账号"));


	// Create tasks pane windows.
	// TODO: create your own tasks panes here:

	return 0;
}

void CTaskPane::UpdateMRUFilesList ()
{
	AddQueryList(m_nDocumentsGroup);
	RedrawWindow ();
}


/*******************************************
    Function Name : 
    author        : Qiu Guohua
    Date          : 2009-2-14 14:13:25
    Description   : 
    Return type  : 
    Argument      : 
********************************************/
BOOL CTaskPane::ShowAccountInfo(CIDSet *pSet)
{
	if(pSet == NULL)
		return FALSE;
	RemoveGroup(m_nAccountGroup);
	m_nAccountGroup = AddGroup (_T("账号"));

	AddLabel (m_nAccountGroup, pSet->m_ID);
	AddLabel (m_nAccountGroup, pSet->m_bank);
	AddLabel (m_nAccountGroup, pSet->m_name);
	AddLabel (m_nAccountGroup, pSet->m_remain);
    if(pSet->m_bExist)
    {
        AddLabel(m_nAccountGroup,"状态：正常使用");
    }
    else
    {
        AddLabel(m_nAccountGroup,"状态：已经注销");
    }
    AddLabel(m_nAccountGroup,pSet->GetType());

    
	RedrawWindow();
	return TRUE;
}

int CTaskPane::AddQueryList(int nGroup, int nMaxFiles)
{
	POSITION pos = m_lstTaskGroups.FindIndex (nGroup);
	if (pos == NULL)
	{
		ASSERT (FALSE);
		return -1;
	}

	CBCGPTasksGroup* pGroup = (CBCGPTasksGroup*) m_lstTaskGroups.GetAt (pos);
	ASSERT_VALID (pGroup);

	POSITION posFirstMRUFile = NULL;

	// Clean up old MRU files from the group:
	for (pos = pGroup->m_lstTasks.GetHeadPosition (); pos != NULL;)
	{
		POSITION posSave = pos;

		CBCGPTask* pTask = (CBCGPTask*) pGroup->m_lstTasks.GetNext (pos);
		ASSERT_VALID (pTask);

		if (pTask->m_uiCommandID >= ID_FILE_MRU_QUERY0 &&
			pTask->m_uiCommandID <= ID_FILE_MRU_QUERY15)
		{
			posFirstMRUFile = posSave;
			pGroup->m_lstTasks.GetNext (posFirstMRUFile);

			delete pGroup->m_lstTasks.GetAt (posSave);
			pGroup->m_lstTasks.RemoveAt (posSave);
		}
	}

	CQueryItemList* pQueryList = &(theApp.m_querylist);


	int nNum = min (pQueryList->GetCount(), nMaxFiles);

	// Add new MRU files to the group:
	pos = pQueryList->GetHeadPosition();
	for (int i = 0; i < nNum; i++)
	{
		CQueryItem* pItem = pQueryList->GetNext(pos);
		CBCGPTask* pTask = new CBCGPTask (pGroup, pItem->strName, -1, ID_FILE_MRU_QUERY0 + i);
		ASSERT_VALID (pTask);
		
		if (posFirstMRUFile == NULL)
		{
			pGroup->m_lstTasks.AddTail (pTask);
		}
		else
		{
			pGroup->m_lstTasks.InsertBefore (posFirstMRUFile, pTask);
		}
	}
	CollapseGroup(pGroup);

	AdjustScroll ();
	ReposTasks ();

	return (int) pGroup->m_lstTasks.GetCount () - 1;
}


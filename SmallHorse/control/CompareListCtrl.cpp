// CompareListCtrl.cpp: implementation of the CCompareListCtrl class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "..\SmallHorse.h"
#include "CompareListCtrl.h"
#include "listcompare.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNCREATE(CCompareListCtrl,CMailReportCtrl)



enum
{
    COLUMN_ID____, 
		COLUMN_DATE__, 
		COLUMN_CHANGE, 
		COLUMN_REASON, 
		COLUMN_TYPE__, 
		COLUMN_SITE__, 
		COLUMN_SUBCOUNT,
		COLUMN_BASE_NUMBER
};
#define COLUMN_MID 1

enum
{
    COLUMN_RIGHT_BASE = COLUMN_BASE_NUMBER + COLUMN_MID
};

#define COLUMN_COUNT COLUMN_RIGHT_BASE + COLUMN_BASE_NUMBER









Alike2* CCompareListCtrl::m_pJoinA = NULL;
Alike2* CCompareListCtrl::m_pJoinB = NULL;

CCompareListCtrl::CCompareListCtrl()
{


}

BEGIN_MESSAGE_MAP(CCompareListCtrl, CMailReportCtrl)
	//{{AFX_MSG_MAP(CCompareListCtrl)
	ON_COMMAND(ID_COMPARE_COPY_TO_RIGHT, OnCompareCopyToRight)
	ON_UPDATE_COMMAND_UI(ID_COMPARE_COPY_TO_RIGHT, OnUpdateCompareCopyToRight)
	ON_COMMAND(ID_COMPARE_COPY_TO_LEFT, OnCompareCopyToLeft)
	ON_UPDATE_COMMAND_UI(ID_COMPARE_COPY_TO_LEFT, OnUpdateCompareCopyToLeft)
	ON_COMMAND(ID_COMPARE_SAVE, OnCompareSave)
	ON_UPDATE_COMMAND_UI(ID_COMPARE_SAVE, OnUpdateCompareSave)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_COMAPRE_JOIN, OnComapreJoin)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CCompareListCtrl::~CCompareListCtrl()
{
    m_pJoinList = NULL;

}


/*******************************************
    Function Name :	 
    Create by     :	  Qiu Simon
    Input         :   
    Output        :   
    Description   :   
    Date          :   9/15/2011 4:16:35 PM
********************************************/
void CCompareListCtrl::OnContextMenu(CWnd*, CPoint point)
{
	theApp.ShowPopupMenu (IDR_MENU_COMPARE, point, this);
}


/*******************************************
    Function Name :	 
    Create by     :	  Qiu Simon
    Input         :   
    Output        :   
    Description   :   
    Date          :   9/15/2011 4:18:15 PM
********************************************/
void CCompareListCtrl::OnCompareCopyToRight() 
{
    CDWordArray dbAry;
    int n = GetSelectedRows(dbAry);
    Alike2* palike = NULL;
    if(dbAry.GetSize()>0)
    {
        for(int i = 0;i<n;i++)
        {
            palike = ((Alike2 *) dbAry[i]) ;
            palike->CopyA2B();
			UpdateRow(palike);
        }
    }
}


/*******************************************
    Function Name :	 
    Create by     :	  Qiu Simon
    Input         :   
    Output        :   
    Description   :   
    Date          :   9/15/2011 4:18:19 PM
********************************************/
void CCompareListCtrl::OnUpdateCompareCopyToRight(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}


/*******************************************
    Function Name :	 
    Create by     :	  Qiu Simon
    Input         :   
    Output        :   
    Description   :   
    Date          :   9/15/2011 4:18:22 PM
********************************************/
void CCompareListCtrl::OnCompareCopyToLeft() 
{
    CDWordArray dbAry;
    int n = GetSelectedRows(dbAry);
    Alike2* palike = NULL;
    if(dbAry.GetSize()>0)
    {
        for(int i = 0;i<n;i++)
        {
            palike = ((Alike2 *) dbAry[i]) ;
            palike->CopyB2A();
			UpdateRow(palike);
        }
    }
}


/*******************************************
    Function Name :	 
    Create by     :	  Qiu Simon
    Input         :   
    Output        :   
    Description   :   
    Date          :   9/15/2011 4:18:26 PM
********************************************/
void CCompareListCtrl::OnUpdateCompareCopyToLeft(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CCompareListCtrl::UpdateRow(Alike2* pAlike)
{
	CBCGPGridRow* prow = FindRowByData((DWORD)pAlike);
	UpdateRow(prow);
}

void CCompareListCtrl::AddAlike(Alike2 *pAlike)
{
    CBCGPGridRow* pRow = CreateRow (COLUMN_COUNT);
    if(pRow!=NULL)
    {
		AddRow(pRow,FALSE);
        pRow->SetData( (DWORD)pAlike);
		UpdateRow(pRow);
	}
}

void CCompareListCtrl::UpdateRow(CBCGPGridRow *pRow)
{
    if(pRow!=NULL)
    {
		Alike2* palike = (Alike2*)pRow->GetData();
		ASSERT(palike);
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
					pRow->GetItem(i+COLUMN_RIGHT_BASE)->SetTextColor(RGB(0,55,0),FALSE);
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
    }
}

void CCompareListCtrl::InitCompareCtrl(CB_FUNC_ONDBCLK_ITEM pfun,CListCompare* pListCompare)
{
    InsertColumn (COLUMN_ID____, _T("序号"), 15);
    InsertColumn (COLUMN_DATE__, _T("日期"), 30);
    InsertColumn (COLUMN_CHANGE, _T("收支"), 30);
    InsertColumn (COLUMN_REASON, _T("事由"), 120);
    InsertColumn (COLUMN_TYPE__, _T("类型"), 20);
    InsertColumn (COLUMN_SITE__, _T("地点"), 30);
    InsertColumn (COLUMN_SUBCOUNT, _T("子账号"), 1);
	
    InsertColumn(COLUMN_BASE_NUMBER,"  ",20);
	
    InsertColumn (COLUMN_ID____ + COLUMN_RIGHT_BASE, _T("序号"), 15);
    InsertColumn (COLUMN_DATE__+ COLUMN_RIGHT_BASE, _T("日期"), 30);
    InsertColumn (COLUMN_CHANGE+ COLUMN_RIGHT_BASE, _T("收支"), 30);
    InsertColumn (COLUMN_REASON+ COLUMN_RIGHT_BASE, _T("事由"), 120);
    InsertColumn (COLUMN_TYPE__+ COLUMN_RIGHT_BASE, _T("类型"), 20);
    InsertColumn (COLUMN_SITE__+ COLUMN_RIGHT_BASE, _T("地点"), 30);
    InsertColumn (COLUMN_SUBCOUNT+ COLUMN_RIGHT_BASE, _T("子账号"), 1);
	
	
    EnableColumnAutoSize (TRUE);
    SetDbClkCBFunc(pfun);

    m_pListCompare = pListCompare;
    m_pJoinList = &(m_pListCompare->m_lstJoin);
}


/*******************************************
    Function Name :	 
    Create by     :	  Qiu Simon
    Input         :   
    Output        :   
    Description   :   
    Date          :   9/16/2011 10:08:24 AM
********************************************/
void CCompareListCtrl::OnCompareSave() 
{
    m_pListCompare->SaveAlltoA();
    m_pListCompare->SaveAlltoB();
}

void CCompareListCtrl::OnUpdateCompareSave(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}
void MakeManualJoin();
void CCompareListCtrl::OnComapreJoin() 
{
    CDWordArray dbAry;
    int n = GetSelectedRows(dbAry);
    Alike2* palike = NULL;
    if(dbAry.GetSize()!=1)
    {
        AfxMessageBox("只能选一行！");
        return ;
    }
    palike = ((Alike2 *) dbAry[0]) ;
    if(palike->m_pRecordA != NULL && palike->m_pRecordB == NULL)
    {
        m_pJoinA = palike;
        if(m_pJoinB != NULL)
        {
            MakeManualJoin();
        }
    }
    else if(palike->m_pRecordA == NULL && palike->m_pRecordB != NULL)
    {
        m_pJoinB = palike;
        if(m_pJoinA != NULL)
        {
            MakeManualJoin();
        }
    }
    else
    {
        AfxMessageBox("Error!");

    }
}

void CCompareListCtrl::MakeManualJoin()
{
    ASSERT(m_pJoinB != NULL && m_pJoinA != NULL);
    m_pJoinA->m_pRecordB = m_pJoinB->m_pRecordB;
    m_pJoinB->m_pRecordB = NULL;
    CBCGPGridRow* prow ;
    int ncount = this->GetRowCount();
    for(int i = 0;i< ncount;i++)
    {
        prow = this->GetRow(i);
        if(prow->GetData() == (DWORD)m_pJoinB)
        {
            this->RemoveRow(i);
            break;
        }
    }

    POSITION pos = m_pJoinList->GetHeadPosition();
    POSITION pos_prev;
    while(pos)
    {
        pos_prev = pos;
        Alike2 * plike = m_pJoinList->GetNext(pos);
        if(plike == m_pJoinB)
        {
            m_pJoinList->RemoveAt(pos_prev);
            delete plike;
        }
    }
    prow = FindRowByData((DWORD)m_pJoinA);
	UpdateRow(prow);
    m_pJoinA = NULL;
    m_pJoinB = NULL;
    AdjustLayout();
}

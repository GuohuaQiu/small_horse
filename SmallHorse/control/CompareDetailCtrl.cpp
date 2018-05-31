// CompareDetailCtrl.cpp: implementation of the CCompareDetailCtrl class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "..\SmallHorse.h"
#include "CompareDetailCtrl.h"
#include "DetailItem.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNCREATE(CCompareDetailCtrl,CBCGPReportCtrl)

CCompareDetailCtrl::CCompareDetailCtrl()
{
    m_pAlike = NULL;

}

CCompareDetailCtrl::~CCompareDetailCtrl()
{

}

BEGIN_MESSAGE_MAP(CCompareDetailCtrl, CBCGPReportCtrl)
	//{{AFX_MSG_MAP(CCompareListCtrl)
	ON_WM_CONTEXTMENU()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
void CCompareDetailCtrl::Setup()
{
    InsertColumn (0, _T("项目"), 15);
    InsertColumn (1, _T("LEFT"), 30);
    InsertColumn (2, _T("RIGHT"), 30);

    for(int i = 0;i<LINE_COUNT;i++)
    {
        CBCGPGridRow* pRow = CreateRow(3);
        AddRow(pRow,FALSE);
    }
    
    GetDetailItem(LINE_OPER_DAY,0)->SetValue((LPCTSTR)"日期",FALSE);
    GetDetailItem(LINE_VALUE        ,0)->SetValue((LPCTSTR)"金额",FALSE);
    GetDetailItem(LINE_COMMENT      ,0)->SetValue((LPCTSTR)"备注",FALSE);
    GetDetailItem(LINE_SITE         ,0)->SetValue((LPCTSTR)"地点",FALSE);
    GetDetailItem(LINE_TYPE         ,0)->SetValue((LPCTSTR)"类型",FALSE);
    GetDetailItem(LINE_ACCOUNT      ,0)->SetValue((LPCTSTR)"账号",FALSE);
    GetDetailItem(LINE_SUB_COUNT    ,0)->SetValue((LPCTSTR)"子账号",FALSE);
    GetDetailItem(LINE_ARRAY_NUMBER ,0)->SetValue((LPCTSTR)"序号",FALSE);
    GetDetailItem(LINE_ADD_TIME     ,0)->SetValue((LPCTSTR)"新加日期",FALSE);
    GetDetailItem(LINE_MODIFY_TIME  ,0)->SetValue((LPCTSTR)"修改日期",FALSE);

    EnableColumnAutoSize (TRUE);

    
}


/*******************************************
    Function Name :	 
    Create by     :	  Qiu Simon
    Input         :   A Row which contains the content .
    Output        :   
    Description   :   This is the interface that the content input.
    Date          :   2/12/2011 2:47:05 PM
********************************************/
void CCompareDetailCtrl::ShowDetail(CBCGPGridRow *pRow)
{
    DWORD dwData = pRow->GetData();
    if(dwData!=0)
    {
        m_pAlike = (Alike2 *)dwData;
        FillContent(1, m_pAlike->m_pRecordA);
        FillContent(2, m_pAlike->m_pRecordB);
        SetItemsColor();
        AdjustLayout();
    }
}



CBCGPGridItem* CCompareDetailCtrl::GetDetailItem(int line, int column)
{
    return GetRow(line)->GetItem(column);
}


/*******************************************
    Function Name :	 
    Create by     :	  Qiu Simon
    Input         :   
    Output        :   
    Description   :   
    Date          :   2/11/2011 2:54:29 PM
********************************************/
void CCompareDetailCtrl::FillContent(int nColumn,LPRECORD pRecord)
{
    if(pRecord)
    {
        GetRow(LINE_OPER_DAY)->GetItem(nColumn)->SetValue (_variant_t((DATE)pRecord->m_day,VT_DATE), FALSE);
        GetRow(LINE_VALUE)->GetItem(nColumn)->SetValue ((LPCTSTR)pRecord->m_addorsub,FALSE);
        GetRow(LINE_COMMENT)->GetItem(nColumn)->SetValue ((LPCTSTR)pRecord->m_remain,FALSE);
        GetRow(LINE_SITE)->GetItem(nColumn)->SetValue ((LPCTSTR)pRecord->m_strSite, FALSE);
        GetRow(LINE_TYPE)->GetItem(nColumn)->SetValue ((LPCTSTR)theApp.m_cType[pRecord->m_bType], FALSE);
        GetRow(LINE_ACCOUNT)->GetItem(nColumn)->SetValue ((LPCTSTR)pRecord->m_ID, FALSE);
        GetRow(LINE_SUB_COUNT)->GetItem(nColumn)->SetValue ((LPCTSTR)pRecord->m_strSubCount, FALSE);
        GetRow(LINE_ARRAY_NUMBER)->GetItem(nColumn)->SetValue ((LONG)pRecord->m_arraynumber, FALSE);
    }
    else
    {
        CDetailItem* pItem = NULL;
        for(int i = 0;i<LINE_COUNT;i++)
        {
            pItem = (CDetailItem*)(GetRow(i)->GetItem(nColumn));
            pItem->EmptyItem();
        }
    }
}

void CCompareDetailCtrl::SetItemsColor()
{
    BOOL bBothExist = (m_pAlike->m_pRecordA!=NULL)&&(m_pAlike->m_pRecordB!=NULL);
    if(bBothExist)
    {
        if(!(m_pAlike->m_dwSameFields & FIELD_COMMENT))
        {
            GetDetailItem(LINE_COMMENT,1)->SetTextColor(RGB(255,0,0),FALSE);
            GetDetailItem(LINE_COMMENT,2)->SetTextColor(RGB(255,0,0),FALSE);
        }
        else
        {
            GetDetailItem(LINE_COMMENT,1)->SetTextColor(RGB(0,0,0),FALSE);
            GetDetailItem(LINE_COMMENT,2)->SetTextColor(RGB(0,0,0),FALSE);
        }
        if(!(m_pAlike->m_dwSameFields & FIELD_TYPE))
        {
            GetDetailItem(LINE_TYPE,1)->SetTextColor(RGB(255,0,0),FALSE);
            GetDetailItem(LINE_TYPE,2)->SetTextColor(RGB(255,0,0),FALSE);
        }
        else
        {
            GetDetailItem(LINE_TYPE,1)->SetTextColor(RGB(0,0,0),FALSE);
            GetDetailItem(LINE_TYPE,2)->SetTextColor(RGB(0,0,0),FALSE);
        }
        if(!(m_pAlike->m_dwSameFields & FIELD_SITE))
        {
            GetDetailItem(LINE_SITE,1)->SetTextColor(RGB(255,0,0),FALSE);
            GetDetailItem(LINE_SITE,2)->SetTextColor(RGB(255,0,0),FALSE);
        }
        else
        {
            GetDetailItem(LINE_SITE,1)->SetTextColor(RGB(0,0,0),FALSE);
            GetDetailItem(LINE_SITE,2)->SetTextColor(RGB(0,0,0),FALSE);
        }
    }
    else
    {
        if(m_pAlike->m_pRecordA!=NULL)
        {
            GetDetailItem(LINE_COMMENT,1)->SetTextColor(RGB(0,0,255),FALSE);
            GetDetailItem(LINE_TYPE,1)->SetTextColor(RGB(0,0,255),FALSE);
            GetDetailItem(LINE_SITE,1)->SetTextColor(RGB(0,0,255),FALSE);
        }
        else if(m_pAlike->m_pRecordB!=NULL)
        {
            GetDetailItem(LINE_COMMENT,2)->SetTextColor(RGB(0,0,255),FALSE);
            GetDetailItem(LINE_TYPE,2)->SetTextColor(RGB(0,0,255),FALSE);
            GetDetailItem(LINE_SITE,2)->SetTextColor(RGB(0,0,255),FALSE);
        }
    }

}


/*******************************************
    Function Name :	 
    Create by     :	  Qiu Simon
    Input         :   
    Output        :   
    Description   :   
    Date          :   9/15/2011 4:16:35 PM
********************************************/
void CCompareDetailCtrl::OnContextMenu(CWnd*, CPoint point)
{
	theApp.ShowPopupMenu (IDR_MENU_COMPARE, point, this);
}


// GroupRow.cpp: implementation of the CGroupRow class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GroupRow.h"
#include "..\SmallHorse.h"
#include "ReportDemoView.h"
//#include "childfrm.h"
#include "SubCountSet.h"
#include "MailReportCtrl.h"
#include "Windows.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGroupRow::CGroupRow(const CString& strGroupName)
:CBCGPReportRow(strGroupName)
{
    m_bNeedUpdateTip = TRUE;
}

CGroupRow::~CGroupRow()
{

}


/*******************************************
    Function Name :	 
    Create by     :	  Qiu Simon
    Input         :   
    Output        :   
    Description   :   
    Date          :   2010-2-23 16:47:48
********************************************/
CString CGroupRow::GetTipString(const CString &strID)
{
  if(m_bNeedUpdateTip)
  {
    CSubCountSet* pset = theApp.GetSubCountSet();
    if(pset->Find(strID,m_strName))
    {
      CString strTip;
      pset->GetTipString(m_strTip);
    }
    else
    {
      m_strTip = strID + " " + m_strName;
    }
    m_bNeedUpdateTip = FALSE;
  }
  return m_strTip;
  
}


/*******************************************
    Function Name :	 
    Create by     :	  Qiu Simon
    Input         :   
    Output        :   
    Description   :   
    Date          :   2010-2-24 11:37:08
********************************************/
const CRect CGroupRow::GetTipRect()
{
    int dx = m_pWndList->IsSortingMode () && !m_pWndList->IsGrouping () ? 0 : 
    GetHierarchyLevel () * m_pWndList->GetRowHeight();
    
    CRect rectExpand = m_Rect;
    rectExpand.DeflateRect (dx, 0, 0, 0);
    rectExpand.right = min (rectExpand.left + m_pWndList->GetRowHeight(), rectExpand.right);
    CRect rect;
    rect = m_Rect;
    rect.left = rectExpand.right+1;
    rect.top += 2;
    rect.bottom -= 2;
    return rect;
    
}


/*******************************************
    Function Name :	 
    Create by     :	  Qiu Simon
    Input         :   
    Output        :   
    Description   :   
    Date          :   2010-3-11 17:19:15
********************************************/
CString& CGroupRow::GetText()
{
    return m_strName;

}
#define MARGIN_ITEMS 2
#define ICON_W       16

void DrawIcon(CDC* pDC,int x,int y,UINT uIconID)
{
    CBitmap bmp;
    bmp.LoadBitmap(uIconID);
    CDC dc;
    dc.CreateCompatibleDC(pDC);
    CBitmap* poldbmp = dc.SelectObject(&bmp);

    ::TransparentBlt(pDC->GetSafeHdc(),x,y,ICON_W,ICON_W,dc.GetSafeHdc(),0,0,ICON_W,ICON_W,RGB(255,255,255));

 //   pDC->BitBlt(&dc,0,0,SRCCOPY);
    dc.SelectObject(poldbmp);
    bmp.DeleteObject();
}

void CGroupRow::OnDrawName (CDC* pDC, CRect rect)
{
    CMailReportCtrl* pWndList = (CMailReportCtrl*)m_pWndList;
	ASSERT_VALID (this);
	ASSERT_VALID (pDC);
	ASSERT_VALID (pWndList);

	if (HasValueField ())
	{
		return;
	}

	// Draw group row:
	COLORREF clrTextOld = pDC->GetTextColor ();//(COLORREF)-1;

	COLORREF clrText = (COLORREF)-1;
	if (IsSelected ())
	{
		CRect rectFill = rect;
		rectFill.top++;
		if (IsGroup ())
		{
			rectFill.DeflateRect (0, 0, 0, 1);
		}

		if (pWndList->m_ColorData.m_GroupColors.m_clrText != (COLORREF)-1)
		{
			clrText = pWndList->m_ColorData.m_GroupColors.m_clrText;
		}
		else
		{
			clrText = CBCGPVisualManager::GetInstance ()->OnFillReportCtrlRowBackground (
				pWndList, pDC, rectFill, IsSelected (), IsGroup ());
		}
	}
	else
	{
		if (IsGroup () && !HasValueField ())
		{
			if (pWndList->m_ColorData.m_GroupColors.m_clrText != (COLORREF)-1)
			{
				clrText = pWndList->m_ColorData.m_GroupColors.m_clrText;
			}
			else
			{
				clrText = CBCGPVisualManager::GetInstance ()->OnFillReportCtrlRowBackground (
					pWndList, pDC, rect, IsSelected (), IsGroup () && !HasValueField ());
			}
		}
		else
		{
			clrText = CBCGPVisualManager::GetInstance ()->OnFillReportCtrlRowBackground (
				pWndList, pDC, rect, IsSelected (), IsGroup () && !HasValueField ());
		}
	}

	rect.DeflateRect (TEXT_MARGIN, 0);
	if (IsGroup ())
	{
		rect.DeflateRect (0, (pWndList->m_nLargeRowHeight - pWndList->m_nRowHeight) / 2, 0, 0);
	}

	if (clrText != (COLORREF)-1)
	{
		pDC->SetTextColor (clrText);
	}

    CPoint ptIcon;
    ptIcon.x = rect.left+TEXT_MARGIN;
    ptIcon.y = rect.top+(rect.Height()-16)/2;
    if(IsActiveRow())
    {
        DrawIcon(pDC,ptIcon.x,ptIcon.y,IDB_ACTIVE);
    }
    else
    {
        DrawIcon(pDC,ptIcon.x,ptIcon.y,IDB_INACTIVE);
    }

    CRect rect_text;
    rect_text=rect;
    rect_text.left += ICON_W + TEXT_MARGIN+ TEXT_MARGIN;

	pDC->DrawText (m_strName, rect_text, 
		DT_LEFT | DT_SINGLELINE | DT_VCENTER | DT_NOPREFIX | DT_END_ELLIPSIS);

	if (clrText != (COLORREF)-1)
	{
		pDC->SetTextColor (clrTextOld);
	}

	m_bNameIsTrancated = pDC->GetTextExtent (m_strName).cx > rect.Width ();

}



/*******************************************
    Function Name :	 
    Create by     :	  Qiu Simon
    Input         :   
    Output        :   
    Description   :   
    Date          :   12/23/2010 5:16:07 PM
********************************************/
void CGroupRow::ExpandActive()
{
    if(IsActiveRow())
    {
        m_bExpanded = TRUE;
    }
}

CString CGroupRow::GetMainID()
{
    CReportDemoView* pwnd = (CReportDemoView*)m_pWndList->GetParent();
    return pwnd->m_pParent->m_strID;
}

BOOL CGroupRow::IsActiveRow()
{
    if(m_strName == _T("»îÆÚ"))
    {
        return TRUE;
    }
    CSubCountSet* pset = theApp.GetSubCountSet();
    if(pset->Find(GetMainID(),m_strName))
    {
        TRACE("\n%s,%d",m_strName,pset->m_bExist);
        return pset->m_bExist;
    }
    return FALSE;
}

void CGroupRow::CollapseInactive()
{
    if(!IsActiveRow())
    {
       	m_bExpanded = FALSE;
    }
}


/*******************************************
    Function Name :	 
    Create by     :	  Qiu Simon
    Input         :   
    Output        :   
    Description   :   
    Date          :   12/24/2010 10:21:02 AM
********************************************/
void CGroupRow::SetExpandValueWithNoRedraw(BOOL bExpand)
{
    m_bExpanded = bExpand;
}

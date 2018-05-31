// MailReportCtrl.cpp : implementation file
//

#include "stdafx.h"
//#include "..\SmallHorse.h"
#include "MailReportCtrl.h"
#include "reportframe.h"
#include "GroupRow.h"
//#include "CompareDetailCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMailReportCtrl
IMPLEMENT_DYNCREATE(CMailReportCtrl, CBCGPReportCtrl)
//IMPLEMENT_DYNAMIC(CMailReportCtrl, CBCGPReportCtrl)
CMailReportCtrl::CMailReportCtrl()
{
	m_pCbFun = NULL;
    m_bEditOnline = FALSE;
    m_pDetailCtrl = NULL;
}

CMailReportCtrl::~CMailReportCtrl()
{
}


BEGIN_MESSAGE_MAP(CMailReportCtrl, CBCGPReportCtrl)
	//{{AFX_MSG_MAP(CMailReportCtrl)
	ON_WM_LBUTTONDBLCLK()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


BOOL IsStringsSimmilarTo (CString str1, CString str2)
{
	int nIndex = -1;

	//---------------------------
	// Remove all "Re: ", "FWD: "
	//---------------------------
	while ((nIndex = str1.Find (':')) >= 0)
	{
		str1 = str1.Mid (nIndex + 1);
	}

	str1.TrimLeft ();
	str1.TrimRight ();

	while ((nIndex = str2.Find (':')) >= 0)
	{
		str2 = str2.Mid (nIndex + 1);
	}

	str2.TrimLeft ();
	str2.TrimRight ();

	return str1.CompareNoCase (str2) == 0;
}
#if 0
BOOL DoCompare (const CBCGPGridRow* pRow1, const CBCGPGridRow* pRow2, int iColumn)
{
	switch (iColumn)
	{
	case 7:	// Created
	case 8:	// Received
		{
			COleDateTime date1 = (DATE) pRow1->GetItem (iColumn)->GetValue ();
			COleDateTime date2 = (DATE) pRow2->GetItem (iColumn)->GetValue ();

			return date1.GetYear () == date2.GetYear () &&
				date1.GetMonth () == date2.GetMonth () &&
				date1.GetDay () == date2.GetDay ();
		}
	}

	return FALSE;
}
#endif
/////////////////////////////////////////////////////////////////////////////
// CMailReportCtrl message handlers

int CMailReportCtrl::CompareGroup (const CBCGPGridRow* pRow1, const CBCGPGridRow* pRow2, int iColumn)
{
	ASSERT_VALID (this);
	ASSERT_VALID (pRow1);
	ASSERT_VALID (pRow2);
#if 0
	if (DoCompare (pRow1, pRow2, iColumn))
	{
		return 0;
	}
#endif
	return CBCGPReportCtrl::CompareGroup (pRow1, pRow2, iColumn);
}

CString CMailReportCtrl::GetGroupName (int iColumn, CBCGPGridItem* pItem)
{
	ASSERT_VALID (this);
	ASSERT_VALID (pItem);


    CString strValue = pItem->FormatItem ();
    if(strValue == _T(""))
    {
        strValue = _T("»îÆÚ");
    }
    else
    {

    }
    return strValue;
}

void CMailReportCtrl::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	CBCGPGridRow* pRow = HitTest(point);
	if(pRow == NULL)
	{
	}
	else
	{
		if(m_pCbFun != NULL)
		{
			(*m_pCbFun)(this,pRow);
		}
	}

	
	
	CBCGPReportCtrl::OnLButtonDblClk(nFlags, point);
}

void CMailReportCtrl::SetDbClkCBFunc(CB_FUNC_ONDBCLK_ITEM pfun)
{
	m_pCbFun = pfun;
}

void CMailReportCtrl::Test()
{
	for (POSITION pos = m_lstAutoGroups.GetHeadPosition (); pos != NULL;)
	{
		CGroupRow* pSelRange = (CGroupRow*)m_lstAutoGroups.GetNext (pos);
        pSelRange->ExpandActive();
	}
#if 0
	for (POSITION pos = m_lstSel.GetHeadPosition (); pos != NULL;)
	{
		CBCGPGridRange* pSelRange = m_lstSel.GetNext (pos);
		ASSERT (pSelRange != NULL);
		
		for(int ii= pSelRange->m_nTop;ii<=pSelRange->m_nBottom;ii++)
		{
			CBCGPGridRow* prow = GetRow(ii);
			CBCGPGridItem* pitem =  prow->GetItem(0);
			TRACE((char*)(_bstr_t)pitem->GetValue());
			TRACE("\n");
		}
	}
#endif	
	
}


/*******************************************
    Function Name : 
    author        : Qiu Guohua
    Date          : 2009-5-18 21:55:01
    Description   : 
    Return type  : 
    Argument      : 
********************************************/
int CMailReportCtrl::GetSelectedRows(CDWordArray &rowArray)
{
	int nCount = 0;
	for (POSITION pos = m_lstSel.GetHeadPosition (); pos != NULL;)
	{
		CBCGPGridRange* pSelRange = m_lstSel.GetNext (pos);
		ASSERT (pSelRange != NULL);
		
		for(int ii= pSelRange->m_nTop;ii<=pSelRange->m_nBottom;ii++)
		{
			CBCGPGridRow* prow = GetRow(ii);
			if(prow != NULL)
			{
				rowArray.Add(prow->GetData());
				nCount++;
			}
			TRACE(_T("\n"));
		}
	}
	return nCount;
}


/*******************************************
    Function Name : 
    author        : Qiu Guohua
    Date          : 2009-5-19 20:43:03
    Description   : 
    Return type  : 
    Argument      : 
********************************************/
CBCGPGridRow* CMailReportCtrl::GetFirstSelectedRow()
{
	CBCGPGridRow* prow = NULL;
	CBCGPGridRange* pSelRange = m_lstSel.GetHead();
	if(pSelRange != NULL)
	{
		prow = GetRow( pSelRange->m_nTop);
	}
	return prow;
}


/*******************************************
    Function Name : 
    author        : Qiu Guohua
    Date          : 2009-5-30 22:22:17
    Description   : 
    Return type  : 
    Argument      : 
********************************************/
BOOL CMailReportCtrl::ToggleEditInPlace()
{
    m_bEditOnline = !m_bEditOnline;
    return m_bEditOnline;
}


/*******************************************
    Function Name :	 
    Create by     :	  Qiu Simon
    Input         :   
    Output        :   
    Description   :   
    Date          :   2010-2-23 15:30:51
********************************************/
void CMailReportCtrl::TrackToolTip(CPoint point)
{
	if (m_nDraggedColumn >= 0 || m_bTracking || m_bSelecting)
	{
		return;
	}

#ifndef _BCGPGRID_STANDALONE
	if (CBCGPPopupMenu::GetActiveMenu () != NULL)
	{
		return;
	}
#endif

	CPoint ptScreen = point;
	ClientToScreen (&ptScreen);

	CRect rectTT;
	m_ToolTip.GetLastRect (rectTT);

	if (rectTT.PtInRect (ptScreen) && m_ToolTip.IsWindowVisible ())
	{
		return;
	}

	if (::GetCapture () == GetSafeHwnd ())
	{
		ReleaseCapture ();
	}

	if (!m_bShowInPlaceToolTip)
	{
		m_ToolTip.Deactivate ();
		return;
	}

	if (m_rectColumnChooser.PtInRect (ptScreen))
	{
		m_ToolTip.Deactivate ();
		return;
	}

	CBCGPGridRow::ClickArea clickArea;
	CBCGPGridItemID id;
	CBCGPGridItem* pHitItem = NULL;
	CBCGPGridRow* pHitRow = HitTest (point, id, pHitItem, &clickArea);

	if (pHitRow == NULL)
	{
		m_ToolTip.Deactivate ();
		return;
	}

	ASSERT_VALID (pHitRow);

	CString strTipText;
	CRect rectToolTip;
	rectToolTip.SetRectEmpty ();

//    TRACE("clickArea is %d\n",clickArea);

	if (clickArea == CBCGPGridRow::ClickName)
	{
    //here are my codes.
    CWnd* pwnd = GetParent();
    pwnd = pwnd->GetParent();
    if(pwnd->IsKindOf(RUNTIME_CLASS (CReportFrame)))
    {
      CReportFrame* pfrm = (CReportFrame*)pwnd;
      strTipText = ((CGroupRow*)pHitRow)->GetTipString(pfrm->m_strID);
    }

    
//    TRACE("CBCGPGridRow::ClickName\n");
//		strTipText = pHitRow->GetNameTooltip ();
		rectToolTip = ((CGroupRow*)pHitRow)->GetTipRect ();
	}
	else if (clickArea == CBCGPGridRow::ClickValue)
	{
//    TRACE("CBCGPGridRow::ClickValue\n");
		if (pHitRow->IsGroup ())
		{
//      TRACE("IsGroup\n");
			strTipText = pHitRow->GetValueTooltip ();
			rectToolTip = pHitRow->GetRect ();
		}
		else
		{
//      TRACE("NOT IsGroup\n");
			if (pHitItem != NULL)
			{
//        TRACE("pHitItem != NULL\n");
				ASSERT_VALID (pHitItem);
				if (pHitItem->IsInPlaceEditing ())
				{
					return;
				}

				strTipText = pHitItem->GetValueTooltip ();
				rectToolTip = pHitItem->GetRect ();
			}
		}
	}
	
	if (!strTipText.IsEmpty ())
	{
		ClientToScreen (&rectToolTip);
		
		if (rectTT.TopLeft () == rectToolTip.TopLeft ())
		{
			// Tooltip on the same place, don't show it to prevent flashing
			return;
		}
		
		m_ToolTip.SetTextMargin (TEXT_MARGIN);
		m_ToolTip.SetFont (GetFont ());

		m_ToolTip.Track (rectToolTip, strTipText);
		SetCapture ();
	}
	else
	{
		m_ToolTip.Deactivate ();
	}
}


/*******************************************
    Function Name :	 
    Create by     :	  Qiu Simon
    Input         :   
    Output        :   
    Description   :   
    Date          :   2010-2-23 16:38:00
********************************************/
CBCGPGridRow* CMailReportCtrl::CreateRow(CString strName)
{
  return (CBCGPGridRow*)new CGroupRow(strName);
}





/*******************************************
    Function Name :	 
    Create by     :	  Qiu Simon
    Input         :   
    Output        :   
    Description   :   
    Date          :   2010-3-2 17:18:32
********************************************/
void CMailReportCtrl::SetRowBackColor(CBCGPGridRow* pRow, COLORREF crBkColor)
{
  int nCount = pRow->GetItemCount();
  for(int i = 0;i<nCount;i++)
  {
     pRow->GetItem(i)->SetBackgroundColor(crBkColor,FALSE);
  }
}


/*******************************************
    Function Name : 
    author        : Qiu Guohua
    Date          : 2010-12-23 20:19:44
    Description   : 
    Return type   : 
    Argument      : 
********************************************/
void CMailReportCtrl::ExpandAllActiveGroup()
{
    for (POSITION pos = m_lstAutoGroups.GetHeadPosition (); pos != NULL;)
    {
        CGroupRow* pGroup = (CGroupRow*)m_lstAutoGroups.GetNext (pos);
        pGroup->ExpandActive();
    }
    AdjustLayout();
}


/*******************************************
    Function Name : 
    author        : Qiu Guohua
    Date          : 2010-12-23 21:19:35
    Description   : 
    Return type   : 
    Argument      : 
********************************************/
void CMailReportCtrl::ExpandAllGroup()
{
    for (POSITION pos = m_lstAutoGroups.GetHeadPosition (); pos != NULL;)
    {
        CGroupRow* pGroup = (CGroupRow*)m_lstAutoGroups.GetNext (pos);
        pGroup->SetExpandValueWithNoRedraw(TRUE);
    }
    AdjustLayout();
}


/*******************************************
    Function Name : 
    author        : Qiu Guohua
    Date          : 2010-12-23 21:19:39
    Description   : 
    Return type   : 
    Argument      : 
********************************************/
void CMailReportCtrl::CollapseAllGroup()
{
    for (POSITION pos = m_lstAutoGroups.GetHeadPosition (); pos != NULL;)
    {
        CGroupRow* pGroup = (CGroupRow*)m_lstAutoGroups.GetNext (pos);
        pGroup->SetExpandValueWithNoRedraw(FALSE);
    }
    AdjustLayout();
}


/*******************************************
    Function Name : 
    author        : Qiu Guohua
    Date          : 2010-12-23 21:19:41
    Description   : 
    Return type   : 
    Argument      : 
********************************************/
void CMailReportCtrl::CollapseAllInactiveGroup()
{
    for (POSITION pos = m_lstAutoGroups.GetHeadPosition (); pos != NULL;)
    {
        CGroupRow* pGroup = (CGroupRow*)m_lstAutoGroups.GetNext (pos);
        pGroup->CollapseInactive();
    }
    AdjustLayout();
}

CBCGPGridRow* CMailReportCtrl::CreateRow(int nColumns)
{
    return CBCGPReportCtrl::CreateRow(nColumns);
}


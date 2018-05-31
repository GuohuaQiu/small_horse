// QiuHeadCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "..\SmallHorse.h"
#include "QiuHeadCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CQiuHeadCtrl

CQiuHeadCtrl::CQiuHeadCtrl()
{
}

CQiuHeadCtrl::~CQiuHeadCtrl()
{
}

#define ID_MENU_ADD_TO_COMMENT         34000
#define ID_MENU_SET_FIELD_NAME_START   34001
#define ID_MENU_SET_FIELD_NAME_END     34010
#define ID_MENU_SET_AS_BLANK           34011



BEGIN_MESSAGE_MAP(CQiuHeadCtrl, CHeaderCtrl)
	//{{AFX_MSG_MAP(CQiuHeadCtrl)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_COMMAND_RANGE(ID_MENU_ADD_TO_COMMENT, ID_MENU_SET_FIELD_NAME_END,OnMenuitem)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CQiuHeadCtrl message handlers
int g_a = 3;

void CQiuHeadCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CMenu mu;
	mu.CreatePopupMenu( );
	for(int i = 0;i<m_nFieldCount;i++)
	{
		mu.AppendMenu(MF_STRING,ID_MENU_SET_FIELD_NAME_START+i,m_pFieldNames+i*FIELD_NAME_LEN);
	}
	mu.AppendMenu(MF_STRING,ID_MENU_ADD_TO_COMMENT,_T("添加到备注"));
	mu.AppendMenu(MF_STRING,ID_MENU_SET_AS_BLANK,_T(">>>删除"));
//	mu.setwindow
	CMenu* pMenu = &mu;
	int n = GetItemCount();
	CRect rect;
	for(int i = 0;i<n;i++)
	{
		GetItemRect(i,&rect);
		TRACE("%d,|%d %d|\n",i,rect.left,rect.right);
		if(point.x>(rect.left+g_a)&&point.x<(rect.right-g_a)&&point.y>rect.top&&point.y<rect.bottom)
		{
			m_nLastSelectedItem = i;
			ClientToScreen(&rect);
			pMenu->TrackPopupMenu(TPM_LEFTALIGN,rect.left,rect.top,this,0);
//			CHeaderCtrl::OnLButtonUp(nFlags, point);
			return;
		}
	}
	CHeaderCtrl::OnLButtonDown(nFlags, point);
}

void CQiuHeadCtrl::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	g_a++;
	TRACE("G_A = %d\n",g_a);
	CHeaderCtrl::OnLButtonDblClk(nFlags, point);
}

void CQiuHeadCtrl::OnMenuitem(UINT nID) 
{
	if(nID<ID_MENU_ADD_TO_COMMENT)	
		return;
	HDITEM hitem;
	memset(&hitem,0,sizeof(hitem));
	hitem.mask = HDI_TEXT;
	if(nID==ID_MENU_ADD_TO_COMMENT)
	{
		TCHAR  lpBuffer[256];
		
		hitem.pszText = lpBuffer;
		hitem.cchTextMax = 256;
		GetItem(m_nLastSelectedItem,&hitem);
		int nCommentIndex = GetCommentIndex();
		if(nCommentIndex == m_nLastSelectedItem)
		{
			nCommentIndex = GetCommentIndex(nCommentIndex + 1);
		}
		if(nCommentIndex == -1)
		{
			AfxMessageBox("没有\"备注\"这一项,请设置!");
			return;
		}
		CListCtrl* pListCtrl = (CListCtrl*)GetParent();
		CString strOldTitle = GetItemString(m_nLastSelectedItem);
		BOOL bAddTitle = TRUE;
		if(strOldTitle == m_pFieldNames+(m_nFieldCount-1)*FIELD_NAME_LEN)
		{
			bAddTitle = FALSE;
		}
		int nItmCount = pListCtrl->GetItemCount();
		CString strNewTxt;
		for(int i = 0;i<nItmCount;i++)
		{
			CString strTxt = pListCtrl->GetItemText(i,nCommentIndex);
			CString strOldTxt = pListCtrl->GetItemText(i,m_nLastSelectedItem);
			if(bAddTitle)
			{
				strNewTxt.Format("%s;%s:%s",strTxt,strOldTitle,strOldTxt);
			}
			else
			{
				strNewTxt.Format("%s;%s",strTxt,strOldTxt);
			}
			pListCtrl->SetItemText(i,nCommentIndex,strNewTxt);
		}
		pListCtrl->DeleteColumn(m_nLastSelectedItem);
		m_nLastSelectedItem = -1;
		return;
	}
	hitem.pszText = m_pFieldNames + (nID - ID_MENU_SET_FIELD_NAME_START)*FIELD_NAME_LEN ;
	SetItem(m_nLastSelectedItem,&hitem);
}

int CQiuHeadCtrl::GetCommentIndex(int nFrom)
{
	int nCount = GetItemCount();
	CString strItem;
	for(int i = nFrom;i < nCount;i++)
	{
		strItem = GetItemString(i);
		if(strItem == m_pFieldNames+(m_nFieldCount-1)*FIELD_NAME_LEN)
		{
			return i;
		}
	}
    return -1;
}

CString CQiuHeadCtrl::GetItemString(int nIndex)
{
	HDITEM hitem;
	memset(&hitem,0,sizeof(hitem));
	hitem.mask = HDI_TEXT;
	TCHAR  lpBuffer[256]={0};
	hitem.pszText = lpBuffer;
	hitem.cchTextMax = 256;
	GetItem(nIndex,&hitem);
	CString strRtn(lpBuffer);
	return strRtn;
}




BOOL CQiuHeadCtrl::FindType(int nTypeArry[],int nAttrArry[])
{
	int nHeadCount = GetItemCount();
	memset(nTypeArry,-1,m_nFieldCount*sizeof(nTypeArry[0]));
	for(int j = 0;j<nHeadCount;j++)
	{
		CString strItem = GetItemString(j);
		for(int i = 0 ; i < m_nFieldCount;i++)
		{
			if(strItem == m_pFieldNames+i*FIELD_NAME_LEN)
			{
				if(nTypeArry[i] == -1)
				{
					nTypeArry[i] = j;
					break;
				}
				else
				{
					CString strTip;
					strTip.Format(_T("%s 重复了!"),strItem);
					AfxMessageBox(strTip);
					return FALSE;
				}
			}
		}
	}


	BOOL bRet = TRUE;
	CString strTip(_T("找不到 "));
//  find all must set fields.
	for(int i = 0 ; i < m_nFieldCount;i++)
	{
		if((nAttrArry[i] == 1) && (nTypeArry[i]==-1))
		{
			strTip += _T("\"");
			strTip += m_pFieldNames+i*FIELD_NAME_LEN;
			strTip += _T("\"");
			bRet = FALSE;
		}
	}
	
	if(bRet)
	{// All must field found.
		strTip = _T("");

	}
	else
	{
		strTip += _T("\n");
	}
//  find all at least one  fields.
	for(int i = 0 ; i < m_nFieldCount;i++)
	{
		if((nAttrArry[i] > 1) && (nTypeArry[i]==-1))
		{
			//find another one.
			for(int j = i+1;j<m_nFieldCount;j++)
			{
				if(nAttrArry[j] == nAttrArry[i])
				{
					if(nTypeArry[j]==-1)
					{
						strTip += _T("\"");
						strTip += m_pFieldNames+i*FIELD_NAME_LEN;
						strTip += _T("\" 和 ");
						strTip += _T("\"");
						strTip += m_pFieldNames+j*FIELD_NAME_LEN;
						strTip += _T("\" 至少应有一个");
						bRet = FALSE;
					}
				}
			}
		}
	}
	if(!bRet)
	{
		AfxMessageBox(strTip);
	}
	return bRet;
}

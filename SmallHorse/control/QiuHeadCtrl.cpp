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
	m_nFieldCount = 0;
	m_pFieldNames = NULL;
	m_pIndex = NULL;
	m_pFieldAttr = NULL;


	m_TotalColumnCount = 0;
	m_pAddToComments = NULL;
}

CQiuHeadCtrl::~CQiuHeadCtrl()
{
	if(m_pAddToComments)
	{
		delete [] m_pAddToComments;
	}
	if(m_pIndex)
	{
		delete [] m_pIndex;
	}
}

#define ID_MENU_ADD_TO_COMMENT         34000
#define ID_MENU_SET_FIELD_NAME_START   34001
#define ID_MENU_SET_FIELD_NAME_END     34010
#define ID_MENU_SET_AS_BLANK           34011

//extern int g_comment_string_index_in_header;

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
	if(m_TotalColumnCount == 0)
	{
		m_TotalColumnCount = GetItemCount();
		m_pAddToComments = new int[m_TotalColumnCount];
		for(int i=0;i<m_TotalColumnCount;i++)
		{
			m_pAddToComments[i] = 0;
		}
	}

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
		AddToComments(m_nLastSelectedItem);
		m_nLastSelectedItem = -1;
		return;
	}
	SetColumeAs(m_nLastSelectedItem,nID - ID_MENU_SET_FIELD_NAME_START);
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


void CQiuHeadCtrl::SetColumnName(int count, TCHAR* pNames,int nAttrArry[])
{
	m_nFieldCount = count;
	m_pFieldNames = pNames;
	m_pFieldAttr = nAttrArry;
	m_pIndex = new int[count];
	for(int i=0;i<count;i++)
	{
		m_pIndex[i] = -1;
	}

}

void CQiuHeadCtrl::SetColumeAs(int col_index,int name_index)
{
    if(m_pIndex[name_index] == col_index)
    {
        return;
    }
    if(m_pIndex[name_index] != -1)
    {
        for(int i = 0;i<m_nFieldCount;i++)
        {
            if(m_pIndex[i] == col_index){
                m_pIndex[i] = -1;
            }
        }
        //TOO ALL ONLY ONECE ITEM, SHOULD CLEAR
        ClearName(m_pIndex[name_index]);
    }
    m_pAddToComments[col_index] = 0;

    m_pIndex[name_index] = col_index;
    UpdateName(col_index);
}
void CQiuHeadCtrl::UpdateName(int col_index)
{
	for(int i=0;i<m_nFieldCount;i++)
	{
		if(m_pIndex[i] == col_index)
		{
			HDITEM hitem;
			memset(&hitem,0,sizeof(hitem));
			hitem.mask = HDI_TEXT;
			hitem.pszText = m_pFieldNames + i*FIELD_NAME_LEN ;
			SetItem(col_index,&hitem);
			return;
		}
	}
}

char STRING_NULL[4] = "_";
char STRING_ADDTOCOMMENT[] = "ToComment";

void CQiuHeadCtrl::ClearName(int col_index)
{
	HDITEM hitem;
	memset(&hitem,0,sizeof(hitem));
	hitem.mask = HDI_TEXT;
	hitem.pszText = STRING_NULL ;
	SetItem(col_index,&hitem);
}
void CQiuHeadCtrl::AddToComments(int col_index)
{
	HDITEM hitem;
	memset(&hitem,0,sizeof(hitem));
	hitem.mask = HDI_TEXT;
	hitem.pszText = STRING_ADDTOCOMMENT;
	SetItem(col_index,&hitem);

	for(int i=0;i<m_nFieldCount;i++)
	{
		if(m_pIndex[i] == col_index)
		{
			m_pIndex[i] = -1;
		}
	}
	m_pAddToComments[col_index] = 1;
}

BOOL CQiuHeadCtrl::ValidateNames()
{
	//  find all at least one  fields.
	BOOL hasOne = FALSE;
	BOOL MustHas = TRUE;
	CString strTip(_T(""));
	CString strMust(_T(""));
	for(int i = 0 ; i < m_nFieldCount;i++)
	{
		if((m_pFieldAttr[i] > 1))
		{
			if(m_pIndex[i]!=-1)
			{
				hasOne = TRUE;
			}
			strTip += m_pFieldNames+i*FIELD_NAME_LEN;
			strTip += _T(" ");
		}
		else if(m_pFieldAttr[i] == 1)
		{
			if(m_pIndex[i]==-1)
			{
				MustHas = FALSE;
				strMust += m_pFieldNames+i*FIELD_NAME_LEN;
				strTip += _T(" ");
			}
		}
	}
	CString strInfo;
	if(!hasOne)
	{
		strTip += _T("\" 至少应有一个\n");
		strInfo += strTip;
	}
	if(!MustHas)
	{
		strMust += _T("\" 必须有\n");
		strInfo += strMust;
	}
	if(!hasOne||!MustHas)
	{
		AfxMessageBox(strInfo );
		return FALSE;
	}
	return TRUE;
}

int* CQiuHeadCtrl::GetNameIndex()
{
	return m_pIndex;
}

int CQiuHeadCtrl::GetAddToComments(int** ppATC)
{
	*ppATC = m_pAddToComments;
	return m_TotalColumnCount;
}

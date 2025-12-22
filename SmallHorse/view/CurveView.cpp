// CurveView.cpp : implementation file
//

#include "stdafx.h"
#include "..\SmallHorse.h"
#include "CurveView.h"
#include "BankBookDoc.h"
#include "math.h"
#include "reportframe.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define LEFTBEGIN 50
#define BOTTOMBEGIN 280
/////////////////////////////////////////////////////////////////////////////
// CCurveView
//int linearray[100];
//int arraylength=0;

IMPLEMENT_DYNCREATE(CCurveView, CScrollView)

CCurveView::CCurveView()
{
	m_beginyear=1999;
	bDraw=TRUE;
	m_daysum=0;//tspan.GetDays();
//	m_daysum=Get1999Days(COleDateTime::GetCurrentTime(),TRUE);//tspan.GetDays();
	SetDisSpend();
	SetDisBalance();
	SetDisSave();
	m_bdown=FALSE;
	m_pArea = NULL;
	m_nAreaCount = 0;
	m_pLastArea = NULL;
	m_pParent = NULL;

}

CCurveView::~CCurveView()
{
}


BEGIN_MESSAGE_MAP(CCurveView, CScrollView)
	//{{AFX_MSG_MAP(CCurveView)
	ON_WM_ERASEBKGND()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCurveView drawing

void CCurveView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();
	CClientDC dc(this);

	CSize sizeTotal;
	// TODO: calculate the total size of this view
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
}

void CCurveView::OnDraw(CDC* pDC)
{
    CListSet listSet;


    listSet.m_strFilter = m_pParent->m_strFilter;
    listSet.m_strSort = m_pParent->m_strSort;
    listSet.OpenEx();

	int mode=pDC->SetBkMode(TRANSPARENT);

	GetMaxValue();
	//画坐标系
	SetBeginYear();
	DrawCoordinate(pDC);
	if(bDraw)
	{
		if(m_bDisBalance)
			DrawCurve(pDC);
		if(m_bDisSave)
			DrawAllSaveCurve(pDC);
		if(m_bDisSpend)
			DrawAllExpenseCurve(pDC);
	}
	CString str=_T("金额曲线图");
	DrawName(pDC,m_curvename);
    DrawInformation(pDC,&(m_pParent->mInformation));
	CSize size(m_daysum+LEFTBEGIN+50,BOTTOMBEGIN+40);
	SetScrollSizes(MM_TEXT,size);
	pDC->SetBkMode(mode);

}

/////////////////////////////////////////////////////////////////////////////
// CCurveView diagnostics

#ifdef _DEBUG
void CCurveView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CCurveView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCurveView message handlers

BOOL CCurveView::CreateView(CWnd* pParent, CCreateContext* pContext)
{
    CRect rect(0,0,300,300);

    if (!Create(NULL, NULL, AFX_WS_DEFAULT_VIEW,
        rect, pParent, AFX_IDW_PANE_FIRST, pContext))
    {
        TRACE0("Warning: couldn't create CMyFormView!\n");
        return FALSE;
    }

    return TRUE;
}

void CCurveView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
}

void CCurveView::DrawCoordinate(CDC *pDC)
{

	int x_regionright=LEFTBEGIN+m_daysum;//有效曲线区域右坐标x
	int x_array=x_regionright+20;
	CPen pengran;
	pengran.CreatePen(PS_SOLID,1,RGB(128,128,128));
	CPen* oldpen=pDC->SelectObject(&pengran);
	pDC->MoveTo(LEFTBEGIN,10);
	pDC->LineTo(LEFTBEGIN,2*BOTTOMBEGIN);
	pDC->MoveTo(LEFTBEGIN,BOTTOMBEGIN);

	pDC->LineTo(x_array,BOTTOMBEGIN);
	//画箭头
	pDC->LineTo(x_array-7,BOTTOMBEGIN-2);
	pDC->LineTo(x_array-7,BOTTOMBEGIN+2);
	pDC->LineTo(x_array,BOTTOMBEGIN);/**/
	//画网格
	CPen pendot;
	pendot.CreatePen(PS_DOT   ,1,RGB(192,192,192));
	pDC->SelectObject(&pendot);
	for(int c=1;c<5;c++)
	{
		pDC->MoveTo(LEFTBEGIN,BOTTOMBEGIN-c*50);
		pDC->LineTo(x_regionright,BOTTOMBEGIN-c*50);
	}
	pDC->SelectObject(&pengran);
	//下面是纵刻度
	CFont fontverscale,fonthorscale,fontverscale1,fonthorscale1,*oldfont;
	if(!fontverscale.CreateFont(14,NULL,0,0,600,FALSE,FALSE,0,0,OUT_CHARACTER_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY   ,FF_DONTCARE   ,"Arial"))
		TRACE(_T("MAKE FONT VERSCALE ERROR"));
	oldfont=pDC->SelectObject(&fontverscale);
	COLORREF rgb=pDC->SetTextColor(RGB(128,0,128));
	for(int c=0;c<6;c++)
	{
		pDC->MoveTo(LEFTBEGIN-5,BOTTOMBEGIN-c*50);
		pDC->LineTo(LEFTBEGIN,BOTTOMBEGIN-c*50);
		CString strc;
		strc.Format(_T("%d"),c*50*m_denominator);
		pDC->TextOut(5,BOTTOMBEGIN-c*50-10,strc);
    if(c>0)
    {
		  pDC->MoveTo(LEFTBEGIN-5,BOTTOMBEGIN+c*50);
		  pDC->LineTo(LEFTBEGIN,BOTTOMBEGIN+c*50);
		  CString strc;
		  strc.Format(_T("-%d"),c*50*m_denominator);
		  pDC->TextOut(5,BOTTOMBEGIN+c*50-10,strc);
    }
	}
	fontverscale1.CreateFont(15,NULL,0,0,500,FALSE,FALSE,0,0,OUT_CHARACTER_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY   ,FF_DONTCARE   ,"Arial");
	pDC->SelectObject(&fontverscale1);
	pDC->TextOut(LEFTBEGIN+5,10,_T("（单位：元）"));
	//下面是横刻度
	fonthorscale.CreateFont(14,NULL,0,0,600,FALSE,FALSE,0,0,OUT_CHARACTER_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY   ,FF_DONTCARE   ,_T("Arial"));
	pDC->SelectObject(&fonthorscale);
	pDC->SetTextColor(RGB(0,0,200));
	COleDateTime tc=COleDateTime::GetCurrentTime();
	
	for(int d=m_beginyear;d<=tc.GetYear();d++)
	{
		COleDateTime timetemp(d,1,1,0,0,0);
		int days=Get1999Days(timetemp);
		DrawScale(pDC,LEFTBEGIN+days,BOTTOMBEGIN,15,d,16);
		for(int month=2;month<13;month++)
		{
			if(d==tc.GetYear()&&month>tc.GetMonth())
				break;

			COleDateTime timem(d,month,1,0,0,0);
			days=Get1999Days(timem);
			DrawScale(pDC,LEFTBEGIN+days,BOTTOMBEGIN,5,month,8);
		}
	}
	fonthorscale1.CreateFont(13,NULL,0,0,500,FALSE,FALSE,0,0,OUT_CHARACTER_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY   ,FF_DONTCARE   ,_T("Arial"));
	pDC->SelectObject(&fonthorscale1);

	pDC->TextOut(LEFTBEGIN+20,BOTTOMBEGIN+20,_T("年.月"));
	pDC->SelectObject(oldfont);
	pDC->SelectObject(oldpen);
	pDC->SetTextColor(rgb);
}


void CCurveView::DrawScale(CDC *pDC, int a, int b0, int b1, int number,int ahead, BOOL bV)
{
	pDC->MoveTo(a,b0);
	pDC->LineTo(a,b0+b1);
	CString stryear;
	stryear.Format(_T("%d"),number);
	pDC->TextOut(a-ahead,b0+b1,stryear);
	if(number>m_beginyear)
	{
		COLORREF oldcolor=pDC->SetTextColor(RGB(192,0,192));
		CFont* oldfont,fontlittle;
		fontlittle.CreateFont(12,NULL,0,0,400,FALSE,FALSE,0,0,OUT_CHARACTER_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY   ,FF_DONTCARE   ,_T("Arial"));
		oldfont=pDC->SelectObject(&fontlittle);
		for(int i=1;i<6;i++)
		{
			stryear.Format(_T("%d"),m_denominator*50*i);
			pDC->TextOut(a,BOTTOMBEGIN-i*50-5,stryear);
		}
		pDC->SetTextColor(oldcolor);
		pDC->SelectObject(oldfont);

	}

}

int CCurveView::Get1999Days(COleDateTime time,BOOL bLocal)
{
	if(bLocal)
    {
		time=COleDateTime::GetCurrentTime();
    }
	COleDateTime t1999(m_beginyear,1,1,0,0,0);
	COleDateTimeSpan tsp=time-t1999;
	return (int)tsp.GetDays();
}

void CCurveView::DrawCurve(CDC *pDC)
{
    CListSet listSet;
    listSet.m_strFilter = m_pParent->m_strFilter;
    listSet.m_strSort = m_pParent->m_strSort;
    listSet.OpenEx();
    ClearAreaInfo();

	CString strtrace;

	m_nAreaCount = listSet.GetRecordCount();
	if(m_nAreaCount > 0)
	{
		listSet.MoveFirst();
		m_pArea = new Area[m_nAreaCount];
		
		
		int prevalue=0;
		
		CPen penred,*oldpen;
		penred.CreatePen(PS_SOLID,2,RGB(0,0,255));
		oldpen=pDC->SelectObject(&penred);
		int nCount=0;
		int thisvalue=0;
		while(!listSet.IsEOF())
		{
			int thisdays=Get1999Days(listSet.m_day);
			m_pArea[nCount].x_start = LEFTBEGIN+thisdays;
			m_pArea[nCount].nID = listSet.m_arraynumber;
			
			thisvalue+=(int)listSet.GetAddorSubValue();//GetSumValue();
			listSet.MoveNext();
			
			if(nCount ==0)
			{
				pDC->MoveTo(LEFTBEGIN+thisdays,BOTTOMBEGIN);
				pDC->LineTo(LEFTBEGIN+thisdays,BOTTOMBEGIN-thisvalue/m_denominator);
			}
			else
			{
				pDC->LineTo(LEFTBEGIN+thisdays,BOTTOMBEGIN-prevalue/m_denominator);
				pDC->LineTo(LEFTBEGIN+thisdays,BOTTOMBEGIN-thisvalue/m_denominator);
			}
			prevalue=thisvalue;
			nCount++;
		}
		if(prevalue>=0.01)
		{
			pDC->LineTo(LEFTBEGIN+Get1999Days(COleDateTime::GetCurrentTime(),TRUE),BOTTOMBEGIN-prevalue/m_denominator);
		}
		
		pDC->SelectObject(oldpen);
	}
}

void CCurveView::GetMaxValue()
{
    CListSet listSet;
    listSet.m_strFilter = m_pParent->m_strFilter;
    listSet.m_strSort = m_pParent->m_strSort;
    listSet.OpenEx();
    if(listSet.GetRecordCount()>0)
	{
	int max=0;
  float positiveValue=0.0;
  float negativeValue=0.0;
  float tempValue;
	int a=0;
		listSet.MoveFirst();
		while(!listSet.IsEOF())
		{
      tempValue = listSet.GetAddorSubValue();
      if(tempValue>=0.0)
      {
        positiveValue += tempValue;
      }
      else
      {
        negativeValue += tempValue;
      }
//			a+=(int)pSet->GetAddorSubValue()>0 ? (int)pSet->GetAddorSubValue() :0 ;
//			if(a>max)
//				max=a;
			listSet.MoveNext();
      tempValue = max(positiveValue,-negativeValue);
		  m_denominator=CalDenoninator((int)(tempValue));
		}

	}
  else
  {
    m_denominator = 0;
  }
}

void CCurveView::SetBeginYear()
{
    CListSet listSet;
    listSet.m_strFilter = m_pParent->m_strFilter;
    listSet.m_strSort = m_pParent->m_strSort;
    listSet.OpenEx();

    if (bDraw)
    {
        if (listSet.GetRecordCount() > 0)
        {
            listSet.MoveFirst();
            if (listSet.m_day.m_status == COleDateTime::valid)
            {
                m_beginyear = listSet.m_day.GetYear();
            }

            m_daysum = Get1999Days(COleDateTime::GetCurrentTime(), TRUE);
        }
    }
}

void CCurveView::DrawName(CDC *pDC, CString strName)
{
	strName+=_T("  余额曲线图");
	CFont fonttitle,*oldfont;
	COLORREF oldfontcolor=pDC->SetTextColor(RGB(0,192,128));
	COLORREF oldbkcolor=pDC->SetBkColor(RGB(210,210,210));
	fonttitle.CreateFont(17,NULL,0,0,600,FALSE,FALSE,0,0,OUT_CHARACTER_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY   ,FF_DONTCARE   ,_T("Arial"));
	oldfont=pDC->SelectObject(&fonttitle);
	pDC->TextOut(LEFTBEGIN+100,10,strName);
	pDC->SelectObject(oldfont);
	pDC->SetTextColor(oldfontcolor);
	pDC->SetBkColor(oldbkcolor);
}

void CCurveView::DrawAllSaveCurve(CDC *pDC)
{
    CListSet listSet;
    listSet.m_strFilter = m_pParent->m_strFilter;
    listSet.m_strSort = m_pParent->m_strSort;
    listSet.OpenEx();
    CString strtrace;
	if(listSet.GetRecordCount()>0)
	{
		listSet.MoveFirst();
	}
	else
	{
		return;
			
	}
	int prevalue=0;
	
	CPen penred,*oldpen;
	penred.CreatePen(PS_SOLID   ,1,RGB(0,128,0));
	oldpen=pDC->SelectObject(&penred);
	int first=0;
	int thisvalue=0;
	int curvalue;
	while(!listSet.IsEOF())
	{
		curvalue=(int)listSet.GetAddorSubValue();
		if(curvalue>0)
		{
			thisvalue+=curvalue;//GetSumValue();
			int thisdays=Get1999Days(listSet.m_day);
			if(first++==0)
			{
				pDC->MoveTo(LEFTBEGIN+thisdays,BOTTOMBEGIN);
				pDC->LineTo(LEFTBEGIN+thisdays,BOTTOMBEGIN-thisvalue/m_denominator);
			}
			else
			{
				pDC->LineTo(LEFTBEGIN+thisdays,BOTTOMBEGIN-prevalue/m_denominator);
				pDC->LineTo(LEFTBEGIN+thisdays,BOTTOMBEGIN-thisvalue/m_denominator);
			}
			prevalue=thisvalue;
		}
		listSet.MoveNext();
	}
	if(prevalue>=0.01)
	{
		pDC->LineTo(LEFTBEGIN+Get1999Days(COleDateTime::GetCurrentTime(),TRUE),BOTTOMBEGIN-prevalue/m_denominator);
	}

	pDC->SelectObject(oldpen);

}

void CCurveView::DrawAllExpenseCurve(CDC *pDC)
{
    CListSet listSet;
    listSet.m_strFilter = m_pParent->m_strFilter;
    listSet.m_strSort = m_pParent->m_strSort;
    listSet.OpenEx();
    CString strtrace;
	if(listSet.GetRecordCount()>0)
	{
		listSet.MoveFirst();
	}
	else
	{
		return;
			
	}
	int prevalue=0;
	
	CPen penred,*oldpen;
	penred.CreatePen(PS_DASH   ,1,RGB(255,0,0));
	oldpen=pDC->SelectObject(&penred);
	int first=0;
	int thisvalue=0;
	int curvalue;
	while(!listSet.IsEOF())
	{
		curvalue=(int)listSet.GetAddorSubValue();
		if(curvalue<0)
		{
			thisvalue-=curvalue;//GetSumValue();
			int thisdays=Get1999Days(listSet.m_day);
			if(first++==0)
			{
				pDC->MoveTo(LEFTBEGIN+thisdays,BOTTOMBEGIN);
				pDC->LineTo(LEFTBEGIN+thisdays,BOTTOMBEGIN-thisvalue/m_denominator);
			}
			else
			{
				pDC->LineTo(LEFTBEGIN+thisdays,BOTTOMBEGIN-prevalue/m_denominator);
				pDC->LineTo(LEFTBEGIN+thisdays,BOTTOMBEGIN-thisvalue/m_denominator);
			}
			prevalue=thisvalue;
		}
		listSet.MoveNext();
	}
	if(prevalue>=0.01)
	{
		pDC->LineTo(LEFTBEGIN+Get1999Days(COleDateTime::GetCurrentTime(),TRUE),BOTTOMBEGIN-prevalue/m_denominator);
	}

	pDC->SelectObject(oldpen);

}

void CCurveView::SetDisSpend(BOOL b)
{
	m_bDisSpend=b;
}

void CCurveView::SetDisBalance(BOOL b)
{
	m_bDisBalance=b;
}

void CCurveView::SetDisSave(BOOL b)
{
	m_bDisSave=b;
}

BOOL CCurveView::GetDisSave()
{
	return m_bDisSave;

}

BOOL CCurveView::GetDisBalance()
{
	return m_bDisBalance;

}

BOOL CCurveView::GetDisSpend()
{
	return m_bDisSpend;
}

int CCurveView::CalDenoninator(int max)
{
	int half=max/2;
	int be=10000000;
	for(int i=7;i>1;i--)
	{
		int dom=half/be;
		if(dom>0)
		{
			if(half>5*be)   //*20
			{
				return (int)be/12.5;
			}
			if(half>2.5*be)// *10
			{
				return be/25;
			}
			if(half>1.25*be) // *5
			{
				return be/50;
			}
			return be/100;// *2.5
		}
		be/=10;
	}
	return 1;

}


BOOL CCurveView::OnEraseBkgnd(CDC* pDC) 
{

	return CScrollView::OnEraseBkgnd(pDC);
}

BOOL CCurveView::PreCreateWindow(CREATESTRUCT& cs) 
{
	CSmallHorseApp* pApp=(CSmallHorseApp*)AfxGetApp();
	HCURSOR handcur=pApp->LoadCursor(IDC_NULL);
	CBrush brush;
	brush.CreateSolidBrush(RGB(204,236,255));

	if (!CScrollView::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		handcur ,HBRUSH(brush), NULL);//NULL
	
	return TRUE;
}


void CCurveView::OnMouseMove(UINT nFlags, CPoint point) 
{
	if(!m_bdown)
	{
		CPoint ptscl = GetScrollPosition();
		LPAREA pArea = GetArea(point.x+ptscl.x,point.y+ptscl.y);
		if(m_pLastArea != pArea)
		{
			m_pLastArea = pArea;
			// Remove the old tooltip (if available)
			if (m_OwnToolTipCtrl.GetToolCount()>0)
			{
				m_OwnToolTipCtrl.DelTool(this);
				m_OwnToolTipCtrl.Activate(FALSE);
			}
			if(m_pLastArea)
			{
				static CString strInfo,strInfo2;
				theApp.GetRecordInfo(pArea->nID,strInfo);
				TOOLINFO ti = {0};
				ti.cbSize = sizeof(TOOLINFO);
				ti.uFlags = TTF_IDISHWND;    // Indicate that uId is handle to a control
				ti.uId = (UINT_PTR)m_hWnd;    // Handle to the control
				ti.hwnd = m_hWnd;            // Handle to window to receive the tooltip-messages
				ti.hinst = AfxGetInstanceHandle();
				ti.lpszText = (LPTSTR)(LPCTSTR)strInfo;
				theApp.GetBookInfo(pArea->nID,strInfo2);
				m_OwnToolTipCtrl.SetDescription(strInfo2);
				m_OwnToolTipCtrl.SendMessage(TTM_ADDTOOL, 0, (LPARAM) (LPTOOLINFO) &ti);
				m_OwnToolTipCtrl.Activate(TRUE);
			}
		}
	}
	else
	{
			if (m_OwnToolTipCtrl.GetToolCount()>0)
			{
				m_OwnToolTipCtrl.DelTool(this);
				m_OwnToolTipCtrl.Activate(FALSE);
			}
		CSize size=GetTotalSize();
		CSize movesize=point-m_beginpt;
		CPoint ptnow=GetDeviceScrollPosition();
		CPoint ptnew=ptnow-movesize;
		if(ptnew.x<0)
			ptnew.x=0;
		if(ptnew.y<0)
			ptnew.y=0;
		if(ptnew.x>size.cx)
			ptnew.x=size.cx;
		if(ptnew.y>size.cy)
			ptnew.y=size.cy;
		if(ptnew==m_beginpt)
			return;
		ScrollToPosition(ptnow-movesize);
		m_beginpt=point;
		
	}
	


	CScrollView::OnMouseMove(nFlags, point);
}

void CCurveView::OnLButtonDown(UINT nFlags, CPoint point) 
{
//	CSmartHorseApp* pApp=(CSmartHorseApp*)AfxGetApp();
//	HCURSOR handcur=pApp->LoadCursor(IDC_HAND);
//	SetCursor(handcur);
	m_beginpt=point;
	m_bdown=TRUE;
	CScrollView::OnLButtonDown(nFlags, point);
}

void CCurveView::OnLButtonUp(UINT nFlags, CPoint point) 
{
//	CSmartHorseApp* pApp=(CSmartHorseApp*)AfxGetApp();
//	HCURSOR handcur=pApp->LoadCursor(IDC_HANDPOINT);
//	SetCursor(handcur);
	m_bdown=FALSE;
	CScrollView::OnLButtonUp(nFlags, point);
}

int CCurveView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CScrollView::OnCreate(lpCreateStruct) == -1)
		return -1;
	m_pParent = (CReportFrame*)GetParent()->GetParent();
    VERIFY( m_OwnToolTipCtrl.Create(this, TTS_ALWAYSTIP) );
    m_OwnToolTipCtrl.Activate(TRUE);
	m_OwnToolTipCtrl.SetDelayTime(0);
#if 0	
	CBCGPTooltipManager::CreateToolTip (m_pToolTip, this,
		BCGP_TOOLTIP_TYPE_RIBBON);

	if (m_pToolTip->GetSafeHwnd () != NULL)
	{
		CRect rectDummy (0, 0, 500, 500);

		m_pToolTip->SetMaxTipWidth (640);

		m_pToolTip->AddTool (this, LPSTR_TEXTCALLBACK, &rectDummy, 1);
		m_pToolTip->SetDelayTime(3400,1000);
	}

#endif
	// TODO: Add your specialized creation code here
	
	return 0;
}

BOOL CCurveView::PreTranslateMessage(MSG* pMsg) 
{
   	switch (pMsg->message)
	{
	case WM_LBUTTONDOWN:
	case WM_RBUTTONDOWN:
	case WM_MBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_RBUTTONUP:
	case WM_MBUTTONUP:
	case WM_MOUSEMOVE:
		if (m_OwnToolTipCtrl.m_hWnd)
			m_OwnToolTipCtrl.RelayEvent(pMsg);
		break;
	}
	// TODO: Add your specialized code here and/or call the base class
	
	return CScrollView::PreTranslateMessage(pMsg);
}

void CCurveView::OnDestroy() 
{
	CScrollView::OnDestroy();
	ClearAreaInfo();	
}


void CCurveView::ClearAreaInfo()
{
	if(m_pArea)
	{
		delete m_pArea;
		m_pArea = NULL;
	}
	m_nAreaCount = 0;

}

LPAREA CCurveView::GetArea(int logx, int logy)
{
	if(m_nAreaCount == 0 || m_pArea == NULL)
	{
		return NULL;
	}
	for(int i = 0;i<m_nAreaCount;i++)
	{
		if(m_pArea[i].x_start>logx)
		{
			if(i == 0)
			{
				return NULL;
			}
			return &(m_pArea[i-1]);
		}
			
	}
	return &(m_pArea[m_nAreaCount-1]);
}


/*******************************************
    Function Name : 
    author        : Qiu Guohua
    Date          : 2010-12-17 21:55:16
    Description   : 
    Return type   : 
    Argument      : 
********************************************/
void CCurveView::DrawInformation(CDC *pDC, LPGEN_INFO pinfo)
{
    CString strInfo;
    strInfo.Format("收入：%11.2f,支出：%11.2f，合计：%11.2f",pinfo->mAmountEarn,pinfo->mAmountExpense,pinfo->mAmountTotal);
    CFont fonttitle,*oldfont;
    COLORREF oldfontcolor=pDC->SetTextColor(RGB(215,0,0));
    COLORREF oldbkcolor=pDC->SetBkColor(RGB(210,210,210));
    fonttitle.CreateFont(14,NULL,0,0,600,FALSE,FALSE,0,0,OUT_CHARACTER_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY   ,FF_DONTCARE   ,_T("Arial"));
    oldfont=pDC->SelectObject(&fonttitle);
    pDC->TextOut(LEFTBEGIN+500,10,strInfo);
    pDC->SelectObject(oldfont);
    pDC->SetTextColor(oldfontcolor);
    pDC->SetBkColor(oldbkcolor);
}

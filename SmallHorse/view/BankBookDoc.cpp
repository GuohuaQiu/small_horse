// BankBookDoc.cpp : implementation of the CBankBookDoc class
//

#include "stdafx.h"
#include "..\SmallHorse.h"
#include "..\MainFrm.h"
#include "BankBookDoc.h"
#include "BankBookTree.h"
#include "AddNewItemDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBankBookDoc

IMPLEMENT_DYNCREATE(CBankBookDoc, CDocument)

BEGIN_MESSAGE_MAP(CBankBookDoc, CDocument)
	//{{AFX_MSG_MAP(CBankBookDoc)
#if 0
	ON_COMMAND(IDM_DISPLAYTYPE, OnDisplaytype)
	ON_COMMAND(IDM_DISPLAYTYPECAL, OnDisplaytypecal)
	ON_UPDATE_COMMAND_UI(IDM_DISPLAYTYPECAL, OnUpdateDisplaytypecal)
#endif
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBankBookDoc construction/destruction

CBankBookDoc::CBankBookDoc()
{
	m_curbeginyear=1999;
	m_displaytype=0;

	// TODO: add one-time construction code here

}

CBankBookDoc::~CBankBookDoc()
{
}

BOOL CBankBookDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CBankBookDoc serialization

void CBankBookDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CBankBookDoc diagnostics

#ifdef _DEBUG
void CBankBookDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CBankBookDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBankBookDoc commands
////////////////////////////////////////////////////////////////////////////////

COleDateTime CBankBookDoc::GetCompareTime(COleDateTime timea, COleDateTime timeb, BOOL bMax)
{
	int yeara=timea.GetYear();
	int yearb=timeb.GetYear();
	int montha=timea.GetMonth();
	int monthb=timeb.GetMonth();
	int Daya=timea.GetDay();
	int Dayb=timeb.GetDay();
	if(bMax)
	{
		if(yeara>yearb)
			return timea;
		else if(yeara<yearb)
			return timeb;
		if(montha>monthb)
			return timea;
		else if(montha<monthb)
			return timeb;
		if(Daya>Dayb)
			return timea;
		else if(Daya<Dayb)
			return timeb;
	}
	if(yeara<yearb)
		return timea;
	else if(yeara>yearb)
		return timeb;
	if(montha<monthb)
		return timea;
	else if(montha>monthb)
		return timeb;
	if(Daya<=Dayb)
		return timea;
	else 
		return timeb;

}
#if 0
void CBankBookDoc::OnDisplaytype() 
{
	if(m_displaytype==0)
		m_displaytype=1;
	else
		m_displaytype=0;
	
}


void CBankBookDoc::OnDisplaytypecal() 
{
	if(m_displaytype==0)
		m_displaytype=1;
	else
		m_displaytype=0;
	UpdateAllViews(NULL);
	
}

void CBankBookDoc::OnUpdateDisplaytypecal(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_displaytype!=0);
}
#endif



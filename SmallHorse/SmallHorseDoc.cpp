// SmallHorseDoc.cpp : implementation of the CSmallHorseDoc class
//

#include "stdafx.h"
#include "SmallHorse.h"

#include "SmallHorseDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSmallHorseDoc

IMPLEMENT_DYNCREATE(CSmallHorseDoc, CDocument)

BEGIN_MESSAGE_MAP(CSmallHorseDoc, CDocument)
END_MESSAGE_MAP()


// CSmallHorseDoc construction/destruction

CSmallHorseDoc::CSmallHorseDoc()
{
	// TODO: add one-time construction code here

}

CSmallHorseDoc::~CSmallHorseDoc()
{
}

BOOL CSmallHorseDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CSmallHorseDoc serialization

void CSmallHorseDoc::Serialize(CArchive& ar)
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


// CSmallHorseDoc diagnostics

#ifdef _DEBUG
void CSmallHorseDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSmallHorseDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CSmallHorseDoc commands

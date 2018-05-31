// SmallHorseDoc.h : interface of the CSmallHorseDoc class
//


#pragma once


class CSmallHorseDoc : public CDocument
{
protected: // create from serialization only
	CSmallHorseDoc();
	DECLARE_DYNCREATE(CSmallHorseDoc)

// Attributes
public:

// Operations
public:

// Overrides
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implementation
public:
	virtual ~CSmallHorseDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};



#if !defined(AFX_HTMLRECORDSET_H__92FE69BB_9B57_4AF0_8DC0_797E8899CCBA__INCLUDED_)
#define AFX_HTMLRECORDSET_H__92FE69BB_9B57_4AF0_8DC0_797E8899CCBA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HtmlRecordSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CHtmlRecordSet recordset

class CHtmlRecordSet : public CRecordset
{
private:
    CString m_strHeader;
    CString m_strTitle;
public:
	void SetTitle(const CString& strTitle);
	void SetHeader(const CString& strHeader);
	void ExportTable(CString &strHtml);
	void MakeHeader(CString &strHtml);
	void MakeCurrentRow(CString& strHtml);
	CHtmlRecordSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CHtmlRecordSet)

// Field/Param Data
	//{{AFX_FIELD(CHtmlRecordSet, CRecordset)
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHtmlRecordSet)
	public:
	//}}AFX_VIRTUAL

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HTMLRECORDSET_H__92FE69BB_9B57_4AF0_8DC0_797E8899CCBA__INCLUDED_)

// GroupRow.h: interface for the CGroupRow class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GROUPROW_H__223D48D4_F21B_4D74_9656_D85B026244FE__INCLUDED_)
#define AFX_GROUPROW_H__223D48D4_F21B_4D74_9656_D85B026244FE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CGroupRow : public CBCGPReportRow  
{
	DECLARE_DYNAMIC(CGroupRow)
public:
	void SetExpandValueWithNoRedraw(BOOL bExpand);
	void CollapseInactive();
	void ExpandActive();
	BOOL IsActiveRow();
	CString GetMainID();
	CString& GetText();
	const CRect GetTipRect();
    CString m_strTip;
	CString GetTipString(const CString& strID);
	CGroupRow(const CString& strGroupName);
    BOOL m_bNeedUpdateTip;
    virtual void OnDrawName(CDC*pDC,CRect rect);
	virtual ~CGroupRow();

};

#endif // !defined(AFX_GROUPROW_H__223D48D4_F21B_4D74_9656_D85B026244FE__INCLUDED_)

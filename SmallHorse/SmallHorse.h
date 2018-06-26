// SmallHorse.h : main header file for the SmallHorse application
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif
#define LOAD_DATEBASE
#include "resource.h"       // main symbols
#include <afxdb.h>
    
#include "idset.h"
#include "listset.h"       
#include "SubCountSet.h"       
#include "RateSet.h"       
#include "QueryHistoryList.h"     
#include "BookTypeSet.h"
#include "RecordList.h"
#include "convertdata.h"

// CSmallHorseApp:
// See SmallHorse.cpp for the implementation of this class
//

class CSmallHorseApp : public CWinApp,
							public CBCGPWorkspace
{
public:
	CSmallHorseApp();
	CString AutoNameforQuery(const CStringList& strNameList,const CStringList& strTypeList);
	BOOL GetBookInfo(int nRecordID, CString &strDescription);
	BOOL GetRecordInfo(int nRecordID,CString& strDescription);
	BOOL OpenView(const CString &strFilter,const CString &strOrder,BOOL bSaveHistory = FALSE,LPCTSTR lpstrName = NULL);
	void GenIDList(const CStringList& namelist,CStringList& idlist);
	void Search(const CStringList& idlist,const CStringList& typelist,COleDateTime* pBeginTime=NULL,COleDateTime* pEndTime=NULL, LPCTSTR lpstrName = NULL,LPCTSTR  lpstrCommentLike = NULL);
	void SetBookFilter(const CString strID);
	void CalSum(const CString& strID);
	BOOL ShowAccountInfo(const CString& strID);
	BOOL Rectifypassword(const CString& strID);
	void DeleteRecord(int nRecordID);
	void UpdateAllView();
	BOOL AddNewItem(const CString& strID);
	CDocument* GetDoc();
	
	BOOL OpenBankbook(const CString& strID);
	CIDSet* GetIDSet();
	CListSet* GetListSet();
	static UINT  m_DataFormat;
	int GetTypeIndex(const CString& strType);
	TCHAR	m_cType[256][64];
	// Override from CBCGPWorkspace
	virtual void PreLoadState ();
    virtual BOOL ShowPopupMenu (UINT uiMenuResId, const CPoint& point, CWnd* pWnd);
    virtual BOOL ShowPopupMenu (HMENU hMenu, const CPoint& point, CWnd* pWnd);

protected:
	CMultiDocTemplate* m_pDocTemplate;
	CMultiDocTemplate* m_pCompareTemplate;
public:

// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	afx_msg void OnQuery();
    afx_msg void OnUpdateShowNoExistBook(CCmdUI* pCmdUI);
	afx_msg void OnShowNoExistBook();
	afx_msg BOOL OnOpenQueryFile (UINT nID);
	afx_msg void OnOpenSubCounts();
	afx_msg void OnFileNew();
	afx_msg void OnQueryComment();
	afx_msg void OnQueryDate();
	afx_msg void OnQueryMoney();
	afx_msg void OnCompareDatabase();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
    CIDSet m_IDSet;
    CListSet m_listset;
	CSubCountSet m_subCountSet;
	CRateSet m_rateSet;
	CBookTypeSet m_bookTypeSet;
public:
	void CopyRecordsTo(const CDWordArray& dbAry,
		const CString& strCount,
		const CString& strSubCount,
		BOOL m_bTransfer);
	void GetAllOpendCount(CStringList& list);
	int GetYear(int arrayIndex,CString strFilter);
	int GetDate(CString strDate, int& y, int& m, int& d,int& hh, int& mm,int& ss);
	BOOL SetAutoReturnCreditCard(const CString &strid);
	BOOL IsAccountLocked(const CString &strID);
	void LockCount(const CString &strid);
	float GetRepay(CListSet* pListSet,const CString &strid, const COleDateTime &timeBegin);
	float GetPay(CListSet* pListSet,const CString&strid, const COleDateTime& timeBegin,const COleDateTime &timeEnd);
    BOOL OpenReportView(const CString &strID);
	BOOL OpenCompareView();
	CBookTypeSet* GetBookTypeSet();
	BOOL RenewSubCount(const CString &strID, const CString &strSubID,const COleDateTime &endDate);
	BOOL CloseSubCount(const CString &strID, const CString &strSubID,const COleDateTime &endDate,BOOL bSavetoDefault);
	CRateSet* GetRateSet();
	double GetRate(const COleDateTime &date, int nMonth);
	BOOL IsSubcountActive(const CString &strMainCount, const CString &strSubCount);
	BOOL CloseSubCount(const CString& strMainCount,const CString& strSubCount);
	int  GetBookType(const CString& strId);
	void AddCreditPayInfo(const CString& strID);
	void OpenSubCountbyId(const CString& strId);
	void ModifySubCount(const CString &strId, const CString &strSubId,COleDateTime* pOleDate = NULL, float* pvalue = NULL);
	void DeleteRecords(const CDWordArray& dbAry);
	void LoadAllSite(CStringArray& arySites);
	void ForceUpdateViews();
	static void SelectPeriod(CComboBox *pCmbBox,int nMonth);
	BOOL FreeBook(const CString& strID);
	BOOL RectifyBookInfo(const CString& strID);
	BOOL DeleteBook(const CString& strID);
    void RectifyBookinfo(const CString& strID);
	void GetTypeList(CStringList &strTypeList);
	void GetBankList(CStringList& strBankList);
	static COleDateTime CalEndDate(COleDateTime time, int month);
	void OpenAllCount();
	void OpenAllCountOrderbyBank();
	void OpenAllCountOrderbyOwner();
	void OpenCountsbyBank(CString strText);
	void OpenCountsbyPeople(CString strText);
	BOOL OpenCountsView(const CString &strFilter, VIEW_TYPE viewType, BOOL bSaveHistory ,LPCTSTR lpstrName);
	void TransferDingqi(const CString& strID);
	void FillPeriodtoCombox(CComboBox* pCmbBox);
	CSubCountSet* GetSubCountSet();
	BOOL RenewSubCount(const CString& strID, const CString& strSubID);
public:
	afx_msg void OnAccountNew();
    BOOL m_bShowNoExistBook;
	CQueryItemList m_querylist;
public:
	int StaticDoubtItems(CString& nID);
};

extern CSmallHorseApp theApp;
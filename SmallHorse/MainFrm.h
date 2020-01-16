// MainFrm.h : interface of the CMainFrame class
//


#pragma once
#include "bar\WorkSpaceBar.h"
#include "bar\WorkSpaceBar2.h"
#include "OutputBar.h"
#include "bar\TaskPane.h"

class CMainFrame : public CBCGPMDIFrameWnd
{
public:
	CMainFrame();

protected: // create from serialization only
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd* pParentWnd = NULL, CCreateContext* pContext = NULL);

// Implementation
public:
	void SetQueryDay(const COleDateTime& day);
	void UpdateQueryList();
	BOOL ShowAccountInfo(CIDSet *pSet);
	CBankbookTree* GetBookTree();
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CBCGPMenuBar		m_wndMenuBar;
	CBCGPStatusBar  m_wndStatusBar;
	CBCGPToolBar    m_wndToolBar;
	CBCGPReBar			m_wndReBar;
	
	
	
	CWorkspaceBar	m_wndWorkSpace;
	CWorkspaceBar2	m_wndWorkSpace2;
	COutputBar	m_wndOutput;

	CBCGPToolBarImages	m_UserImages;
	CTaskPane				m_wndTaskPane;
// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnFileClose();
	afx_msg void OnViewCustomize();
	afx_msg void OnDayRoundQuery();
	afx_msg LRESULT OnToolbarReset(WPARAM,LPARAM);
	void OnToolsViewUserToolbar (UINT id);
	void OnUpdateToolsViewUserToolbar (CCmdUI* pCmdUI);
	afx_msg LRESULT OnToolbarContextMenu(WPARAM,LPARAM);
	afx_msg LRESULT OnHelpCustomizeToolbars(WPARAM wp, LPARAM lp);
	afx_msg void OnAppLook(UINT id);
	afx_msg void OnUpdateAppLook(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()

	BOOL CreateTaskPane ();

	UINT	m_nAppLook;
};



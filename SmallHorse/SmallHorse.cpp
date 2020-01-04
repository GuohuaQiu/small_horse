// SmallHorse.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "SmallHorse.h"
#include "querysheet.h"
#include "MainFrm.h"
#include "PassWordDlg.h"
#include "typeSet.h"
#include "AddNewItemDlg.h"
#include "DingQiInputDlg.h"
#include "CreditPayDlg.h"
#include "CreditPaySet.h"
#include "QueryFromDateDlg.h"
#include "QueryFromMoneyDlg.h"
#include "QueryFromCommentDlg.h"
#include "NewBook.h"
#include "BankbookDoc.h"
#include "ReportDemoView.h"
#include "CloseSubCountDlg.h"
#include "CompareFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSmallHorseApp

CString g_strAutoReturnCreditCard;
BEGIN_MESSAGE_MAP(CSmallHorseApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_QUERY, OnQuery)
	ON_COMMAND(ID_TODO, OnTodo)
    ON_UPDATE_COMMAND_UI(ID_ACCOUNT_SHOW_CLOSED, OnUpdateShowNoExistBook)
	ON_COMMAND(ID_ACCOUNT_SHOW_CLOSED, OnShowNoExistBook)
	ON_COMMAND_EX_RANGE(ID_FILE_MRU_QUERY0, ID_FILE_MRU_QUERY15, OnOpenQueryFile)
	//ON_COMMAND(ID_FILE_NEW_FRAME, OnFileNewFrame)
	//ON_COMMAND(ID_GO_BACK, OnFileNew)
	ON_COMMAND(ID_QUERY_COMMENT, OnQueryComment)
	ON_COMMAND(ID_QUERY_DATE, OnQueryDate)
	ON_COMMAND(ID_QUERY_MONEY, OnQueryMoney)
	ON_COMMAND(ID_SUBCOUNT_LIST_ALL, OnOpenSubCounts)
	ON_COMMAND(ID_DATABASE_COMPARE, OnCompareDatabase)
	// Standard print setup command
	ON_COMMAND(ID_ACCOUNT_NEW, &CSmallHorseApp::OnAccountNew)
END_MESSAGE_MAP()


// CSmallHorseApp construction
UINT  CSmallHorseApp::m_DataFormat = 0;

typedef struct 
{
	int month;
	TCHAR cName[FIELD_NAME_LEN];
}SAVE_PERIOD;

#define PEROID_TYPE   6
SAVE_PERIOD gSavePeroid[PEROID_TYPE] = {
	{3,_T("三月")},
	{6,_T("六月")},
	{12,_T("一年")},
	{24,_T("两年")},
	{36,_T("三年")},
	{60,_T("五年")}
};

CSmallHorseApp::CSmallHorseApp() :
	CBCGPWorkspace (TRUE /* m_bResourceSmartUpdate */)
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
	for(int i=0;i<256;i++)
	{
		m_cType[i][0]=0;
	}
    m_bShowNoExistBook = FALSE;
}

// The one and only CSmallHorseApp object

CSmallHorseApp theApp;


// CSmallHorseApp initialization

BOOL CSmallHorseApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}
	AfxEnableControlContainer();
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("BCGP AppWizard-Generated Applications"));
	LoadStdProfileSettings(4);  // Load standard INI file options (including MRU)
	m_querylist.Load();

	SetRegistryBase (_T("Settings"));

	// Initialize all Managers for usage. They are automatically constructed
	// if not yet present
	InitContextMenuManager();
	InitKeyboardManager();

	// TODO: Remove this if you don't want extended tooltips:
	InitTooltipManager();

	CBCGPToolTipParams params;
	params.m_bVislManagerTheme = TRUE;

	theApp.GetTooltipManager ()->SetTooltipParams (
		BCGP_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS (CBCGPToolTipCtrl),
		&params);

#ifdef  LOAD_DATEBASE

	CTypeSet typeset;
	if(!typeset.Open())
	{
		AfxMessageBox(_T("数据库装载错误(type)!"));
		return FALSE;
	};
	typeset.Requery();
	typeset.MoveFirst();
	while(!typeset.IsEOF())
	{
		_tcscpy(m_cType[typeset.m_typeid],typeset.m_strType);
		typeset.MoveNext();
	}
	typeset.Close();
#endif

    
	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views

	CBCGPGridRow::m_strFormatFloat = _T("%.2f");
	
	m_pDocTemplate = new CMultiDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CBankBookDoc),
		RUNTIME_CLASS(CReportFrame), // custom MDI child frame
		RUNTIME_CLASS(CReportDemoView));

	m_pCompareTemplate = new CMultiDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CDocument),
		RUNTIME_CLASS(CCompareFrame), // custom MDI child frame
		RUNTIME_CLASS(CView));

	AddDocTemplate(m_pDocTemplate);
    m_DataFormat = RegisterClipboardFormat(_T("RECORD_BANKBOOK"));
	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;
#if 0
	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	if(cmdInfo.m_nShellCommand==CCommandLineInfo::FileNew)
		cmdInfo.m_nShellCommand=CCommandLineInfo::FileNothing;

	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
#endif
	// The one and only window has been initialized, so show and update it
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	// call DragAcceptFiles only if there's a suffix
	//  In an SDI app, this should occur after ProcessShellCommand
	return TRUE;
}

// CSmallHorseApp message handlers

int CSmallHorseApp::ExitInstance() 
{
	BCGCBProCleanUp();
	m_querylist.Save();
	if(m_pCompareTemplate)
	{
		delete m_pCompareTemplate;
		m_pCompareTemplate = NULL;
	}
	return CWinApp::ExitInstance();
}

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };
	CBCGPURLLinkButton m_btnURL;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMPANY_URL, m_btnURL);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

// App command to run the dialog
void CSmallHorseApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}


// CSmallHorseApp message handlers
#if 0
void CSmallHorseApp::OnFileNewFrame() 
{
	ASSERT(m_pDocTemplate != NULL);

	CDocument* pDoc = NULL;
	CFrameWnd* pFrame = NULL;

	// Create a new instance of the document referenced
	// by the m_pDocTemplate member. 
	pDoc = m_pDocTemplate->CreateNewDocument();
	if (pDoc != NULL)
	{
		// If creation worked, use create a new frame for
		// that document.
		pFrame = m_pDocTemplate->CreateNewFrame(pDoc, NULL);
		if (pFrame != NULL)
		{
			// Set the title, and initialize the document.
			// If document initialization fails, clean-up
			// the frame window and document.

			m_pDocTemplate->SetDefaultTitle(pDoc);
			if (!pDoc->OnNewDocument())
			{
				pFrame->DestroyWindow();
				pFrame = NULL;
			}
			else
			{
				// Otherwise, update the frame
				m_pDocTemplate->InitialUpdateFrame(pFrame, pDoc, TRUE);
			}
		}
	}

	// If we failed, clean up the document and show a
	// message to the user.

	if (pFrame == NULL || pDoc == NULL)
	{
		delete pDoc;
		AfxMessageBox(AFX_IDP_FAILED_TO_CREATE_DOC);
	}
}
#endif
void CSmallHorseApp::OnFileNew() 
{
	CDocument* pDoc = NULL;
	CFrameWnd* pFrame;
	pFrame = DYNAMIC_DOWNCAST(CFrameWnd, CWnd::GetActiveWindow());
	
	if (pFrame != NULL)
		pDoc = pFrame->GetActiveDocument();

	if (pFrame == NULL || pDoc == NULL)
	{
		// if it's the first document, create as normal
		CWinApp::OnFileNew();
	}
	else
	{
		// Otherwise, see if we have to save modified, then
		// ask the document to reinitialize itself.
		if (!pDoc->SaveModified())
			return;

		CDocTemplate* pTemplate = pDoc->GetDocTemplate();
		ASSERT(pTemplate != NULL);

		pTemplate->SetDefaultTitle(pDoc);
		pDoc->OnNewDocument();
	}
}

void CSmallHorseApp::PreLoadState ()
{
	GetContextMenuManager()->AddMenu (_T("My menu"), IDR_RECORD_MENU);
	GetContextMenuManager()->AddMenu (_T("My menu2"), IDR_BANKBOOK_MENU);
    GetContextMenuManager()->AddMenu (_T("My menu3"), IDR_SUBCOUNT_MENU);
    GetContextMenuManager()->AddMenu (_T("My menu4"), IDR_MENU_COMPARE);
}



/*******************************************
    Function Name :	 
    Create by     :	  Qiu Simon
    Input         :   
    Output        :   
    Description   :   
    Date          :   1/10/2011 5:01:52 PM
********************************************/
CBookTypeSet* CSmallHorseApp::GetBookTypeSet()
{
#ifdef  LOAD_DATEBASE
    if(!m_bookTypeSet.IsOpen())
    	m_bookTypeSet.Open();

    return &m_bookTypeSet;
#else
    return NULL;
#endif

}


//return value:
//0 : fail
//1 : only date
//2 : date and time
//2014-10-21

int CSmallHorseApp::GetDate(CString strDate, int &y, int &m, int &d,int& hh, int& mm,int& ss)
{
	if(strDate.FindOneOf("-")!=-1)
	{
		if(strDate.FindOneOf(":")!=-1 )
		{
			_stscanf(strDate,_T("%d-%d-%d %d:%d:%d"),&y,&m,&d,&hh,&mm,&ss);
			return 2;
		}
		_stscanf(strDate,_T("%d-%d-%d"),&y,&m,&d);
		
	}
	else
	{
		int date_len = strDate.GetLength();
		if(date_len >13)
		{
			if(strDate.Find('\/')>0)//2018/9/18  18:20:30
			{
				_stscanf(strDate,_T("%d\/%d\/%d %d:%d:%d"),&y,&m,&d,&hh,&mm,&ss);
			}
			else//20150921  01:40:22
			{
				_stscanf(strDate,_T("%4d%2d%2d %d:%d:%d"),&y,&m,&d,&hh,&mm,&ss);
			}
			return 2;
		}
		else if(date_len >= 8)//"20100203"
		{
			_stscanf(strDate,_T("%4d%2d%2d"),&y,&m,&d);
		}
		else if(date_len == 5)//"09/23"
		{
			_stscanf(strDate,_T("%2d/%2d"),&m,&d);
			COleDateTime time = COleDateTime::GetCurrentTime();
			y = time.GetYear();
			int currentM = time.GetMonth();
			if(m>currentM)
			{
				y--;
			}
		} 
		else
		{
			return 0;
		}

	}

	return 1;
}

int CSmallHorseApp::GetYear(int arrayIndex,CString strFilter)
{
#ifdef USE_APP_LIST_SET
	CListSet* pListSet = GetListSet();
#else
	CListSet setEdit;
	setEdit.Open();
	CListSet* pListSet = &setEdit;
#endif
	
	if(pListSet->MoveToID(arrayIndex,strFilter))
	{
		return pListSet->m_day.GetYear();
	}
}
 

int CSmallHorseApp::GetTypeIndex(const CString &strType)
{
	for(int i=0;i<256;i++)
	{
		if(strType==m_cType[i])
			return i;
	}
	return -1;
}

/*******************************************
    Function Name :	 
    Create by     :	  Qiu Simon
    Input         :   
    Output        :   
    Description   :   
    Date          :   2009-2-4 10:57:44
********************************************/
CIDSet* CSmallHorseApp::GetIDSet()
{
#ifdef  LOAD_DATEBASE
    if(!m_IDSet.IsOpen())
    {
    	m_IDSet.Open();
    }

    return &m_IDSet;
#else
    return NULL;
#endif
}


/*******************************************
    Function Name :	 
    Create by     :	  Qiu Simon
    Input         :   
    Output        :   
    Description   :   
    Date          :   2009-2-4 11:11:42
********************************************/
CListSet* CSmallHorseApp::GetListSet()
{
    if(!m_listset.IsOpen())
    {
        m_listset.Open(AFX_DB_USE_DEFAULT_TYPE,  NULL, CRecordset::skipDeletedRecords  );
    }
    return &m_listset;
}




BOOL CSmallHorseApp::OpenBankbook(const CString &strID)
{
	CString strfil=_T("\'")+strID+_T("\'");
    CString strFilter;
	CString strSort;
	strFilter =_T("Item_Book_ID=") + strfil;// '379 70052992*3'
	strSort=_T("OperDate,Index");// '379 70052992*3'
	OpenView(strFilter,strSort);

	return TRUE;
}

CDocument* CSmallHorseApp::GetDoc()
{
	POSITION pos=m_pDocTemplate->GetFirstDocPosition();
	if(pos==NULL)
		return NULL;
	return m_pDocTemplate->GetNextDoc(pos);
}


/*******************************************
    Function Name :	 
    Create by     :	  Qiu Simon
    Input         :   
    Output        :   
    Description   :   
    Date          :   5/24/2012 10:01:38 AM
********************************************/
BOOL CSmallHorseApp::IsAccountLocked(const CString &strID)
{
    CIDSet* pidset = GetIDSet();
    int status = pidset->GetEditStatus(strID);

    if(status == 0)
    {
        CString strWarn;
        strWarn.Format("%s 已经锁定了，不能增加，删除以及修改.",strID);
        ::MessageBox(NULL,strWarn,_T("确认"),MB_OK|MB_ICONEXCLAMATION);
        return TRUE;
    }
    return FALSE;
}

BOOL CSmallHorseApp::AddNewItem(const CString &strID)
{
    if(IsAccountLocked(strID))
    {
        return FALSE;
    }

	CAddNewItemDlg dlg;
	dlg.m_id=strID;
/**** Add by Qiu Guohua on 2004-07-19 09:50:39 **********************/
	dlg.m_nType=m_IDSet.m_bDefaultNetIncome;
/**************************2004-07-19 09:50:39 **********************/
	CListSet* plistset = GetListSet();
	do{
		if(dlg.DoModal()==IDOK)
		{
			if(plistset->GetRecordCount())
			{
				plistset->Requery();
				plistset->MoveLast();
			}
			CListSet listData;

//			plistset->AddNew();
			listData.m_day=dlg.m_date;
			listData.m_ID=dlg.m_id;
			listData.m_remain=dlg.m_remain;
			listData.m_bType=(BYTE)dlg.m_nType;
			listData.m_addorsub=dlg.m_sum;
			listData.m_strSubCount = dlg.m_strSubCount;
            listData.m_strSite = dlg.m_strSite;
 //           BOOL b = plistset->UpdateRequery();
 //           if(!b)
 //           {
  //              AfxMessageBox("提交失败！");
 //           }
			plistset->New_Item(&listData);
			//Simon UpdateAllView();
			dlg.m_bnewbook=FALSE;
		}
	}while(dlg.bgonext==TRUE);
	return TRUE;
}

void CSmallHorseApp::UpdateAllView()
{
	CBankBookDoc* pdoc = (CBankBookDoc*)GetDoc();
	if(pdoc == NULL)
		return;
	pdoc->UpdateAllViews(NULL,NULL,NULL);

}

void CSmallHorseApp::DeleteRecord(int nRecordID)
{
	CString strTip;
	strTip.Format(_T("确定要删除序号为 %d 的记录吗?"),nRecordID);
	if(IDYES == ::MessageBox(NULL,strTip,_T("确认"),MB_YESNO|MB_ICONEXCLAMATION))
	{
		CListSet* plistset = GetListSet();
		BOOL bSuccess = plistset->MoveToID(nRecordID);
		if(!bSuccess)
		{
			ASSERT(FALSE);
			CString strID;
			strID.Format(_T("%d"),nRecordID);
			plistset->m_strFilter =_T("Index = ") + strID;// '379 70052992*3'
			plistset->Requery();
			bSuccess = plistset->MoveToID(nRecordID);
			if(!bSuccess)
			{
				TRACE(_T("\nFALSE TO  MOVE TO  ID."));
				return;
			}
		}
		plistset->Delete();
		plistset->Requery();
		UpdateAllView();
	}
}


/*******************************************
    Function Name : 
    author        : Qiu Guohua
    Date          : 2009-2-13 23:43:10
    Description   : 
    Return type  : 
    Argument      : 
********************************************/
BOOL CSmallHorseApp::Rectifypassword(const CString& strID)
{
#ifdef  LOAD_DATEBASE
    CIDSet* pIdSet = theApp.GetIDSet();
    if(!pIdSet->MovetoCurID(strID))
    {
        return FALSE;
    }

    CString strpw0,strpw1;
	CPassWordDlg pwdlg;
	do{
		pwdlg.m_id=_T("请输入新密码:");
		pwdlg.m_password=_T("");
		if(pwdlg.DoModal()!=IDOK)
			return FALSE;
		strpw0=pwdlg.m_password;
		pwdlg.m_id=_T("请再输入一次新密码:");
		pwdlg.m_password=_T("");
		if(pwdlg.DoModal()!=IDOK)
			return FALSE;
		strpw1=pwdlg.m_password;
	}while(strpw0!=strpw1);
	
// 	pIdSet->Edit();
// 	pIdSet->m_password=strpw1;
// 	pIdSet->Update();
	if(pIdSet->Change_Pwd(strpw1))
	{
		pIdSet->Requery();
		pIdSet->MovetoCurID(strID);
		if(pIdSet->m_password==strpw1)
			AfxMessageBox(_T("您的新密码已经确认,谢谢使用!"));

	}
	return TRUE;

#endif
}


/*******************************************
    Function Name : 
    author        : Qiu Guohua
    Date          : 2009-2-14 14:20:36
    Description   : 
    Return type   : 
    Argument      : 
********************************************/
BOOL CSmallHorseApp::ShowAccountInfo(const CString &strID)
{
	if(!m_IDSet.MovetoCurID(strID))
		return FALSE;
	return ((CMainFrame*)m_pMainWnd)->ShowAccountInfo(&m_IDSet);
}

#include <afxcoll.h>
/*******************************************
    Function Name : 
    author        : Qiu Guohua
    Date          : 2009-2-14 21:11:38
    Description   : 
    Return type  : 
    Argument      : 
********************************************/
void CSmallHorseApp::CalSum(const CString &strID)
{
	
    if(IsAccountLocked(strID))
    {
        return;
    }

    CMapStringToPtr map;
	map.InitHashTable(16);
	
    CListSet* pListSet = GetListSet();
	SetBookFilter(strID);
    if(!pListSet->IsBOF())
    {
        pListSet->MoveFirst();
    }
    pListSet->SetUpdateTime(FALSE);
	float fBaseSum = 0.0;
	while(!pListSet->IsEOF())
	{
		if(pListSet->m_strSubCount == "")
		{
			pListSet->Edit_CalSum(&fBaseSum);
		} 
		else
		{
			float *pf;
			if(map.Lookup(pListSet->m_strSubCount,(void*&)pf))
			{
				pListSet->Edit_CalSum(pf);
				TRACE(_T("MAP[%s] = %f\n"),pListSet->m_strSubCount,*pf);
			}
			else
			{//first record for a subcount.
				float *pff = new float;
				*pff = 0.0;
				pListSet->Edit_CalSum(pff);
				map[pListSet->m_strSubCount] = pff;
				TRACE(_T("MAP[%s] = %f init\n"),pListSet->m_strSubCount,*pff);
			}
		}
		pListSet->MoveNext();
	}
    pListSet->SetUpdateTime(TRUE);
	pListSet->Requery();
	UpdateAllView();
	
	POSITION pos;
	CString key;
	float* p;
	
	for( pos = map.GetStartPosition(); pos != NULL; )
	{
		map.GetNextAssoc( pos, key, (void*&)p );
		delete p;
	}
	map.RemoveAll();
}

void CSmallHorseApp::SetBookFilter(const CString strID)
{
	CString strfil=_T("\'")+strID+_T("\'");
	m_listset.m_strFilter =_T("Item_Book_ID=") + strfil;
	m_listset.m_strSort=_T("OperDate,Index");
    m_listset.Requery();
}


/*******************************************
    Function Name : 
    author        : Qiu Guohua
    Date          : 2009-4-20 21:32:05
    Description   : 
    Return type  : 
    Argument      : 
********************************************/
BOOL CSmallHorseApp::OnOpenQueryFile (UINT nID)
{
	ASSERT_VALID(this);

	ASSERT(nID >= ID_FILE_MRU_QUERY0);
	ASSERT(nID < ID_FILE_MRU_QUERY0 + (UINT)m_querylist.GetCount());
	int nIndex = nID - ID_FILE_MRU_QUERY0;


	CQueryItem* pItem = m_querylist.Get(nIndex);
	if(pItem)
	{
		OpenView(pItem->strFilter,_T("OperDate,Index"),FALSE,pItem->strName);
	}

	return TRUE;
}

void CSmallHorseApp::OnShowNoExistBook() 
{
    m_bShowNoExistBook = !m_bShowNoExistBook;

}

void CSmallHorseApp::OnQuery() 
{
	CStringList strNameList;
	CStringList strTypeList;
	CQuerySheet dlg(_T("复杂查询"));
	dlg.m_pNameList=&strNameList;
	dlg.m_pTypeList=&strTypeList;

	dlg.m_pgName.m_pIDSet=&(m_IDSet);
	if(dlg.DoModal()!=ID_WIZFINISH )
		return;
	CStringList strIDList;
	GenIDList(strNameList,strIDList);
	CString strQueryName = AutoNameforQuery(strNameList,strTypeList);
	if(dlg.m_bUseTime)
        Search(strIDList,strTypeList,&dlg.m_beginTime,&dlg.m_endTime,strQueryName,dlg.m_strCommentLike.GetLength()>0 ? (LPCTSTR)dlg.m_strCommentLike : NULL);
	else
		Search(strIDList,strTypeList,NULL,NULL,strQueryName,dlg.m_strCommentLike.GetLength()>0 ? (LPCTSTR)dlg.m_strCommentLike : NULL);

}

void CSmallHorseApp::OnTodo()
{
    OpenTodoView();
}

void CSmallHorseApp::Search(const CStringList &idlist, const CStringList &typelist, COleDateTime *pBeginTime, COleDateTime *pEndTime, LPCTSTR lpstrName,LPCTSTR lpstrCommentLike)
{
	CString strfil;
	CString strID;
	CString strType;
	CString strTime;
    CString strComment;
	if(idlist.GetCount()>0)
	{
		strID=_T("Item_Book_ID IN(");
		POSITION pos=idlist.GetHeadPosition();
		while(pos)
		{
			strID+='\'';
			strID+=idlist.GetNext(pos);
			strID+='\'';
			if(pos)
				strID+=_T(",");
		}
		strID+=_T(")");
	}
	if(pBeginTime&&pEndTime)
	{
		CString strBegin=pBeginTime->Format(_T("#%Y-%m-%d#"));
		CString strEnd=pEndTime->Format(_T("#%Y-%m-%d#"));
		strTime.Format(_T("(OperDate BETWEEN %s and %s)"),strBegin,strEnd);
	}
	if(typelist.GetCount()>0)
	{
		strType=_T("(");
		POSITION pos=typelist.GetHeadPosition();
		while(pos)
		{
			CString strt=typelist.GetNext(pos);
			int n=theApp.GetTypeIndex(strt);
			if(n==-1)
				continue;
			CString strid;
			strid.Format(_T("Type=%d"),n);
			strType+=strid;
			if(pos)
				strType+=_T(" or ");
		}
		strType+=_T(")");
	}

    if(lpstrCommentLike)
    {
        strComment = _T("Comment LIKE \'%");
        strComment += lpstrCommentLike;
        strComment += _T("%\'");
        
    }
	strfil=strID;
	if(strTime!=_T(""))
	{
        if(strfil.GetLength()>0)
        {
            strfil+=_T(" and ");
        }
		strfil+=strTime;
	}
	if(strType!=_T(""))
	{
        if(strfil.GetLength()>0)
        {
            strfil+=_T(" and ");
        }
        strfil+=strType;
	}

    if(strComment!=_T(""))
    {
        if(strfil.GetLength()>0)
        {
            strfil+=_T(" and ");
        }
        strfil+=strComment;
    }
	TRACE(_T("\n"));
	TRACE(strType);
	TRACE(_T("\n"));
	TRACE(_T("--begin-\n"));
	TRACE(_T("\n"));
	TRACE(_T("--end-\n"));
	TRACE(_T("\n"));
	CFile file;
	file.Open(_T("C:\\testfil.txt"),CFile::modeCreate|CFile::modeWrite);
	file.Write((LPTSTR)(LPCTSTR)strfil,strfil.GetLength());
	file.Close();
	
	OpenView(strfil,_T("OperDate,Index"),TRUE,lpstrName);
}

void CSmallHorseApp::GenIDList(const CStringList &namelist, CStringList &idlist)
{
	CString strfil;
	if(namelist.GetCount()>0)
	{
		strfil=_T("Book_Owner IN(");
		POSITION pos=namelist.GetHeadPosition();
		while(pos)
		{
			CString strName=namelist.GetNext(pos);
			strfil+=_T("\'");
			strfil+=strName;
			strfil+=_T("\'");
			if(pos)
				strfil+=',';
		}
		strfil+=_T(")");

        m_IDSet.m_strFilter=strfil;
        m_IDSet.Requery();
        while(!m_IDSet.IsEOF())
        {
            idlist.AddTail(m_IDSet.m_ID);
            m_IDSet.MoveNext();
        }
	}
    else
    {
        //if on name ,we search all. no need to make a idlist.
    }
}


BOOL CSmallHorseApp::OpenView(const CString &strFilter, const CString &strOrder, BOOL bSaveHistory ,LPCTSTR lpstrName)
{
	CMainFrame* pfrm=(CMainFrame*)AfxGetMainWnd();

	CDocument* pdoc=GetDoc();
	if(pdoc)
	{
		POSITION pos=pdoc->GetFirstViewPosition();
		CView* pview;
		while(pos)
		{
			pview=pdoc->GetNextView(pos);
			CReportFrame* psfrm=(CReportFrame*)pview->GetParent();
			//the view has created activate it.
			if(IS_RECORD(psfrm->m_ViewType))
			{	
				if((strFilter == psfrm->m_strFilter))
				{
					((CFrameWnd*)psfrm)->ActivateFrame();
					return TRUE;
				}
			}
		}
	}
	else
	{
		pdoc= m_pDocTemplate->CreateNewDocument();
	}

	CReportFrame* pcframe=(CReportFrame*)m_pDocTemplate->CreateNewFrame(pdoc,NULL);
	pcframe->SetFilter(strFilter,strOrder);
	if(lpstrName)
	{
		pcframe->m_strTitle = lpstrName;
	}

	m_pDocTemplate->InitialUpdateFrame(pcframe, pdoc);
	if(bSaveHistory)
	{
		m_querylist.AddNewQuery(strFilter,lpstrName);
		((CMainFrame*)m_pMainWnd)->UpdateQueryList();
	}
	return TRUE;
}


/*******************************************
    Function Name : 
    author        : Qiu Guohua
    Date          : 2009-3-6 21:04:45
    Description   : 
    Return type  : 
    Argument      : 
********************************************/
BOOL CSmallHorseApp::GetRecordInfo(int nRecordID,CString &strDescription)
{
    CListSet* pListSet = GetListSet();
	BOOL b = pListSet->MoveToID(nRecordID);
	if(!b)
	{
		return FALSE;
	}
	strDescription.Format(_T("%s\n\n%s\n\n%s"),m_listset.m_addorsub,m_listset.GetDate(),m_listset.m_remain);
	return TRUE;
}


/*******************************************
    Function Name : 
    author        : Qiu Guohua
    Date          : 2009-3-6 21:15:02
    Description   : 
    Return type  : 
    Argument      : 
********************************************/
BOOL CSmallHorseApp::GetBookInfo(int nRecordID, CString &strDescription)
{
	BOOL b = m_listset.MoveToID(nRecordID);
	if(!b)
	{
		return FALSE;
	}
	b = m_IDSet.MovetoCurID(m_listset.m_ID);
	if(!b)
	{
		return FALSE;
	}
	strDescription.Format(_T("%s\n\n%s\n\n%s"),m_listset.m_ID,m_IDSet.m_name,m_IDSet.m_bank);
	return TRUE;
}


/*******************************************
    Function Name : 
    author        : Qiu Guohua
    Date          : 2009-4-20 20:17:17
    Description   : 
    Return type  : 
    Argument      : 
********************************************/
CString CSmallHorseApp::AutoNameforQuery(const CStringList &namelist, const CStringList &typelist)
{
	CString retName;
	POSITION pos=namelist.GetHeadPosition();
	while(pos)
	{
		CString strName=namelist.GetNext(pos);
		retName+=strName;
		retName+=_T(" ");
	}
	retName+=_T("的");
	
	pos=typelist.GetHeadPosition();
	while(pos)
	{
		CString strName=typelist.GetNext(pos);
		retName+=strName;
		retName+=_T(" ");
	}
	return retName;
}


CSubCountSet* CSmallHorseApp::GetSubCountSet()
{
#ifdef  LOAD_DATEBASE
    if(!m_subCountSet.IsOpen())
    	m_subCountSet.Open();

    return &m_subCountSet;
#else
    return NULL;
#endif

}

/*******************************************
    Function Name : 
    author        : Qiu Guohua
    Date          : 2009-4-23 22:29:28
    Description   : 
    Return type  : 
    Argument      : 
********************************************/
void CSmallHorseApp::FillPeriodtoCombox(CComboBox *pCmbBox)
{
	for(int i = 0;i<PEROID_TYPE;i++)
	{
		pCmbBox->InsertString(i,gSavePeroid[i].cName);
		pCmbBox->SetItemData(i,gSavePeroid[i].month);
	}
}



/*******************************************
    Function Name : 
    author        : Qiu Guohua
    Date          : 2009-4-23 22:29:40
    Description   : 
    Return type  : 
    Argument      : 
********************************************/
void CSmallHorseApp::TransferDingqi(const CString& strID) 
{
        if(IsAccountLocked(strID))
        {
            return ;
        }

	CDingQiInputDlg dlg;
	dlg.m_id = strID;
	CSubCountSet* pSubCountSet = GetSubCountSet();
	CListSet* pListSet = GetListSet();
	if(dlg.DoModal()==IDOK)
	{
		pSubCountSet->MoveLast();
		pSubCountSet->AddNew();
		pSubCountSet->m_Comment = dlg.m_remain;
		pSubCountSet->m_Count_ID = strID;
		pSubCountSet->m_Sub_Count_ID = dlg.m_strSubCount;
		pSubCountSet->m_Start_Date = dlg.m_date;
		pSubCountSet->m_End_Date = CalEndDate(dlg.m_date, dlg.m_nMonth);
        //get rate from database, rate field is not needed.
		//pSubCountSet->m_Year_Rate = dlg.m_fRate;
		pSubCountSet->m_Time_Span = dlg.m_nMonth;
		pSubCountSet->m_BeginValue = dlg.m_sum;
		pSubCountSet->Update();
        pSubCountSet->RequeryCount(strID);

        if(!dlg.m_bNewSave)
        {
			CListSet listData;
//            pListSet->AddNew();
            listData.m_day=dlg.m_date;
            listData.m_ID=strID;
            listData.m_strSubCount = _T("");
            listData.m_remain.Format(_T("转存为定期:%s"),dlg.m_strSubCount);
            listData.m_bType=3;
            listData.m_addorsub.Format(_T("%f"),dlg.m_sum);
            listData.m_addorsub.Insert(0,_T("-"));
//            pListSet->Update();
			pListSet->New_Item(&listData);
        }
		CListSet listData;
//		pListSet->AddNew();
		listData.m_day=dlg.m_date;
		listData.m_ID=strID;
		listData.m_strSubCount = dlg.m_strSubCount;
		listData.m_remain= _T("");
		listData.m_bType=3;
		listData.m_addorsub.Format(_T("%f"),dlg.m_sum);

		pListSet->New_Item(&listData);
//		pListSet->Update();
	}
    ForceUpdateViews();
}

/*******************************************
    Function Name : 
    author        : Qiu Guohua
    Date          : 2009-4-29 22:13:56
    Description   : 
    Return type  : 
    Argument      : 
********************************************/
BOOL CSmallHorseApp::OpenCountsView(const CString &strFilter, VIEW_TYPE viewType, BOOL bSaveHistory, LPCTSTR lpstrName)
{
	CMainFrame* pfrm=(CMainFrame*)AfxGetMainWnd();

	CDocument* pdoc=GetDoc();
	if(pdoc)
	{
		POSITION pos=pdoc->GetFirstViewPosition();
		CView* pview;
		while(pos)
		{
			pview=pdoc->GetNextView(pos);
			CReportFrame* psfrm=(CReportFrame*)pview->GetParent();
			//the view has created activate it.
			if(IS_COUNTS(psfrm->m_ViewType ))
			{
				if(strFilter == psfrm->m_strFilter)
				{	
					((CFrameWnd*)psfrm)->ActivateFrame();
					return TRUE;
				}
			}
		}
	}
	else
	{
		pdoc= m_pDocTemplate->CreateNewDocument();
	}

	CReportFrame* pcframe=(CReportFrame*)m_pDocTemplate->CreateNewFrame(pdoc,NULL);
	pcframe->SetCountsFilter(strFilter,viewType,lpstrName);

	m_pDocTemplate->InitialUpdateFrame(pcframe, pdoc);

	return TRUE;
}


/*******************************************
    Function Name : 
    author        : Qiu Guohua
    Date          : 2009-5-4 20:33:07
    Description   : open all sub count
    Return type  : 
    Argument      : 
********************************************/
void CSmallHorseApp::OnOpenSubCounts()
{
	OpenCountsView(SQL_OPEN_ALL_SUB_COUNT SQL_GROUP_SUB_COUNT_WITH_SUM, \
		           VIEW_TYPE_SUB_COUNTS,\
				   FALSE,\
				   _T("子账户列表"));
}



/*******************************************
    Function Name : 
    author        : Qiu Guohua
    Date          : 2009-5-4 20:32:45
    Description   : open all maincount
    Return type   : 
    Argument      : 
********************************************/
void CSmallHorseApp::OpenAllCount()
{
    if(m_bShowNoExistBook)
    {
        OpenCountsView(SQL_OPEN_ALL_MAIN_COUNT,
            VIEW_TYPE_MAIN_COUNTS,
            FALSE,
            _T("账户列表"));
        
    }
    else
    {
        OpenCountsView(SQL_OPEN_ALL_EXIST_MAIN_COUNT,
            VIEW_TYPE_MAIN_COUNTS,
            FALSE,
            _T("账户列表"));

    }
}


/*******************************************
    Function Name :	 
    Create by     :	  Qiu Simon
    Input         :   
    Output        :   
    Description   :   
    Date          :   2010-2-26 17:17:46
********************************************/
void CSmallHorseApp::OpenAllCountOrderbyBank()
{
    if(m_bShowNoExistBook)
    {
        OpenCountsView(SQL_OPEN_ALL_MAIN_COUNT SQL_ORDER_BY_BANK,
            VIEW_TYPE_MAIN_COUNTS,
            FALSE,
            _T("账户列表"));
        
    }
    else
    {
        OpenCountsView(SQL_OPEN_ALL_EXIST_MAIN_COUNT SQL_ORDER_BY_BANK,
            VIEW_TYPE_MAIN_COUNTS,
            FALSE,
            _T("账户列表"));
    }
}


/*******************************************
    Function Name :	 
    Create by     :	  Qiu Simon
    Input         :   
    Output        :   
    Description   :   
    Date          :   2010-2-26 17:18:38
********************************************/
void CSmallHorseApp::OpenAllCountOrderbyOwner()
{
    if(m_bShowNoExistBook)
    {
        OpenCountsView(SQL_OPEN_ALL_MAIN_COUNT SQL_ORDER_BY_OWNER,
            VIEW_TYPE_MAIN_COUNTS,
            FALSE,
            _T("账户列表"));
        
    }
    else
    {
        OpenCountsView(SQL_OPEN_ALL_EXIST_MAIN_COUNT SQL_ORDER_BY_OWNER,
            VIEW_TYPE_MAIN_COUNTS,
            FALSE,
            _T("账户列表"));
    }
}

/*******************************************
    Function Name : 
    author        : Qiu Guohua
    Date          : 2009-5-4 20:33:30
    Description   : open all maincount its bank is strText.
    Return type   : 
    Argument      : 
********************************************/
void CSmallHorseApp::OpenCountsbyBank(CString strText)
{
    CString strFilter;
    if(m_bShowNoExistBook)
    {
        strFilter.Format(SQL_OPEN_MAIN_COUNT_BY_BANK,strText);
    }
    else
    {
        strFilter.Format(SQL_OPEN_EXIST_MAIN_COUNT_BY_BANK,strText);
    }
    
    OpenCountsView(strFilter,VIEW_TYPE_MAIN_COUNTS,FALSE,strText);
}

/*******************************************
    Function Name : 
    author        : Qiu Guohua
    Date          : 2009-5-4 20:34:07
    Description   : open all maincount its owner is strText
    Return type   : 
    Argument      : 
********************************************/
void CSmallHorseApp::OpenCountsbyPeople(CString strText)
{
    CString strFilter;
    if(m_bShowNoExistBook)
    {
        strFilter.Format(SQL_OPEN_MAIN_COUNT_BY_OWNER,strText);
    }
    else
    {
        strFilter.Format(SQL_OPEN_EXIST_MAIN_COUNT_BY_OWNER,strText);
    }
    OpenCountsView(strFilter,VIEW_TYPE_MAIN_COUNTS,FALSE,strText);
}





/*******************************************
    Function Name : 
    author        : Qiu Guohua
    Date          : 2009-5-15 22:51:25
    Description   : 
    Return type  : 
    Argument      : 
********************************************/
COleDateTime CSmallHorseApp::CalEndDate(COleDateTime time, int month)
{
	int newm = month+time.GetMonth();
	int newy = time.GetYear();
	newy += (newm-1)/12;
	newm = (newm)%12;
	if(newm == 0)
	{
		newm = 12;
	}
	COleDateTime timenew;
    int day = time.GetDay();
    int nRet = timenew.SetDate(newy,newm,day);
    while(nRet != 0)
    {//always the last day of the month.
        day--;
        nRet = timenew.SetDate(newy,newm,day);
    }
    
	return timenew;

}


void CSmallHorseApp::GetBankList(CStringList &strBankList)
{
    CDatabase dtbs;
    BOOL b = dtbs.OpenEx(DATA_SOURCE_NAME,CDatabase::openReadOnly|CDatabase::noOdbcDialog);
    CRecordset set(&dtbs);
    
    b = set.Open(CRecordset::snapshot,_T("select Book_Bank from Books  group by Book_Bank"));
    
    if(!set.IsBOF())
    {
        set.MoveFirst();
    }
    while(!set.IsEOF())
    {
        CString strValue;
        set.GetFieldValue((short)0,strValue);
        strBankList.AddTail(strValue);
        set.MoveNext();
    }
    set.Close();
    dtbs.Close();
}

void CSmallHorseApp::GetTypeList(CStringList &strTypeList)
{
    CDatabase dtbs;
    BOOL b = dtbs.OpenEx(DATA_SOURCE_NAME,CDatabase::openReadOnly|CDatabase::noOdbcDialog);
    CRecordset set(&dtbs);
    
    b = set.Open(CRecordset::snapshot,_T("select Book_Type from Books  group by Book_Type"));
    
    if(!set.IsBOF())
    {
        set.MoveFirst();
    }
    while(!set.IsEOF())
    {
        CString strValue;
        set.GetFieldValue((short)0,strValue);
        strTypeList.AddTail(strValue);
        set.MoveNext();
    }
    set.Close();
    dtbs.Close();
}



/*******************************************
    Function Name : 
    author        : Qiu Guohua
    Date          : 2009-6-8 21:12:34
    Description   : 
    Return type  : 
    Argument      : 
********************************************/
BOOL CSmallHorseApp::DeleteBook(const CString &strID)
{

    CIDSet* pIdSet = theApp.GetIDSet();

    CString strmsg;
    strmsg=_T("确定要将帐号为：")+strID+_T("  的存折从数据库中去掉吗？");
    if(MessageBox(NULL,strmsg,_T("请谨慎操作!"),MB_OKCANCEL|MB_ICONWARNING)==IDOK)
    {
        if(pIdSet->MovetoCurID(strID))
        {
            pIdSet->Delete();
            if(pIdSet->Requery())
            {
                strmsg=strID+_T("  已经被成功删除！");
                AfxMessageBox(strmsg);
                return TRUE;
            }
        }
        strmsg=_T("删除 ")+strID+_T("  失败！");
        AfxMessageBox(strmsg);
    }
    return FALSE;
}
BOOL CSmallHorseApp::ShowPopupMenu (UINT uiMenuResId, const CPoint& point, CWnd* pWnd)
{
    if (g_pContextMenuManager == NULL)
    {
        ASSERT (FALSE);
        return FALSE;
    }
    
    ASSERT_VALID (g_pContextMenuManager);
    return g_pContextMenuManager->ShowPopupMenu (uiMenuResId,
        point.x, point.y, pWnd,TRUE);
}

BOOL CSmallHorseApp::ShowPopupMenu (HMENU hMenu, const CPoint& point, CWnd* pWnd)
{
    if (g_pContextMenuManager == NULL)
    {
        ASSERT (FALSE);
        return FALSE;
    }
    
    ASSERT_VALID (g_pContextMenuManager);
    g_pContextMenuManager->ShowPopupMenu (hMenu,
        point.x, point.y, pWnd,TRUE);
	return TRUE;
}


/*******************************************
    Function Name : 
    author        : Qiu Guohua
    Date          : 2009-6-9 22:05:52
    Description   : 
    Return type  : 
    Argument      : 
********************************************/
BOOL CSmallHorseApp::RectifyBookInfo(const CString &strID)
{
    CIDSet* pIdSet = theApp.GetIDSet();
    
    
    if(pIdSet && pIdSet->MovetoCurID(strID))
    {
        CNewBook dlg(pIdSet,FALSE);
        if(dlg.DoModal()==IDOK)
        {
            return TRUE;
        }
    }
    return FALSE;
}




/*******************************************
    Function Name : 
    author        : Qiu Guohua
    Date          : 2009-6-9 22:59:13
    Description   : 
    Return type  : 
    Argument      : 
********************************************/
BOOL CSmallHorseApp::FreeBook(const CString &strID)
{
#ifdef  LOAD_DATEBASE
    CIDSet* pIdSet = theApp.GetIDSet();
    
    if(pIdSet && pIdSet->MovetoCurID(strID))
    {
		pIdSet->RevertExist();
		return TRUE;
// 		
//         pIdSet->Edit();
//         pIdSet->m_bExist=!pIdSet->m_bExist;
//         return pIdSet->Update();
    }
    return FALSE;
#endif
}


/*******************************************
    Function Name : 
    author        : Qiu Guohua
    Date          : 2009-6-13 22:58:27
    Description   : 
    Return type  : 
    Argument      : 
********************************************/
void CSmallHorseApp::SelectPeriod(CComboBox *pCmbBox, int nMonth)
{
    for(int i = 0;i<PEROID_TYPE;i++)
    {
        if(nMonth == gSavePeroid[i].month)
        {
            pCmbBox->SetCurSel(i);
        }
    }
}


/*******************************************
    Function Name : 
    author        : Qiu Guohua
    Date          : 2009-10-10 22:49:43
    Description   : 
    Return type  : 
    Argument      : 
********************************************/
void CSmallHorseApp::ForceUpdateViews()
{
    CListSet* pListSet = theApp.GetListSet();
    if(pListSet != NULL)
    {
        pListSet->Close();
        pListSet->Open();
 //       pListSet->m_strFilter = _T("");
//        pListSet->Requery();
        
        TRACE(_T("pListSet->m_strFilter = _T("");\n"));
    }
        TRACE(_T("update start...;\n"));
    UpdateAllView();
        TRACE(_T("update end...;\n"));
}


#define TRACE_TIME(reason,time) TRACE("%s:%s\n",reason,time.Format("%Y-%m-%d"));



/*******************************************
    Function Name :	 
    Create by     :	  Qiu Simon
    Input         :   
    Output        :   
    Description   :   
    Date          :   Modify 1/6/2011 3:49:18 PM
********************************************/
BOOL CSmallHorseApp::RenewSubCount(const CString &strID, const CString &strSubID)
{
    COleDateTime today;
    today= today.GetCurrentTime();
    int y,m,d;
    y = today.GetYear();
    m = today.GetMonth();
    d = today.GetDay();
    today.SetDate(y,m,d);
    return RenewSubCount(strID,strSubID,today);
}





void CSmallHorseApp::LoadAllSite(CStringArray &arySites)
{
 //   TRACE(_T("列：%s\n"),strColumn);
    CDatabase dtbs;
    BOOL b = dtbs.OpenEx(DATA_SOURCE_NAME,CDatabase::openReadOnly|CDatabase::noOdbcDialog);
    CRecordset set(&dtbs);
    
    b = set.Open(CRecordset::snapshot,SQL_SELECT_ALL_SITE);

  if(set.GetRecordCount()>0)
  {
    CString strTemp;
    arySites.SetSize(0,16);
      set.MoveFirst();
      while(!set.IsEOF())
      {
        set.GetFieldValue((short)0,strTemp);
        arySites.Add(strTemp);
        set.MoveNext();
      }
  }
  set.Close();
  dtbs.Close();
}


/*******************************************
    Function Name :	 
    Create by     :	  Qiu Simon
    Input         :   dbAry , stores all ids we want to delete.
    Output        :   
    Description   :   Delete more than 1 records.
    Date          :   2010-2-11 15:36:44
********************************************/
void CSmallHorseApp::DeleteRecords(const CDWordArray &dbAry)
{
    CString strTip(_T("确定要删除序号为\n"));
    CString strTemp;
    CString strIDs;
#define PER_LINE_NUMBER (10)
    int i=0;
    while(i<dbAry.GetSize())
    {
        strTemp.Format(_T(" %d"),dbAry[i]);
        strTip += strTemp;
        strIDs += strTemp;
        if(i<(dbAry.GetSize()-1))
        {
            strIDs += ",";
        }
        
        i++;
        if(i%PER_LINE_NUMBER == 0)
        {
            strTip += _T("\n");
        }
    }
    strTip += _T("\n的记录吗?");
    if(IDYES == ::MessageBox(NULL,strTip,_T("确认"),MB_YESNO|MB_ICONEXCLAMATION))
    {
        CListSet* pItemSet = GetListSet();
        if(pItemSet->m_pDatabase)
        {
            CString strSql;
            strSql.Format("delete from Items where Index in (%s)",strIDs);
            pItemSet->m_pDatabase->ExecuteSQL(strSql);
            ForceUpdateViews();
        }
        else
        {
            AfxMessageBox("The database is null.");
        }
#if 0 // this database cant update intime.
        CDatabase dtbs;
        BOOL b = dtbs.OpenEx(DATA_SOURCE_NAME,CDatabase::noOdbcDialog|CDatabase::noOdbcDialog);
        if(b)
        {
            
            
            CString strSql;
            strSql.Format("delete from Items where Index in (%s)",strIDs);
            dtbs.ExecuteSQL(strSql);
            dtbs.Close();
            
            ForceUpdateViews();
        }
#endif
    }
}



/*******************************************
    Function Name : 
    author        : Qiu Guohua
    Date          : 2010-2-19 21:36:00
    Description   : 
    Return type   : 
    Argument      : 
********************************************/
void CSmallHorseApp::ModifySubCount(const CString &strId, const CString &strSubId,COleDateTime* pOleDate, float* pvalue)
{
    CDingQiInputDlg dlg;
    dlg.m_bNewItem = FALSE;
    dlg.m_id = strId;
    CSubCountSet* pSubCountSet = GetSubCountSet();
    if(!pSubCountSet->Find(strId,strSubId))
    {
        dlg.m_bModifyMode = TRUE;
        dlg.m_strSubCount = strSubId;
        dlg.m_remain = pSubCountSet->m_Comment;
        //get rate from database, rate field is not needed.
//        dlg.m_fRate =  pSubCountSet->m_Year_Rate;
		
		
		if(pOleDate != NULL)
		{
			dlg.m_date = *pOleDate;
		}
		else
		{
			dlg.m_date = pSubCountSet->m_Start_Date;
		}
		if(pvalue!=NULL)
		{
			dlg.m_sum = *pvalue;
		}
		else
		{
			dlg.m_sum = pSubCountSet->m_BeginValue;
		}
        dlg.m_nMonth = pSubCountSet->m_Time_Span;
        
        if(dlg.DoModal()==IDOK)
        {
            pSubCountSet->AddNew();
            pSubCountSet->m_Count_ID = strId;
            pSubCountSet->m_Sub_Count_ID = strSubId;
            pSubCountSet->m_Comment = dlg.m_remain;
            pSubCountSet->m_Start_Date = dlg.m_date;
            pSubCountSet->m_End_Date = CalEndDate(dlg.m_date, dlg.m_nMonth);
            pSubCountSet->m_Time_Span = dlg.m_nMonth;
            pSubCountSet->m_BeginValue = dlg.m_sum;
            pSubCountSet->m_bExist = TRUE;
            pSubCountSet->Update();
            pSubCountSet->Requery();
            ForceUpdateViews();
        }
        return;
    }
    else
    {
        dlg.m_bModifyMode = TRUE;
        dlg.m_strSubCount = strSubId;
        dlg.m_remain = pSubCountSet->m_Comment;
        dlg.m_date = pSubCountSet->m_Start_Date;
        dlg.m_sum = pSubCountSet->m_BeginValue;
        dlg.m_nMonth = pSubCountSet->m_Time_Span;
        
        if(dlg.DoModal()==IDOK)
        {
			CSubCountSet subSet;
			pSubCountSet->MakeDataCopy(subSet);
			pSubCountSet->Modify(&subSet);
//             pSubCountSet->Edit();
//             pSubCountSet->m_Comment = dlg.m_remain;
//             pSubCountSet->m_Start_Date = dlg.m_date;
//             pSubCountSet->m_End_Date = CalEndDate(dlg.m_date, dlg.m_nMonth);
//             pSubCountSet->m_Time_Span = dlg.m_nMonth;
//             pSubCountSet->m_BeginValue = dlg.m_sum;
//             pSubCountSet->m_bExist = TRUE;
//             pSubCountSet->Update();
//             pSubCountSet->Requery();
            ForceUpdateViews();
        }

    }
}

/*******************************************
    Function Name : 
    author        : Qiu Guohua
    Date          : 2010-3-10 9:20:45
    Description   : 
    Return type   : 
    Argument      : 
********************************************/
void CSmallHorseApp::OpenSubCountbyId(const CString &strId)
{
    CString strSql;
    strSql.Format(SQL_OPEN_ALL_SUB_COUNT_BY_ID SQL_GROUP_SUB_COUNT_WITH_SUM,strId);
    
    OpenCountsView(strSql, \
        VIEW_TYPE_SUB_COUNTS,\
        FALSE,\
        _T("子账户列表"));
}


void CSmallHorseApp::OnUpdateShowNoExistBook(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(m_bShowNoExistBook);
}


/*******************************************
    Function Name :	 
    Create by     :	  Qiu Simon
    Input         :   
    Output        :   
    Description   :   
    Date          :   2010-8-26 16:36:37
********************************************/
void CSmallHorseApp::AddCreditPayInfo(const CString &strID)
{
    CCreditPayDlg dlg;
    dlg.m_strID = strID;
    if(dlg.DoModal()==IDOK)
    {
        CCreditPaySet set;
        set.Open();
        set.AddNew();
        set.m_BookID = strID;
        set.m_Comment = dlg.m_strComment;
        set.m_PaymentDueDate = dlg.m_datePay;
        set.m_StartMonth = dlg.m_EffectYearMonth.GetMonth();
        set.m_StartYear = dlg.m_EffectYearMonth.GetYear();
        set.m_StatementDate = dlg.m_dateStatement;
        set.Update();
    }
}

/*******************************************
    Function Name : 
    author        : Qiu Guohua
    Date          : 2010-10-30 21:50:43
    Description   : 
    Return type   : 
    Argument      : 
********************************************/
int CSmallHorseApp::GetBookType(const CString &strId)
{
    BOOL b = m_IDSet.MovetoCurID(strId);
    if(!b)
    {
        return -1;
    }
    return m_IDSet.m_nType;
}


/*******************************************
    Function Name :	 
    Create by     :	  Qiu Simon
    Input         :   
    Output        :   
    Description   :   
    Date          :   12/14/2010 4:14:42 PM
********************************************/
void CSmallHorseApp::OnQueryComment() 
{
    CQueryFromCommentDlg dlg;
    if(dlg.DoModal()==IDOK)
    {
        CString strSort;
        strSort=_T("OperDate,Index");
        OpenView(dlg.m_strInfo,strSort);
//        OpenView("Comment LIKE '%面粉%'",strSort);
    }
}


/*******************************************
Function Name :	 
Create by     :	  Qiu Simon
Input         :   
Output        :   
Description   :   
Date          :   12/14/2010 4:14:40 PM
********************************************/
void CSmallHorseApp::OnQueryDate() 
{
    CQueryFromDateDlg dlg;
    if(dlg.DoModal()==IDOK)
    {
        CString strSort;
        strSort=_T("OperDate,Index");
        OpenView(dlg.m_strInfo,strSort);
    }
    
}
/*******************************************
Function Name :	 
Create by     :	  Qiu Simon
Input         :   
Output        :   
Description   :   
Date          :   06/26/2018 16:58:40
********************************************/
void CSmallHorseApp::QueryOneDay(COleDateTime day) 
{
	CString strDay = day.Format("%Y-%m-%d");
	CString strInfo;
	strInfo.Format("OperDate BETWEEN #%s 00:00# and  #%s 23:59#",strDay,strDay);

	CString strSort;
	strSort=_T("OperDate,Index");
	OpenView(strInfo,strSort);
}


/*******************************************
    Function Name :	 
    Create by     :	  Qiu Simon
    Input         :   
    Output        :   
    Description   :   
    Date          :   12/14/2010 4:14:37 PM
********************************************/
void CSmallHorseApp::OnQueryMoney() 
{
    CQueryFromMoneyDlg dlg;
    if(dlg.DoModal()==IDOK)
    {
        CString strSort;
        strSort=_T("OperDate,Index");
        OpenView(dlg.m_strInfo,strSort);
        //        OpenView("Oper BETWEEN 3000 and 3001",strSort);
    }
    
}


/*******************************************
    Function Name : 
    author        : Qiu Guohua
    Date          : 2010-12-20 19:58:58
    Description   : 
    Return type   : 
    Argument      : 
********************************************/
BOOL CSmallHorseApp::CloseSubCount(const CString &strMainCount, const CString &strSubCount)
{
    CCloseSubCountDlg dlg;
    if(dlg.DoModal()!=IDOK)
    {
        return FALSE;
    }
    dlg.m_closeDate.m_status = COleDateTime::valid;
    return CloseSubCount(strMainCount,strSubCount,dlg.m_closeDate,dlg.m_bSavetoDefault);
}


/*******************************************
    Function Name : 
    author        : Qiu Guohua
    Date          : 2010-12-20 20:17:36
    Description   : 
    Return type   : 
    Argument      : 
********************************************/
BOOL CSmallHorseApp::IsSubcountActive(const CString &strMainCount, const CString &strSubCount)
{
    CSubCountSet* pset = GetSubCountSet();
    if(pset->Find(strMainCount,strSubCount))
    {
        return pset->m_bExist;
    }
    else
    {
        return FALSE;
    }
    
}


/*******************************************
    Function Name :	 
    Create by     :	  Qiu Simon
    Input         :   
    Output        :   
    Description   :   
    Date          :   12/29/2010 2:57:25 PM
********************************************/
double CSmallHorseApp::GetRate(const COleDateTime &date, int nMonth)
{
    CRateSet* pset = GetRateSet();
    return pset->GetRate(date,nMonth);
}

CRateSet* CSmallHorseApp::GetRateSet()
{
#ifdef  LOAD_DATEBASE
    if(!m_rateSet.IsOpen())
    	m_rateSet.Open();

    return &m_rateSet;
#else
    return NULL;
#endif

}


CTodoSet* CSmallHorseApp::GetTodoSet()
{
    if(!m_TodoSet.IsOpen())
        m_TodoSet.Open();

    return &m_TodoSet;
}

/*******************************************
    Function Name :	 
    Create by     :	  Qiu Simon
    Input         :   
    Output        :   
    Description   :   
    Date          :   1/6/2011 3:42:02 PM
********************************************/
BOOL CSmallHorseApp::CloseSubCount(const CString &strID, const CString &strSubID,const COleDateTime &endDate,BOOL bSavetoDefault)
{
    if(IsAccountLocked(strID))
    {
        return FALSE;
    }
    RenewSubCount(strID,strSubID,endDate);

    CSubCountSet* pset = GetSubCountSet();
    CRateSet* pRateSet = GetRateSet();
    COleDateTime dateEnd;
    COleDateTime dateBegin = pset->m_Start_Date;
    int days = 0;
    float fInterest = 0.0f;
    float fRate = 0.0;
    float fBase = pset->m_BeginValue;
	TRACE("a fBase:%f\n",fBase);
    BOOL bContinue = dateBegin < endDate;
    while(bContinue)
    {
        COleDateTimeSpan span;
        TRACE_TIME("dateBegin",dateBegin);

        fRate = pRateSet->GetDepositRate(dateBegin,dateEnd);
        TRACE_TIME("dateEnd",dateEnd);
        //cal this period.
        if(dateEnd<endDate)
        {
            //will have next period.
            span = dateEnd - dateBegin;
            TRACE_TIME("dateEnd",dateEnd);
            TRACE_TIME("dateBegin",dateBegin);
        }
        else
        {
            //this is the last period.
            span = endDate - dateBegin;
            TRACE_TIME("endDate",endDate);
            TRACE_TIME("dateBegin",dateBegin);
            bContinue = FALSE;
        }
        dateBegin = dateEnd;
        
        days = span.GetDays();
        fInterest += fBase * days / 360.0 * fRate / 100.0;
	    TRACE("b fBase:%f interest :%f \n",fBase,fInterest);
    }
    fBase += fInterest;
    
    
    CListSet* pItemSet = GetListSet();
    if(days > 0)
    {
		CListSet setData;
        setData.m_day=endDate;
        setData.m_ID=strID;
        setData.m_strSubCount = strSubID;
        setData.m_bType=13;//interest
    
        setData.m_addorsub.Format(_T("%f"),fInterest);
        setData.m_remain.Format(_T("Inerest (Smarter Close %.2f)"),fRate);
		pItemSet->New_Item(&setData);
    }
    
//    pItemSet->AddNew();
    CListSet listData;
    listData.m_day=endDate;
    listData.m_ID=strID;
    listData.m_strSubCount = strSubID;
    if(bSavetoDefault)
    {
        listData.m_bType=3;//transfer
    }
    else
    {
        listData.m_bType=-1;//dont know the usage.
    }
    
    listData.m_addorsub.Format(_T("%f"),-fBase);
	TRACE("c fBase:%f\n",fBase);

    listData.m_remain.Format(_T("Inerest (Smarter Close )"));
//    pItemSet->Update();
	pItemSet->New_Item(&listData);
	

    if(bSavetoDefault)
    {
        //transfer to general account. 
//        pItemSet->AddNew();
		CListSet setData;

        
        setData.m_day=endDate;
        setData.m_ID=strID;
        setData.m_strSubCount = _T("");
        setData.m_bType=3;//transfer
        
        setData.m_addorsub.Format(_T("%f"),fBase);
        setData.m_remain.Format(_T("(Smarter Close Sub Count %s)"),strSubID);
 //       pItemSet->Update();
		pItemSet->New_Item(&setData);
    }
    
    pset->SetNoExist();

//     pset->Edit();
//     pset->m_bExist = FALSE;
//     pset->m_BeginValue = 0.00001f;//cant set to 0.0 .so set a very small value.
//     pset->Update();
    return pset->Requery();
}

BOOL CSmallHorseApp::RenewSubCount(const CString &strID, const CString &strSubID, const COleDateTime &endDate)
{
	if(IsAccountLocked(strID))
	{
		return FALSE;
	}
	CSubCountSet* pset = GetSubCountSet();
	BOOL bRet = FALSE;
	if(pset->Find(strID,strSubID))
	{
		if(pset->m_End_Date.m_status!=COleDateTime::valid)
		{
			pset->m_End_Date=CalEndDate(pset->m_Start_Date,pset->m_Time_Span);
		}
		while(pset->m_End_Date <= endDate)
		{
			CListSet* pItemSet = GetListSet();
			CListSet listData;
			//      pItemSet->AddNew();
			listData.m_day=pset->m_End_Date;
			TRACE_TIME("old end date",pset->m_End_Date);
			listData.m_ID=strID;
			listData.m_strSubCount = strSubID;
			listData.m_bType=13;//interest

			//      float fInterset = pset->m_BeginValue * pset->m_Time_Span / 12.0 * pset->m_Year_Rate / 100.0;
			float fRate = theApp.GetRate(pset->m_Start_Date,pset->m_Time_Span);
			float fInterest = pset->m_BeginValue * pset->m_Time_Span / 12.0 * fRate / 100.0;
			//handle interest tax.

			float fInterest8 ,fInterest95, fInterest100;
			int days8 = 0;
			int days95 = 0;
			int days100 = 0;
			COleDateTimeSpan span;
			span = pset->m_End_Date - pset->m_Start_Date;

			int daystotal = span.GetDays();
			if(pset->m_Start_Date < COleDateTime(2007,8,1,0,0,0))
			{
				span = COleDateTime(2007,8,1,0,0,0) - pset->m_Start_Date;

				days8 = span.GetDays();
				if(days8 > daystotal)
				{
					days8 = daystotal;
				}
			}
			if(pset->m_End_Date > COleDateTime(2008,10,9,0,0,0))
			{
				span  = pset->m_End_Date - COleDateTime(2008,10,9,0,0,0);
				days100 = span.GetDays();
				if(days100 > daystotal)
				{
					days100 = daystotal;
				}
			}
			days95 = daystotal - days8 - days100;

			fInterest8 = fInterest * days8 /daystotal;
			fInterest95 = fInterest * days95 /daystotal;
			fInterest100 = fInterest * days100 /daystotal;

			fInterest8 *= 0.8;
			fInterest95 *= 0.95;

			fInterest = fInterest8 + fInterest95+ fInterest100;

			listData.m_addorsub.Format(_T("%f"),fInterest);
			listData.m_remain.Format(_T("Inerest (Smarter Renew %.2f)"),fRate);
			//      pItemSet->Update();
			pItemSet->New_Item(&listData);
// 			pset->Edit();

			CSubCountSet subSet;
			subSet.MakeDataCopy(subSet);
			TRACE_TIME("old start date",subSet.m_Start_Date);
			TRACE_TIME("old END date",subSet.m_End_Date);
			subSet.m_Start_Date = subSet.m_End_Date;
			subSet.m_End_Date = CalEndDate(subSet.m_Start_Date, subSet.m_Time_Span);
			TRACE_TIME("NEW start date",subSet.m_Start_Date);
			TRACE_TIME("NEW END date",subSet.m_End_Date);
			subSet.m_BeginValue += fInterest;
			pset->Modify(&subSet);
			pset->m_Start_Date=subSet.m_Start_Date;
			pset->m_End_Date=subSet.m_End_Date;
			pset->m_BeginValue=subSet.m_BeginValue;

// 			bRet = pset->Update();
		}
	}
	return bRet;

}




/*******************************************
    Function Name :	 
    Create by     :	  Qiu Simon
    Input         :   
    Output        :   
    Description   :   
    Date          :   1/11/2011 4:18:17 PM
********************************************/
BOOL CSmallHorseApp::OpenCompareView()
{
    CCompareFrame* pctestframe=(CCompareFrame*)m_pCompareTemplate->CreateNewFrame(NULL,NULL);
    pctestframe->ActivateFrame(SW_MAXIMIZE);
    
//   m_pCompareTemplate->InitialUpdateFrame(pctestframe, NULL);
    return TRUE;
}

void CSmallHorseApp::OnCompareDatabase() 
{
	    OpenCompareView();
}


/*******************************************
    Function Name : 
    author        : Qiu Guohua
    Date          : 2012-4-1 14:48
    Description   : open credit card report.
    Return type   : 
    Argument      : 
********************************************/
BOOL CSmallHorseApp::OpenReportView(const CString &strID)
{
	CMainFrame* pfrm=(CMainFrame*)AfxGetMainWnd();

	CDocument* pdoc=GetDoc();
	if(pdoc)
	{
		POSITION pos=pdoc->GetFirstViewPosition();
		CView* pview;
		while(pos)
		{
			pview=pdoc->GetNextView(pos);
			CReportFrame* psfrm=(CReportFrame*)pview->GetParent();
			//the view has created activate it.
			if(IS_REPORT(psfrm->m_ViewType ))
			{
				if(strID == psfrm->m_strID)
				{	
					((CFrameWnd*)psfrm)->ActivateFrame();
					return TRUE;
				}
			}
		}
	}
	else
	{
		pdoc= m_pDocTemplate->CreateNewDocument();
	}

	CReportFrame* pcframe=(CReportFrame*)m_pDocTemplate->CreateNewFrame(pdoc,NULL);
    pcframe->SetReportInfo(strID);

    m_pDocTemplate->InitialUpdateFrame(pcframe, pdoc);

	return TRUE;
}


float CSmallHorseApp::GetPay(CListSet* pListSet,const CString &strid, const COleDateTime &timeBegin, const COleDateTime &timeEnd)
{
    if(!pListSet->IsBOF())
    {
        pListSet->MoveFirst();
    }
	
	COleDateTime tBegin(timeBegin.GetYear(),timeBegin.GetMonth(),timeBegin.GetDay(),0,0,0);
	COleDateTime tEnd(timeEnd.GetYear(),timeEnd.GetMonth(),timeEnd.GetDay(),23,59,59);
	
	float fThisPaySum;
	float fUse = 0.0;
	
	while(!pListSet->IsEOF())
	{
		if(pListSet->m_day > tEnd)
		{
			break;
		}
		if(pListSet->m_day >= tBegin)
		{
			fThisPaySum = pListSet->GetAddorSubValue();
			//2014-10-21
			//退款也是正项,所以就判断是否是转存项目,只有还款项才不计入.
//			if(fThisPaySum<0)
			if(pListSet->m_bType != theApp.GetTypeIndex(_T("转存")))
			{
				fUse += fThisPaySum;
			}
		}
		pListSet->MoveNext();
	}
	return fUse;
}
float CSmallHorseApp::GetRepay(CListSet* pListSet,const CString &strid, const COleDateTime &timeBegin)
{
    if(!pListSet->IsBOF())
    {
        pListSet->MoveFirst();
    }

	int y = timeBegin.GetYear();
	int m = timeBegin.GetMonth();

	
	COleDateTime tBegin(y,m,timeBegin.GetDay(),0,0,0);
	m++;
	if(m==13)
	{
		y++;
		m=1;
	}
	//Feb is a special month , it may have 28 or 29 days.
	int d = timeBegin.GetDay();
	if(m == 2 && d > 28)
	{
		d = 29;
		if(y%4!=0 ||(y%100==0 && y%400!=0) )
		{
			d = 28;
		}
	}

	
	COleDateTime tEnd(y,m,d,23,59,59);
	
	float fThisPaySum;
	float fUse = 0.0;
	
	while(!pListSet->IsEOF())
	{
		if(pListSet->m_day > tEnd)
		{
			break;
		}
		if(pListSet->m_day >= tBegin)
		{
			fThisPaySum = pListSet->GetAddorSubValue();
			//2014-10-21
			//退款也是正项,所以就判断是否是转存项目,只有还款项才计入.
			//if(fThisPaySum>0)
			if(pListSet->m_bType == theApp.GetTypeIndex(_T("转存")))
			{
				fUse += fThisPaySum;
			}
		}
		pListSet->MoveNext();
	}
	return fUse;
}


/*******************************************
    Function Name :	 
    Create by     :	  Qiu Simon
    Input         :   
    Output        :   
    Description   :   
    Date          :   5/23/2012 5:03:43 PM
********************************************/
void CSmallHorseApp::LockCount(const CString &strid)
{
    CIDSet * pset = GetIDSet();
    int status = pset->GetEditStatus(strid);
    if(status != -1)
    {
        if(status == 0)
        {
            CString strInfo;
            strInfo.Format("%s 已经锁定了！不需要再次锁定.", strid);
            AfxMessageBox(strInfo);
        }
        else
        {
            if(pset->LockEditStatus(strid))
            {
                CString strInfo;
                strInfo.Format("%s 被成功锁定！", strid);
                AfxMessageBox(strInfo);
            }
            else
            {
                CString strInfo;
                strInfo.Format("%s 没有被锁定！有错误！");
                AfxMessageBox(strInfo);
            }
        }
    }
}



/*******************************************
    Function Name :	 
    Create by     :	  Qiu Simon
    Input         :   
    Output        :   
    Description   :   
    Date          :   5/24/2012 3:23:50 PM
********************************************/
BOOL CSmallHorseApp::SetAutoReturnCreditCard(const CString &strid)
{
    if(IsAccountLocked(strid))
    {
        g_strAutoReturnCreditCard = "";
        return FALSE;
    }
    g_strAutoReturnCreditCard = strid;
    return TRUE;
}



 
void CSmallHorseApp::GetAllOpendCount(CStringList& list)
{
	CDocument * pdoc = GetDoc();
    POSITION pos = pdoc->GetFirstViewPosition(); 
	list.RemoveAll();
	while (pos)
	{
		CView *pView = pdoc->GetNextView(pos); 
		CReportFrame* pfrm = (CReportFrame*)pView->GetParent();
		if(pfrm->m_ViewType == VIEW_TYPE_RECORD_IN_ONE_COUNT)
		{
			TRACE("%s\n",pfrm->m_strID);
			list.AddTail(pfrm->m_strID);
		}
	}
}

void CSmallHorseApp::CopyRecordsTo(const CDWordArray &dbAry, const CString &strCount, const CString &strSubCount, BOOL bTransfer)
{
    CString strTemp;
    CString strIDs;
    int i=0;
    while(i<dbAry.GetSize())
    {
        strTemp.Format(_T(" %d"),dbAry[i]);
        strIDs += strTemp;
        if(i<(dbAry.GetSize()-1))
        {
            strIDs += ",";
        }
        i++;
    }
	CListSet listSet;
	listSet.Open();//select * from Items where 
	listSet.m_strFilter.Format("Index in (%s)",strIDs);
	TRACE("sql:%s\n",listSet.m_strFilter);
	TRACE("copy to %s,%s,%s\n",strCount,strSubCount ,bTransfer?"TRUE":"FALSE");
	listSet.Requery();
	if(!listSet.IsBOF())
	{
		listSet.MoveFirst();
	}
	CListSet* pListSet = GetListSet();
	while (!listSet.IsEOF()) 
	{
	    BOOL bSameMainCount = (listSet.m_ID.Compare(strCount) == 0);
		TRACE("WHAT? %d\n",listSet.m_arraynumber);
		if(bTransfer)
		{
			float value = 0 - listSet.GetAddorSubValue();
			listSet.m_addorsub.Format("%f", value);
			listSet.m_bType = theApp.GetTypeIndex(_T("转存"));
			CString strRemain;
			if(value > 0)
			{
				if(bSameMainCount)
				{
					strRemain.Format("From: %s",listSet.m_strSubCount); 
				}
				else
				{
					strRemain.Format("From: %s",listSet.m_ID);  
					if(listSet.m_strSubCount.GetLength() > 0)
					{
						strRemain+= "(" + listSet.m_strSubCount + ")";
					}
				}
			}
			else
			{
				if(bSameMainCount)
				{
					strRemain.Format("To: %s",listSet.m_strSubCount);  
				}
				else
				{
					strRemain.Format("To: %s",listSet.m_ID);  
					if(listSet.m_strSubCount.GetLength() > 0)
					{
						strRemain+= "(" + strSubCount + ")";
					}
				}
			}
			listSet.m_remain = strRemain;
		}
		listSet.m_strSubCount = strSubCount;
		listSet.m_ID = strCount;
		listSet.m_TimeAdd = COleDateTime::GetCurrentTime();
		listSet.m_TimeModify = COleDateTime::GetCurrentTime();
		pListSet->New_Item(&listSet);
		listSet.MoveNext();
	}
	listSet.Close();
}

void CSmallHorseApp::OnAccountNew()
{

#ifdef  LOAD_DATEBASE
	CIDSet* pIdSet = GetIDSet();
	CNewBook dlg(pIdSet);
	if(dlg.DoModal()!=IDOK)
		return;
	pIdSet->Requery();
	if(!pIdSet->IsBOF())
	{
		pIdSet->MoveFirst();
	}
	BOOL bSuc=FALSE;
	while(!pIdSet->IsEOF())
	{
		if(pIdSet->m_ID==dlg.m_newid)
		{
			bSuc=TRUE;
			break;
		}
		pIdSet->MoveNext();
	}
	if(bSuc!=TRUE)
	{
		return;
	}
	if(m_pMainWnd)
	{
		CBankbookTree* pTree = ((CMainFrame*)m_pMainWnd)->GetBookTree();
		pTree->ReloadAll();
	}
#endif
}

int CSmallHorseApp::StaticDoubtItems(CString& nID)
{
	CListSet* set = GetListSet();
	CString strfil=_T("\'")+nID+_T("\'");
	set->m_strFilter=_T("Item_Book_ID=")+ strfil;
//	set->m_strFilter+=_T(" and Type=\'0\'");
	TRACE(set->m_strFilter);
	TRACE("\n");

//	set->m_strFilter =_T("Item_Book_ID=")+ nID+_T(" and Type=0");// '379 70052992*3'
//	set->m_strFilter ="Type=0";
//	set->m_strFilter ="Item_Book_ID=" + nID;// '379 70052992*3'
	set->Requery();

	set->MoveFirst();
	int nCountAdd = 0;
	int nCountDec = 0;
	float fAdd =0.0;
	float fDec =0.0;
	int nCountTotal = 0;
	while(!set->IsEOF())
	{
		if(set->m_bType == 0)
		{
			float value = set->GetAddorSubValue();
			if(value<0.0000000)
			{
				nCountDec++;
				fDec += value;
			}
			else
			{
				nCountAdd++;
				fAdd += value;
			}
		}
		nCountTotal++;
		set->MoveNext();
	}
	CString strStatic;
	strStatic.Format("ID:%s:\nTotal Item:%d\nIncome: %d items, total value %.2f\n Output: %d items, total value %.2f\n",nID,nCountTotal,nCountAdd,fAdd,nCountDec,fDec);
	TRACE(strStatic);
	AfxMessageBox(strStatic);
	return 0;
}

BOOL CSmallHorseApp::OpenTodoView(void)
{
    CMainFrame* pfrm=(CMainFrame*)AfxGetMainWnd();

    CDocument* pdoc=GetDoc();
    if(pdoc)
    {
        POSITION pos=pdoc->GetFirstViewPosition();
        CView* pview;
        while(pos)
        {
            pview=pdoc->GetNextView(pos);
            CReportFrame* psfrm=(CReportFrame*)pview->GetParent();
            //the view has created activate it.
            if(IS_TODO(psfrm->m_ViewType))
            {
                ((CFrameWnd*)psfrm)->ActivateFrame();
                return TRUE;
            }
        }
    }
    else
    {
        pdoc= m_pDocTemplate->CreateNewDocument();
    }

    CReportFrame* pcframe=(CReportFrame*)m_pDocTemplate->CreateNewFrame(pdoc,NULL);
    pcframe->SetTodoType();

    m_pDocTemplate->InitialUpdateFrame(pcframe, pdoc);
    return TRUE;
}

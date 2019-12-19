// SelFilePage.cpp : implementation file
//

#include "stdafx.h"
#include "..\SmallHorse.h"
#include "ImportListPage.h"
#include "Importsheet.h"
#include "GridHtmlExporter.h"
#include "TableLoader.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CImportListPage property page


extern int nRegionAttr[VALUE_TYPE_number];
extern int nSubCountRegionAttr[VALUE_SUBCOUNT_TYPE_number];




IMPLEMENT_DYNCREATE(CImportListPage, CPropertyPage)

extern TCHAR cSubCountRegionName[VALUE_SUBCOUNT_TYPE_number][FIELD_NAME_LEN];
extern TCHAR cRegion[VALUE_TYPE_number][FIELD_NAME_LEN];

CImportListPage::CImportListPage() : CPropertyPage(CImportListPage::IDD)
{
	ASSERT(FALSE);
	//{{AFX_DATA_INIT(CImportListPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CImportListPage::CImportListPage(CImportSheet* pParent) : CPropertyPage(CImportListPage::IDD)
{
	m_pParent = pParent;
}

CImportListPage::~CImportListPage()
{
}


void CImportListPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CImportListPage)
	DDX_Control(pDX, IDC_LIST_DATA, m_listctrl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CImportListPage, CPropertyPage)
	//{{AFX_MSG_MAP(CImportListPage)
	ON_BN_CLICKED(IDC_MARKALL, OnMarkall)
	ON_BN_CLICKED(IDC_UNMARKALL, OnUnmarkall)
	ON_BN_CLICKED(IDC_MARKSELED, OnMarkseled)
	ON_BN_CLICKED(IDC_UNMARKSELECTED, OnUnmarkselected)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImportListPage message handlers

BOOL CImportListPage::OnSetActive() 
{
	m_pParent->SetWizardButtons(PSWIZB_BACK | PSWIZB_FINISH);
	
	return CPropertyPage::OnSetActive();
}

BOOL CImportListPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	CHeaderCtrl* pHeadCtrl = m_listctrl.GetHeaderCtrl();
	ASSERT(pHeadCtrl->GetSafeHwnd());
	   
	VERIFY( m_qiuheadCtrl.SubclassWindow(pHeadCtrl->GetSafeHwnd()) );
	if(m_pParent->m_nImportType == IMPORT_TYPE_RECORD)
	{
		m_qiuheadCtrl.m_nFieldCount = VALUE_TYPE_number;
		m_qiuheadCtrl.m_pFieldNames = (TCHAR*)cRegion;
	}
	else
	{
		m_qiuheadCtrl.m_nFieldCount = VALUE_SUBCOUNT_TYPE_number;
		m_qiuheadCtrl.m_pFieldNames = (TCHAR*)cSubCountRegionName;
	}

	
	m_listctrl.SetBkColor(RGB(204,255,204));
	m_listctrl.SetTextBkColor(RGB(204,255,204));
	DWORD dwExstyle=m_listctrl.GetExtendedStyle();//GetE
	m_listctrl.SetExtendedStyle(dwExstyle|LVS_EX_CHECKBOXES|LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_ONECLICKACTIVATE);
	
	// build list columns
	if(m_pParent->m_bFromFile)
	{
		ReFill();
	}
	else
	{
		ReFillbyPaste();
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CImportListPage::ReFill()
{
	HWND hwnd = GetSafeHwnd();
	if(hwnd == NULL)
	{
		return;
	}
	CCSVLoader* pLoader = &(m_pParent->m_loader);
	m_listctrl.DeleteAllItems( );
	while(m_listctrl.DeleteColumn(0));
    pLoader->MovetoHead();
	CString strGet;
	NEXT_TYPE type;
	int nGrid = 0;
	
	while(1)
	{
		type = pLoader->GetNextString(strGet);
		m_listctrl.InsertColumn(nGrid,strGet,LVCFMT_CENTER,70);
		if(type == TYPE_LINE)
		{
			break;
		}
		if(type == TYPE_ERROR)
		{
			break;
		}
        nGrid++;
	}
	int nItems = 0;
	while(1)
	{
		type = pLoader->GetNextString(strGet);
		m_listctrl.InsertItem(nItems,strGet);
		nGrid = 1;
		while(1)
		{
			if(type == TYPE_LINE)
			{
				break;
			}
			if(type == TYPE_ERROR)
			{
				break;
			}
			type = pLoader->GetNextString(strGet);
			m_listctrl.SetItemText(nItems,nGrid,strGet);
			nGrid++;
		}
		nItems++;
		if(type == TYPE_END)
		{
			break;
		}
		if(type == TYPE_ERROR)
		{
			break;
		}
	}
}


/*******************************************
    Function Name :	 SaveDataToDataLib
    Create by     :	  Qiu Guohua
    Input         :   
    Output        :   
    Description   :   
    Date          :   2007-1-18 10:41:54
********************************************/
BOOL CImportListPage::SaveDataToDataLib()
{
	if(m_pParent->m_nImportType == IMPORT_TYPE_RECORD)
	{
		int nTypeArry[VALUE_TYPE_number];
		if(!m_qiuheadCtrl.FindType(nTypeArry,nRegionAttr))
			return FALSE;
		int nCount = FindConflict(nTypeArry);
		if(nCount>0)
		{
			//		return FALSE;
		}
		
		return m_pParent->m_pListSet->AddItems(&m_listctrl,nTypeArry,m_pParent->m_strMainCount);
	}
	else
	{
		int nTypeArry[VALUE_SUBCOUNT_TYPE_number];
		if(!m_qiuheadCtrl.FindType(nTypeArry,nSubCountRegionAttr))
			return FALSE;
		int nCount = FindSubCountConflict(nTypeArry);
		if(nCount>0)
		{
			//		return FALSE;
		}
		return m_pParent->m_pSubCountSet->AddItems(&m_listctrl,nTypeArry,m_pParent->m_strMainCount);
	}
}

void CImportListPage::OnMarkall() 
{
	int nItemCount = m_listctrl.GetItemCount();
	for(int i = 0;i<nItemCount;i++)
	{
		m_listctrl.SetCheck(i,TRUE);
	}
}

void CImportListPage::OnUnmarkall() 
{
	int nItemCount = m_listctrl.GetItemCount();
	for(int i = 0;i<nItemCount;i++)
	{
		m_listctrl.SetCheck(i,FALSE);
	}
}

void CImportListPage::OnMarkseled() 
{
	POSITION pos = m_listctrl.GetFirstSelectedItemPosition();
	while(pos)
	{
		int n = m_listctrl.GetNextSelectedItem(pos);
		m_listctrl.SetCheck(n,TRUE);
	}
}

void CImportListPage::OnUnmarkselected() 
{
	POSITION pos = m_listctrl.GetFirstSelectedItemPosition();
	while(pos)
	{
		int n = m_listctrl.GetNextSelectedItem(pos);
		m_listctrl.SetCheck(n,FALSE);
	}
}


int CImportListPage::FindSubCountConflict(int nType[])
{
	CString strSubCount;
	CGridHtmlExporter exporter;
	CString strFile(_T("C:\\bank.htm"));
	exporter.SetExportFile(strFile);
	int nConflictCount = 0;
	int nCount = m_listctrl.GetItemCount();
	m_listctrl.SetRedraw(FALSE);
	for(int i = 0;i<nCount;i++)
	{
		if(m_listctrl.GetCheck(i))
		{
			strSubCount = m_listctrl.GetItemText(i,nType[VALUE_SUBCOUNT_TYPE_SUBCOUNT]);
			if(m_pParent->m_pSubCountSet->Find(m_pParent->m_strMainCount,strSubCount))
			{
				nConflictCount++;
				exporter.ExportLine(m_pParent->m_strMainCount,strSubCount,"test",0x65ee89);
				m_listctrl.SetCheck(i,FALSE);
			}
		}
	}
	CString strRemain;
	strRemain.Format(_T("总共有%d项冲突."),nConflictCount);
	exporter.ExportLine("","",strRemain,0x45dd45);
	m_listctrl.SetRedraw(TRUE);
	exporter.ExportTail();
	exporter.CloseFile();
	ShellExecute( AfxGetMainWnd()->m_hWnd, "open", strFile, NULL, NULL, SW_SHOWNORMAL );
	return nConflictCount;
}

int CImportListPage::FindConflict(int nType[5])
{
	//begin
	COleDateTime day;
	float fIncome;
	CString strRemain,strDate,strAdd,strDec,strSubCount;
	int nYear,nMonth,nDay,nHh, nMm, nSs;
	CGridHtmlExporter exporter;
	CString strFile(_T("C:\\bank.htm"));
	exporter.SetExportFile(strFile);
	int nConflictCount = 0;
	int nCount = m_listctrl.GetItemCount();
	m_listctrl.SetRedraw(FALSE);
	for(int i = 0;i<nCount;i++)
	{
		if(m_listctrl.GetCheck(i))
		{
			if(nType[VALUE_TYPE_DATE]>=0)
			{
				strDate = m_listctrl.GetItemText(i,nType[VALUE_TYPE_DATE]);
				nHh = 0;
				nMm = 0;
				nSs = 0;
				int ret = theApp.GetDate(strDate,nYear,nMonth,nDay,nHh, nMm, nSs);
				if(ret == 0)
				{
					CString msg;
					msg.Format("Below format cant be read:\n %s",strDate);

					AfxMessageBox(msg);
				}
//				_stscanf(strDate,_T("%d-%d-%d"),&nYear,&nMonth,&nDay);
				day = COleDateTime(nYear,nMonth,nDay,nHh,nMm,nSs);
			}
			fIncome = 0.0;
			strAdd = _T("");
            TCHAR* pTempTchar;
			if(nType[VALUE_TYPE_INCOME]>=0)
			{
				strAdd = m_listctrl.GetItemText(i,nType[VALUE_TYPE_INCOME]);
				if(strAdd.Remove(','))
				{
					TRACE("%s",strAdd);
				}
				strAdd.Remove(' ');
				fIncome = _tcstod(strAdd,&pTempTchar);
			}
			if(nType[VALUE_TYPE_PAY]>=0 && ((fIncome - 0.0)<0.001&&(fIncome - 0.0)>-0.001))
			{
				strDec = m_listctrl.GetItemText(i,nType[VALUE_TYPE_PAY]);
				if(strDec.Remove(','))
				{
					TRACE(_T("%s"),strDec);
				}
				strDec.Remove(' ');
				strDec.Insert(0,_T("-"));
				strAdd = strDec;//for output.
				fIncome += _tcstod(strDec,&pTempTchar);
			}
            if(nType[VALUE_TYPE_SUBCOUNT]>=0)
            {
                strSubCount = m_listctrl.GetItemText(i,nType[VALUE_TYPE_SUBCOUNT]);
            }
            if(m_pParent->m_pListSet->Find(day,fIncome,strSubCount))
			{
				nConflictCount++;
				if(nType[VALUE_TYPE_COMMENT]>=0)
				{
					strRemain = m_listctrl.GetItemText(i,nType[VALUE_TYPE_COMMENT]);
				}
				exporter.ExportLine(strDate,strAdd,strRemain,0x65ee89);
				exporter.ExportLine(m_pParent->m_pListSet->GetDate(),m_pParent->m_pListSet->m_addorsub,m_pParent->m_pListSet->m_remain,0x99ff89);
				m_listctrl.SetCheck(i,FALSE);
			}
		}
	}
	strRemain.Format(_T("总共有%d项冲突."),nConflictCount);
	exporter.ExportLine("","",strRemain,0x45dd45);
	m_listctrl.SetRedraw(TRUE);
	exporter.ExportTail();
	exporter.CloseFile();
	ShellExecute( AfxGetMainWnd()->m_hWnd,_T( "open"), strFile, NULL, NULL, SW_SHOWNORMAL );
	return nConflictCount;
	//end
}

void CImportListPage::ReFillbyPaste()
{
	CTableLoader loader;
	bool b = loader.GetClipboardTable();
	if(!b)
	{
		return;
	}
	loader.FillListCtrl(&m_listctrl);
}

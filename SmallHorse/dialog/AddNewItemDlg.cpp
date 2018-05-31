// AddNewItemDlg.cpp : implementation file
//

#include "stdafx.h"
#include "..\SmallHorse.h"
#include "AddNewItemDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAddNewItemDlg dialog

extern CSmallHorseApp theApp;
CAddNewItemDlg::CAddNewItemDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAddNewItemDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAddNewItemDlg)
	m_date = COleDateTime::GetCurrentTime();
	m_sum = _T("");
	m_id = _T("");
	m_remain = _T("");
	m_nType = 0;
	m_strSubCount = _T("");
	m_strSite = _T("");
	//}}AFX_DATA_INIT
	bgonext=FALSE;
	m_bnewbook=FALSE;
	m_bNewItem=TRUE;
}


void CAddNewItemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAddNewItemDlg)
	DDX_Control(pDX, IDC_COMBO_SUB_COUNT, m_cmbSubCount);
	DDX_Control(pDX, IDC_COMBO_TYPE, m_cmbType);
	DDX_Control(pDX, IDC_EDIT_MONEY, m_money);
	DDX_Control(pDX, IDC_DATETIMEPICKER, m_wndDateTimePicker);
	DDX_Text(pDX, IDC_EDIT_MONEY, m_sum);
	DDX_Text(pDX, IDC_EDIT_ID, m_id);
	DDX_Text(pDX, IDC_REMAIN, m_remain);
	DDX_CBIndex(pDX, IDC_COMBO_TYPE, m_nType);
	DDX_CBString(pDX, IDC_COMBO_SUB_COUNT, m_strSubCount);
	DDX_CBString(pDX, IDC_COMBO_SITE, m_strSite);
	DDV_MaxChars(pDX, m_strSite, 128);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAddNewItemDlg, CDialog)
	//{{AFX_MSG_MAP(CAddNewItemDlg)
	ON_BN_CLICKED(IDC_NEXTINPUT, OnNextinput)
	ON_BN_CLICKED(IDOK, OnYES)
	ON_BN_CLICKED(IDC_ADD_DEFAULT_NOTE, OnAddDefaultNotes)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAddNewItemDlg message handlers

void CAddNewItemDlg::OnNextinput() 
{
	bgonext=TRUE;
	UpdateData();
	EndDialog(IDOK);
}

void CAddNewItemDlg::OnYES() 
{
	bgonext=FALSE;
	UpdateData();
	EndDialog(IDOK);
}

void CAddNewItemDlg::OnAddDefaultNotes() 
{
	UpdateData();
	m_remain = "ÓÐÆ± "+m_remain;
	UpdateData(FALSE);
}

void CAddNewItemDlg::OnCancel() 
{
	bgonext=FALSE;
	EndDialog(IDCANCEL);
}

BOOL CAddNewItemDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	if(m_bnewbook)
		GetDlgItem(IDCANCEL)->EnableWindow(FALSE);
	if(!m_bNewItem)
	{
		GetDlgItem(IDC_NEXTINPUT)->EnableWindow(FALSE);
	}
	for(int i=0;i<256;i++)
	{
		if(_tcslen(theApp.m_cType[i])>0)
			m_cmbType.InsertString(i,theApp.m_cType[i]);
		else
			break;
	}
	m_cmbType.SetCurSel(m_nType);
	CSubCountSet* pSubCount = theApp.GetSubCountSet();
	pSubCount->RequeryCount(m_id);
	if(pSubCount->GetRecordCount()>0)
	{
		pSubCount->MoveFirst();
		while(!pSubCount->IsEOF())
		{
			m_cmbSubCount.AddString(pSubCount->m_Sub_Count_ID);
			pSubCount->MoveNext();
		}
	}

	
	const UINT stateMask = 
		CBCGPDateTimeCtrl::DTM_SPIN |
		CBCGPDateTimeCtrl::DTM_DROPCALENDAR | 
		CBCGPDateTimeCtrl::DTM_DATE |
		CBCGPDateTimeCtrl::DTM_TIME24H |
		CBCGPDateTimeCtrl::DTM_CHECKBOX |
		CBCGPDateTimeCtrl::DTM_TIME | 
		CBCGPDateTimeCtrl::DTM_TIME24HBYLOCALE;
    m_wndDateTimePicker.SetState (CBCGPDateTimeCtrl::DTM_SPIN |CBCGPDateTimeCtrl::DTM_DROPCALENDAR |CBCGPDateTimeCtrl::DTM_DATE, stateMask);
	m_wndDateTimePicker.SizeToContent();
	UpdateData(FALSE);
  m_cmbSite.Init(GetDlgItem(IDC_COMBO_SITE));
  //Simon theApp.LoadAllSite(m_cmbSite.GetStringList());




	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CAddNewItemDlg::UpdateData(BOOL bSaveAndValidate)
{
	CDialog::UpdateData(bSaveAndValidate);
	if(bSaveAndValidate)
	{
		COleDateTime newDate = m_wndDateTimePicker.GetDate();
		//Only the date change, will set to a new date. otherwise the time will disappear.
/**** Add by Qiu Guohua on 2018-05-09 15:42:53 **********************/
		if(m_date.GetDay() == newDate.GetDay() && m_date.GetMonth() == newDate.GetMonth() && m_date.GetYear() == newDate.GetYear())
/**************************2018-05-09 15:42:53 **********************/
		{
			CString strTrace = m_date.Format();
			TRACE(strTrace);
			TRACE(_T("No changed.\n"));
		}
		else
		{
			m_date.SetDateTime(newDate.GetYear() ,newDate.GetMonth() ,newDate.GetDay(),m_date.GetHour(),m_date.GetMinute(),m_date.GetSecond());
		}
	}
	else
	{
		m_wndDateTimePicker.SetDate(m_date);
	}
	return TRUE;
}




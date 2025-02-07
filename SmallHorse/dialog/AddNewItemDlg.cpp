// AddNewItemDlg.cpp : implementation file
//

#include "stdafx.h"
#include "..\SmallHorse.h"
#include "AddNewItemDlg.h"
#include "SubCountInOneCountSet.h"

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
	m_pSet = NULL;
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
	SubmitData();
	EndDialog(IDOK);
}

void CAddNewItemDlg::OnYES() 
{
	bgonext=FALSE;
	UpdateData();
	SubmitData();
	EndDialog(IDOK);
}

void CAddNewItemDlg::OnAddDefaultNotes() 
{
	UpdateData();
	m_remain = "有票 "+m_remain;
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

	CSubCountInOneCountSet sub_set(this->m_id);
	
	if(!sub_set.Open())
	{
		AfxMessageBox(_T("sub_set 数据库装载错误(type)!"));
		return FALSE;
	};
	sub_set.Requery();
	if (sub_set.GetRecordCount() > 0)
	{
		sub_set.MoveFirst();
		while (!sub_set.IsEOF())
		{
			TRACE("subid:%s \n", sub_set.m_Sub_Count_ID);
			m_cmbSubCount.AddString(sub_set.m_Sub_Count_ID);
			sub_set.MoveNext();
		}
	}
	sub_set.Close();

#if 0 //replaced by CSubCountInOneCountSet which list all subid name.
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
#endif
	
	const UINT stateMask = 
		CBCGPDateTimeCtrl::DTM_SPIN |
		CBCGPDateTimeCtrl::DTM_DROPCALENDAR | 
		CBCGPDateTimeCtrl::DTM_DATE |
		CBCGPDateTimeCtrl::DTM_TIME24H |
		CBCGPDateTimeCtrl::DTM_CHECKBOX |
		CBCGPDateTimeCtrl::DTM_TIME | 
		CBCGPDateTimeCtrl::DTM_TIME24HBYLOCALE;
    m_wndDateTimePicker.SetState (CBCGPDateTimeCtrl::DTM_SPIN |CBCGPDateTimeCtrl::DTM_DROPCALENDAR |CBCGPDateTimeCtrl::DTM_TIME24H |CBCGPDateTimeCtrl::DTM_DATE | CBCGPDateTimeCtrl::DTM_TIME, stateMask);
	m_wndDateTimePicker.SizeToContent();
	UpdateData(FALSE);
  m_cmbSite.Init(GetDlgItem(IDC_COMBO_SITE));
  theApp.LoadAllSite(m_cmbSite.GetStringList());




	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CAddNewItemDlg::UpdateData(BOOL bSaveAndValidate)
{
	CDialog::UpdateData(bSaveAndValidate);
	if(bSaveAndValidate)
	{
        m_date = m_wndDateTimePicker.GetDate();
	}
	else
	{
		m_wndDateTimePicker.SetDate(m_date);
	}
	return TRUE;
}



int CAddNewItemDlg::SubmitData()
{
#ifdef SUBMIT_DATA_IN_DIALOG
	if (m_pSet) 
	{
		m_pSet->AddNew();
		m_pSet->m_ID = m_id;
		m_pSet->m_day = m_date;
		m_pSet->m_addorsub = m_sum;
		m_pSet->m_remain = m_remain;
		m_pSet->m_bType = m_nType;
		m_pSet->m_strSite = m_strSite;
		m_pSet->m_strSubCount = m_strSubCount;
		int ret = m_pSet->SubmitNew();
		if (ret)
		{
			::MessageBox(this->GetSafeHwnd(), "提交失败！", "EditPaste Mode", MB_OK);
		}

	}
#endif
	return 0;
}

// DingQiInputDlg.cpp : implementation file
//

#include "stdafx.h"
#include "..\SmallHorse.h"
#include "DingQiInputDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDingQiInputDlg dialog


CDingQiInputDlg::CDingQiInputDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDingQiInputDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDingQiInputDlg)
	m_date = COleDateTime::GetCurrentTime();
	m_id = _T("");
	m_remain = _T("");
	m_nSpan = 0;
	m_strSubCount = _T("");
	m_sum = 0.0f;
	m_bNewSave = 0;
	//}}AFX_DATA_INIT
	bgonext=FALSE;
	m_bnewbook=FALSE;
	m_bNewItem=TRUE;
    m_bModifyMode = FALSE;
}


void CDingQiInputDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDingQiInputDlg)
	DDX_Control(pDX, IDC_EDIT_SUBCOUNT, m_editSubCount);
	DDX_Control(pDX, IDC_COMBO_TIMESPAN, m_cmbSpan);
	DDX_Control(pDX, IDC_EDIT_MONEY, m_money);
	DDX_Control(pDX, IDC_DATETIMEPICKER, m_wndDateTimePicker);
	DDX_Text(pDX, IDC_EDIT_ID, m_id);
	DDX_Text(pDX, IDC_REMAIN, m_remain);
	DDX_CBIndex(pDX, IDC_COMBO_TIMESPAN, m_nSpan);
	DDX_Text(pDX, IDC_EDIT_SUBCOUNT, m_strSubCount);
	DDX_Text(pDX, IDC_EDIT_MONEY, m_sum);
	DDV_MinMaxFloat(pDX, m_sum, 0.f, 1.e+010f);
	DDX_Radio(pDX, IDC_RADIO_TRANSFER, m_bNewSave);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDingQiInputDlg, CDialog)
	//{{AFX_MSG_MAP(CDingQiInputDlg)
	ON_BN_CLICKED(IDC_NEXTINPUT, OnNextinput)
	ON_BN_CLICKED(IDOK, OnYES)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDingQiInputDlg message handlers

void CDingQiInputDlg::OnNextinput() 
{
	bgonext=TRUE;
	if(UpdateData())
	{
		EndDialog(IDOK);
	}
}

void CDingQiInputDlg::OnYES() 
{
	bgonext=FALSE;
	if(UpdateData())
	{
		EndDialog(IDOK);
	}
}

void CDingQiInputDlg::OnCancel() 
{
	bgonext=FALSE;
	EndDialog(IDCANCEL);
}

BOOL CDingQiInputDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	theApp.FillPeriodtoCombox(&m_cmbSpan);
	m_cmbSpan.SetCurSel(1);

    if(!m_bNewItem)
    {
        GetDlgItem(IDC_RADIO_TRANSFER)->EnableWindow(FALSE);
        GetDlgItem(IDC_RADIO_NEW_SAVE)->EnableWindow(FALSE);
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

    if(m_bModifyMode)
    {
        m_editSubCount.EnableWindow(FALSE);
    }
    UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


BOOL CDingQiInputDlg::UpdateData(BOOL bSaveAndValidate)
{
	CDialog::UpdateData(bSaveAndValidate);
	if(bSaveAndValidate)
	{
		int n = m_cmbSpan.GetCurSel();
		{
			if(n == -1)
			{
				AfxMessageBox(_T("必须添存期!"));
				return FALSE;
			}
			m_nMonth = m_cmbSpan.GetItemData(n);
		}
		if(m_sum <= 0.0)
		{
			AfxMessageBox(_T("金额要大于0!"));
			return FALSE;
		}
		if(m_strSubCount == _T(""))
		{
			AfxMessageBox(_T("请输入子账号!"));
			return FALSE;
		}
        //get rate from database, rate field is not needed.
#if 0
		if(m_fRate <= 0.0)
		{
			if(IDYES != ::MessageBox(NULL,_T("利率不大于0，要继续吗？"),_T("确认"),MB_YESNO|MB_ICONEXCLAMATION))
			{
				return FALSE;
			}
		}
#endif		
		m_date = m_wndDateTimePicker.GetDate();
		CString strTrace = m_date.Format();
		TRACE(strTrace);
		TRACE(_T("\n"));
	}
	else
	{
        theApp.SelectPeriod(&m_cmbSpan,m_nMonth);
        
		m_wndDateTimePicker.SetDate(m_date);
	}
	return TRUE;

}

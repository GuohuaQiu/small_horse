// CFixedDepositManagerDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "SmallHorse.h"
#include "CFixedDepositManagerDlg.h"
#include "afxdialogex.h"


// CFixedDepositManagerDlg 对话框

IMPLEMENT_DYNAMIC(CFixedDepositManagerDlg, CDialogEx)

CFixedDepositManagerDlg::CFixedDepositManagerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DINGQI_MANAGER_DIALOG, pParent)
    , m_strBank(_T(""))
    , m_fRate(0)
    , m_strComment(_T(""))
    , m_strId(_T(""))
    , m_fValue(0)
    , m_strOwner(_T(""))
    , m_strSubCount(_T(""))
    , m_strTimeSpan(_T(""))
{

}

CFixedDepositManagerDlg::~CFixedDepositManagerDlg()
{
}

void CFixedDepositManagerDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT_BANK, m_strBank);
    DDX_Text(pDX, IDC_EDIT_ID, m_strId);
    DDX_Text(pDX, IDC_EDIT_OWNER, m_strOwner);
    DDX_Text(pDX, IDC_EDIT_COMMENT, m_strComment);
    DDX_Text(pDX, IDC_EDIT_MONEY, m_fValue);
    DDX_Text(pDX, IDC_EDIT_SUBCOUNT, m_strSubCount);
    DDX_Text(pDX, IDC_EDIT_RATE, m_fRate);
    DDX_Control(pDX, IDC_COMBO_TIMESPAN, m_cmbSpan);
    DDX_Control(pDX, IDC_DATETIMEPICKER_START, m_wndDateTimeStart);
    DDX_Control(pDX, IDC_DATETIMEPICKER_END, m_wndDateTimeEnd);
    DDX_CBString(pDX, IDC_COMBO_TIMESPAN, m_strTimeSpan);
}
BOOL CFixedDepositManagerDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    const UINT stateMask =
        CBCGPDateTimeCtrl::DTM_SPIN |
        CBCGPDateTimeCtrl::DTM_DROPCALENDAR |
        CBCGPDateTimeCtrl::DTM_DATE |
        CBCGPDateTimeCtrl::DTM_TIME24H |
        CBCGPDateTimeCtrl::DTM_CHECKBOX |
        CBCGPDateTimeCtrl::DTM_TIME |
        CBCGPDateTimeCtrl::DTM_TIME24HBYLOCALE;
    m_wndDateTimeStart.SetState(CBCGPDateTimeCtrl::DTM_SPIN | CBCGPDateTimeCtrl::DTM_DROPCALENDAR | CBCGPDateTimeCtrl::DTM_TIME24H | CBCGPDateTimeCtrl::DTM_DATE | CBCGPDateTimeCtrl::DTM_TIME, stateMask);
    m_wndDateTimeEnd.SetState(CBCGPDateTimeCtrl::DTM_SPIN | CBCGPDateTimeCtrl::DTM_DROPCALENDAR | CBCGPDateTimeCtrl::DTM_TIME24H | CBCGPDateTimeCtrl::DTM_DATE | CBCGPDateTimeCtrl::DTM_TIME, stateMask);

    m_wndDateTimeEnd.SizeToContent();
    m_wndDateTimeStart.SizeToContent();
    m_wndDateTimeStart.SetDate(m_dateStart);
    m_wndDateTimeEnd.SetDate(m_dateEnd);
    UpdateData(FALSE);
    // TODO: Add extra initialization here

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}


BEGIN_MESSAGE_MAP(CFixedDepositManagerDlg, CDialogEx)
    ON_CBN_SELCHANGE(IDC_COMBO_TIMESPAN, &CFixedDepositManagerDlg::OnSelchangeComboTimespan)
    ON_BN_CLICKED(IDOK, &CFixedDepositManagerDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CFixedDepositManagerDlg 消息处理程序


void CFixedDepositManagerDlg::OnSelchangeComboTimespan()
{
    int index = m_cmbSpan.GetCurSel();
    int months[] = { 3,6,12,24,36,60 };
    int MonthDay[] = { 31,28,31,30 ,31,30 ,31 ,31,30 ,31,30,31 };
    int y = m_dateStart.GetYear();
    int m = m_dateStart.GetMonth();
    int d = m_dateStart.GetDay();
    m += months[index] - 1;
    int ay = m / 12;
    int am = m % 12 + 1;
    //if (am == 0) {
    //    am = 12;
    //}
    if (am == 2) {
        if (y % 4 == 0) {
            MonthDay[1] = 29;
        }
    }
    if (d > MonthDay[am - 1]) {
        d = MonthDay[am - 1];
    }

    m_dateEnd.SetDateTime(y + ay, am, d, m_dateStart.GetHour(), m_dateStart.GetMinute(), m_dateStart.GetSecond() );
    m_wndDateTimeEnd.SetDate(m_dateEnd);
}


void CFixedDepositManagerDlg::OnBnClickedOk()
{
    m_dateEnd = m_wndDateTimeEnd.GetDate();
    TRACE("m_dateEnd.GetYear() YEAR:%d\n", m_dateEnd.GetYear());
    
    m_dateStart = m_wndDateTimeStart.GetDate();
    // TODO: 在此添加控件通知处理程序代码
    CDialogEx::OnOK();
}

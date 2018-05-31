// QueryFromMoneyDlg.cpp : implementation file
//

#include "stdafx.h"
#include "..\SmallHorse.h"
#include "QueryFromMoneyDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CQueryFromMoneyDlg dialog


CQueryFromMoneyDlg::CQueryFromMoneyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CQueryFromMoneyDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CQueryFromMoneyDlg)
	m_bGreat = FALSE;
	m_bSmall = FALSE;
	m_nSmall = 0;
	m_nGreat = 0;
	m_bOr = 0;
	m_bSmallRange = 1;
	m_fRange = 1;
	m_strInfo = _T("");
	m_fBase = 0;
	//}}AFX_DATA_INIT
    m_bValid = FALSE;
}


void CQueryFromMoneyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CQueryFromMoneyDlg)
	DDX_Control(pDX, IDC_SPIN, m_spinRange);
	DDX_Control(pDX, IDC_EDIT_MONEY_RANGE, m_editRange);
	DDX_Control(pDX, IDC_EDIT_SMALL, m_ctrlEditSmall);
	DDX_Control(pDX, IDC_EDIT_GREAT, m_ctrlEditGreat);
	DDX_Control(pDX, IDC_CHECK_SMALL, m_ctrlCheckSmall);
	DDX_Control(pDX, IDC_CHECK_GREAT, m_ctrlCheckGreat);
	DDX_Radio(pDX, IDC_RADIO_RANGE_FREE, m_bSmallRange);
	//}}AFX_DATA_MAP

    //below modification is for the case when input only a "-", the prompt "Please enter a number."
    //2012.05.08
    if(m_bSmallRange)
    {
        if (pDX->m_bSaveAndValidate)
        {
            HWND hWndCtrl = pDX->PrepareEditCtrl(IDC_EDIT_EQUAL);
            TCHAR szBuffer[32];
            ::GetWindowText(hWndCtrl, szBuffer, 32);
            if((_tcslen(szBuffer) == 1 && szBuffer[0] == _T('-'))|| _tcslen(szBuffer) == 0)
            {
                m_fBase = 0;
            }
            else
            {
                DDX_Text(pDX, IDC_EDIT_EQUAL, m_fBase);
            }
            DDX_Text(pDX, IDC_EDIT_MONEY_RANGE, m_fRange);
        }
    }
    else
    {
        DDX_Check(pDX, IDC_CHECK_GREAT, m_bGreat);
        DDX_Check(pDX, IDC_CHECK_SMALL, m_bSmall);
        DDX_Text(pDX, IDC_EDIT_SMALL, m_nSmall);
        DDX_Text(pDX, IDC_EDIT_GREAT, m_nGreat);
        DDX_Radio(pDX, IDC_RADIO_AND, m_bOr);
    }
    if(!pDX->m_bSaveAndValidate)
    {
        DDX_Text(pDX, IDC_EDIT_INFO, m_strInfo);
    }
}


BEGIN_MESSAGE_MAP(CQueryFromMoneyDlg, CDialog)
	//{{AFX_MSG_MAP(CQueryFromMoneyDlg)
	ON_BN_CLICKED(IDC_CHECK_GREAT, OnCheckGreat)
	ON_BN_CLICKED(IDC_CHECK_SMALL, OnCheckSmall)
	ON_BN_CLICKED(IDC_RADIO_AND, OnRadioAnd)
	ON_BN_CLICKED(IDC_RADIO_OR, OnRadioOr)
	ON_BN_CLICKED(IDC_RADIO_RANGE_SIMPLE, OnRadioRangeSimple)
	ON_BN_CLICKED(IDC_RADIO_RANGE_FREE, OnRadioRangeFree)
	ON_EN_CHANGE(IDC_EDIT_EQUAL, OnChangeEditEqual)
	ON_EN_CHANGE(IDC_EDIT_MONEY_RANGE, OnChangeEditMoneyRange)
	ON_EN_CHANGE(IDC_EDIT_GREAT, OnChangeEditGreat)
	ON_EN_CHANGE(IDC_EDIT_SMALL, OnChangeEditSmall)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CQueryFromMoneyDlg message handlers

void CQueryFromMoneyDlg::OnCheckGreat() 
{
    if(!m_bSmallRange)
    {
        RefreshInfo();
    }
}

void CQueryFromMoneyDlg::OnCheckSmall() 
{
    if(!m_bSmallRange)
    {
        RefreshInfo();
    }
}

void CQueryFromMoneyDlg::OnRadioAnd() 
{
    if(!m_bSmallRange)
    {
        RefreshInfo();
    }
}

void CQueryFromMoneyDlg::OnRadioOr() 
{
    if(!m_bSmallRange)
    {
        RefreshInfo();
    }
}

void CQueryFromMoneyDlg::OnOK() 
{
    EndDialog(IDOK);
}


void CQueryFromMoneyDlg::OnRadioRangeSimple() 
{
    RefreshInfo();
	// TODO: Add your control notification handler code here
	
}

void CQueryFromMoneyDlg::OnRadioRangeFree() 
{
    RefreshInfo();
}

BOOL CQueryFromMoneyDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_spinRange.SetBuddy(&m_editRange);
   m_spinRange.SetRange(0, 100);
   m_spinRange.SetBase(10);
   m_spinRange.SetPos(1);



	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CQueryFromMoneyDlg::RefreshInfo()
{
    UpdateData();
    m_bValid = TRUE;
    if(!m_bSmallRange)
    {
        if(!m_bGreat && !m_bSmall)
        {
            m_bValid = FALSE;
            
            m_strInfo = ("无查询条件，请设置！");
        }
        else if(m_bGreat && m_bSmall)
        {
            if(m_bOr)
            {
                if(m_nSmall>=m_nGreat)
                {
                    m_bValid = FALSE;
                    m_strInfo = ("条件设置重叠，将列出所有记录！请重设！");
                }
                else
                {
                    m_strInfo.Format("Oper >= %d or Oper <= %d",m_nGreat,m_nSmall);
                }
            }
            else
            {
                if(m_nGreat > m_nSmall)
                {
                    m_bValid = FALSE;
                    m_strInfo = ("条件有误，无法满足！");
                }
                else
                {
                    m_strInfo.Format("Oper BETWEEN %d and %d",m_nSmall,m_nGreat);
                }
            }
        }
        else if(m_bGreat)
        {
            m_strInfo.Format("Oper >= %d ",m_nGreat);
        }
        else
        {
            m_strInfo.Format("Oper <= %d ",m_nSmall);
        }
    }
    else
    {
        m_strInfo.Format("Oper BETWEEN %d and %d",m_fBase-m_fRange,m_fBase+m_fRange);
    }
    UpdateData(FALSE);
    GetDlgItem(IDOK)->EnableWindow(m_bValid);
}

void CQueryFromMoneyDlg::OnChangeEditEqual() 
{
    if(m_bSmallRange)
    {
        RefreshInfo();
    }
}

void CQueryFromMoneyDlg::OnChangeEditMoneyRange() 
{
    if(m_bSmallRange)
    {
        RefreshInfo();
    }
}

void CQueryFromMoneyDlg::OnChangeEditGreat() 
{
    if(!m_bSmallRange)
    {
        RefreshInfo();
    }
}

void CQueryFromMoneyDlg::OnChangeEditSmall() 
{
    if(!m_bSmallRange)
    {
        RefreshInfo();
    }
}

// NewBook.cpp : implementation file
//

#include "stdafx.h"
#include "..\SmallHorse.h"
#include "NewBook.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNewBook dialog


CNewBook::CNewBook(CIDSet* pIDSet,BOOL bModeNew/* = TRUE*/,CWnd* pParent /*=NULL*/)
	: CDialog(CNewBook::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNewBook)
	m_newcomit = _T("");
	m_newbank = _T("");
	m_newname = _T("");
	m_newid = _T("");
	//}}AFX_DATA_INIT
    m_bModeNew = bModeNew;
    m_pIDSet = pIDSet;
}


void CNewBook::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNewBook)
	DDX_Control(pDX, IDC_NEWID, m_editID);
	DDX_Control(pDX, IDC_BOOK_TYPE, m_cmbType);
	DDX_Control(pDX, IDC_NEWBANK, m_cmbBank);
	DDX_Text(pDX, IDC_NEWCOMIT, m_newcomit);
	DDX_Text(pDX, IDC_NEWBANK, m_newbank);
	DDX_Text(pDX, IDC_NEWNAME, m_newname);
	DDX_Text(pDX, IDC_NEWID, m_newid);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNewBook, CDialog)
	//{{AFX_MSG_MAP(CNewBook)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNewBook message handlers

BOOL CNewBook::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CStringList strBankList;
    //Simon theApp.GetBankList(strBankList);
    POSITION pos = strBankList.GetHeadPosition();
    CString strBank;
    while (pos)
    {
        strBank = strBankList.GetNext(pos);
        m_cmbBank.InsertString(0,strBank);
    }
    strBankList.RemoveAll();

    //Simon theApp.FillCardType(&m_cmbType);

    if(m_bModeNew)
    {
        m_editID.EnableWindow();
    }
    else
    {
        ASSERT(m_pIDSet!=NULL);
        m_newbank=m_pIDSet->m_bank;
        m_newid=m_pIDSet->m_ID;
        m_newname=m_pIDSet->m_name;
        m_newcomit=m_pIDSet->m_remain;

        m_cmbType.SetCurSel(m_pIDSet->m_nType-1);
        
        UpdateData(FALSE);
    }
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


/*******************************************
    Function Name :	 
    Create by     :	  Qiu Simon
    Input         :   
    Output        :   
    Description   :   
    Date          :   1/10/2011 3:30:18 PM
********************************************/
void CNewBook::OnOK() 
{
    UpdateData();
    if(m_bModeNew)
    {
        m_pIDSet->AddNew();
        m_pIDSet->m_ID = m_newid;
		m_pIDSet->m_bank=m_newbank;
		m_pIDSet->m_remain=m_newcomit;
		m_pIDSet->m_name=m_newname;
		m_pIDSet->m_nType = m_cmbType.GetCurSel() + 1;
		m_pIDSet->Update();
    }
    else
    {
		CIDSet m_idSet;
		m_pIDSet->MakeDataCopy(m_idSet);

		m_idSet.m_bank=m_newbank;
		m_idSet.m_remain=m_newcomit;
		m_idSet.m_name=m_newname;
		m_idSet.m_nType = m_cmbType.GetCurSel() + 1;


		//m_pIDSet->Edit( );
		m_pIDSet->Modify_Book(&m_idSet);
    }

    
    EndDialog(IDOK);
	// TODO: Add extra validation here
	
}

// QueryEndDlg.cpp : implementation file
//

#include "stdafx.h"
#include "..\SmallHorse.h"
#include "QueryEndDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CQueryEndDlg dialog


CQueryEndDlg::CQueryEndDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CQueryEndDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CQueryEndDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CQueryEndDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CQueryEndDlg)
	DDX_Control(pDX, IDC_LIST, m_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CQueryEndDlg, CDialog)
	//{{AFX_MSG_MAP(CQueryEndDlg)
	ON_BN_CLICKED(IDC_SAVE_RESULT, OnSaveResult)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CQueryEndDlg message handlers

BOOL CQueryEndDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_list.InsertColumn(0,_T("Óà¶î"),1,100);
	m_list.InsertColumn(0,_T("ÕÊºÅ"),1,130);
	int i=0;
    if(!m_pidset->IsBOF())
    {
        m_pidset->MoveFirst();
    }
	while(!m_pidset->IsEOF())
	{
		m_list.InsertItem(i,m_pidset->m_ID);
		m_list.SetItemText(i,1,m_plistset->GetRemain(m_pidset->m_ID ));
		i++;
		m_pidset->MoveNext();
	}
		// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
//temp code. 2008-08-23
//should add select target file.
void CQueryEndDlg::OnSaveResult() 
{
	char pResult[256];
	char pNULL[]= "                                                                            ";
	int nCount = m_list.GetItemCount();
	CFile file;
	BOOL b = file.Open("F:\\bankbookresult.txt",CFile::modeCreate|CFile::modeWrite);
	int nlen;
	for(int i = 0;i <nCount;i++)
	{
		m_list.GetItemText(i,0,pResult,256);
		nlen = strlen(pResult);
		file.Write(pResult,strlen(pResult));
		if(nlen<32)
		{
			file.Write(pNULL,32-nlen);
		}
		m_list.GetItemText(i,1,pResult,256);
		file.Write(pResult,strlen(pResult));
		file.Write("\r\n",2);
	}
	file.Close();
}

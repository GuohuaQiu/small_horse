// dialog\ReplaceStringDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "..\SmallHorse.h"
#include "ReplaceStringDlg.h"


// CReplaceStringDlg 对话框

IMPLEMENT_DYNAMIC(CReplaceStringDlg, CDialog)

CReplaceStringDlg::CReplaceStringDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CReplaceStringDlg::IDD, pParent)
	, m_strNewString(_T(""))
	, m_strOldString(_T(""))
{

}

CReplaceStringDlg::~CReplaceStringDlg()
{
}

void CReplaceStringDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NEW_STR, m_strNewString);
	DDX_Text(pDX, IDC_EDIT_OLD_STR, m_strOldString);
}


BEGIN_MESSAGE_MAP(CReplaceStringDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CReplaceStringDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CReplaceStringDlg 消息处理程序

void CReplaceStringDlg::OnBnClickedOk()
{
	UpdateData(TRUE);
	if(m_strOldString.GetLength() == 0)
	{
		AfxMessageBox("请输入原字符串。");
		return;
	}
	
	// TODO: 在此添加控件通知处理程序代码
	OnOK();
}

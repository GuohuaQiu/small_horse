// dialog\ReplaceStringDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "..\SmallHorse.h"
#include "ReplaceStringDlg.h"


// CReplaceStringDlg �Ի���

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


// CReplaceStringDlg ��Ϣ�������

void CReplaceStringDlg::OnBnClickedOk()
{
	UpdateData(TRUE);
	if(m_strOldString.GetLength() == 0)
	{
		AfxMessageBox("������ԭ�ַ�����");
		return;
	}
	
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnOK();
}

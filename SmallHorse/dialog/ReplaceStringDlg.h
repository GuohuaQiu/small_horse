#pragma once


// CReplaceStringDlg �Ի���

class CReplaceStringDlg : public CDialog
{
	DECLARE_DYNAMIC(CReplaceStringDlg)

public:
	CReplaceStringDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CReplaceStringDlg();

// �Ի�������
	enum { IDD = IDD_REPLACE_STRING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_strNewString;
public:
	CString m_strOldString;
public:
	afx_msg void OnBnClickedOk();
};

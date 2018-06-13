#pragma once


// CReplaceStringDlg 对话框

class CReplaceStringDlg : public CDialog
{
	DECLARE_DYNAMIC(CReplaceStringDlg)

public:
	CReplaceStringDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CReplaceStringDlg();

// 对话框数据
	enum { IDD = IDD_REPLACE_STRING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_strNewString;
public:
	CString m_strOldString;
public:
	afx_msg void OnBnClickedOk();
};

#pragma once


// CFixedDepositManagerDlg 对话框

class CFixedDepositManagerDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFixedDepositManagerDlg)

public:
	CFixedDepositManagerDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CFixedDepositManagerDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DINGQI_MANAGER_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
    virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
    CString m_strBank;
    float m_fRate;
    float m_fValue;
    CString m_strComment;
    CString m_strId;
    CString m_strOwner;
    CString m_strSubCount;
    CBCGPDateTimeCtrl	m_wndDateTimeStart;
    CBCGPDateTimeCtrl	m_wndDateTimeEnd;
    COleDateTime	m_dateStart;
    COleDateTime	m_dateEnd;
    CComboBox	m_cmbSpan;
    CString m_strTimeSpan;
    afx_msg void OnSelchangeComboTimespan();
    afx_msg void OnBnClickedOk();
};

#pragma once


// Look_up 对话框

extern char card_No[17];

class Look_up : public CDialogEx
{
	DECLARE_DYNAMIC(Look_up)

public:
	Look_up(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Look_up();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClickedButton1();
};

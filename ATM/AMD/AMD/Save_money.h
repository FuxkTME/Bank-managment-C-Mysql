#pragma once

extern char card_No[17];

// Save_money 对话框

class Save_money : public CDialogEx
{
	DECLARE_DYNAMIC(Save_money)

public:
	Save_money(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Save_money();

// 对话框数据
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClickedButton1();
	afx_msg void OnClickedButton2();
};

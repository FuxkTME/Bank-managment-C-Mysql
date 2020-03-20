#pragma once


// Functions 对话框

extern char card_pwd[7];
extern char card_No[17];

class Functions : public CDialogEx
{
	DECLARE_DYNAMIC(Functions)

public:
	Functions(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Functions();

// 对话框数据
	enum { IDD = Function };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnClickedLookup();
	afx_msg void OnClickedWithdarw();
	afx_msg void OnClickedTransfer();
	afx_msg void OnClickedSave();
	afx_msg void OnClickedChange();
	afx_msg void OnClickedExit();
};

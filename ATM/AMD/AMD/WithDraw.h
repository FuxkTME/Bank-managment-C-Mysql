#pragma once

// WithDraw 对话框

class WithDraw : public CDialogEx
{
	DECLARE_DYNAMIC(WithDraw)

public:
	WithDraw(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~WithDraw();

// 对话框数据
	enum { IDD = WithDrawC };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClickedWithdarwC();
	afx_msg void OnClickedBack1();
};

extern char card_No[17];

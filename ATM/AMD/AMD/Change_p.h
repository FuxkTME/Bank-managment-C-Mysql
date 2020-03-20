#pragma once

extern char card_No[17];
extern char card_pwd[7];
// Change_p 对话框

class Change_p : public CDialogEx
{
	DECLARE_DYNAMIC(Change_p)

public:
	Change_p(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Change_p();

// 对话框数据
	enum { IDD = IDD_DIALOG4 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClickedButton1();
	afx_msg void OnClickedButton2();
//	CString password_f;
//	CString password_s;
	CString pwd_f;
	CString pwd_s;
};

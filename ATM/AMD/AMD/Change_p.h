#pragma once

extern char card_No[17];
extern char card_pwd[7];
// Change_p �Ի���

class Change_p : public CDialogEx
{
	DECLARE_DYNAMIC(Change_p)

public:
	Change_p(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Change_p();

// �Ի�������
	enum { IDD = IDD_DIALOG4 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClickedButton1();
	afx_msg void OnClickedButton2();
//	CString password_f;
//	CString password_s;
	CString pwd_f;
	CString pwd_s;
};

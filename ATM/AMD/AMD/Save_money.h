#pragma once

extern char card_No[17];

// Save_money �Ի���

class Save_money : public CDialogEx
{
	DECLARE_DYNAMIC(Save_money)

public:
	Save_money(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Save_money();

// �Ի�������
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClickedButton1();
	afx_msg void OnClickedButton2();
};

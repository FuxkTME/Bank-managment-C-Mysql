#pragma once


// Look_up �Ի���

extern char card_No[17];

class Look_up : public CDialogEx
{
	DECLARE_DYNAMIC(Look_up)

public:
	Look_up(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Look_up();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClickedButton1();
};

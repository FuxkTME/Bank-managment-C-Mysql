#pragma once

// WithDraw �Ի���

class WithDraw : public CDialogEx
{
	DECLARE_DYNAMIC(WithDraw)

public:
	WithDraw(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~WithDraw();

// �Ի�������
	enum { IDD = WithDrawC };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClickedWithdarwC();
	afx_msg void OnClickedBack1();
};

extern char card_No[17];

#pragma once

extern char card_No[17];
// Transfer_m �Ի���

class Transfer_m : public CDialogEx
{
	DECLARE_DYNAMIC(Transfer_m)

public:
	Transfer_m(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Transfer_m();

// �Ի�������
	enum { IDD = IDD_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClickedButton1();
	afx_msg void OnClickedButton2();
	CString card_no_f;
	CString card_no_s;
};

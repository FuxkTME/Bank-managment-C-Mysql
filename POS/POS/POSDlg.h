
// POSDlg.h : ͷ�ļ�
//

#pragma once


// CPOSDlg �Ի���
class CPOSDlg : public CDialogEx
{
// ����
public:
	CPOSDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_POS_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString poscardno;
	CString pospwd;
	afx_msg void OnClickedButton1();
	afx_msg void OnClickedButton2();
};

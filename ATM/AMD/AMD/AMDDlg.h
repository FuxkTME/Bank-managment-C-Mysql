
// AMDDlg.h : ͷ�ļ�
//


#pragma once


// CAMDDlg �Ի���
class CAMDDlg : public CDialogEx
{
// ����
public:
	CAMDDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_AMD_DIALOG };

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
	afx_msg void OnClickedLogin();
	afx_msg void OnClickedExit();
	CString input_cardno;
	CString input_pwd;
};

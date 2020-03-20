
// AMDDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "AMD.h"
#include "AMDDlg.h"
#include "afxdialogex.h"
#include "stdlib.h"
#include "string.h"
#include "time.h"
#include<Windows.h>
#include <WinSock2.h>
#include <winsock.h>
#include <mysql.h>
#include "Functions.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


MYSQL mysql, *sock;   //����MySQL�ľ��
MYSQL_RES* result;
MYSQL_ROW row;

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CAMDDlg �Ի���



CAMDDlg::CAMDDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAMDDlg::IDD, pParent)
	, input_cardno(_T(""))
	, input_pwd(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAMDDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, INPUT_CARDNO, input_cardno);
	DDX_Text(pDX, INPUT_PWD, input_pwd);
}

BEGIN_MESSAGE_MAP(CAMDDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(LOGIN, &CAMDDlg::OnClickedLogin)
	ON_BN_CLICKED(EXIT, &CAMDDlg::OnClickedExit)
END_MESSAGE_MAP()


// CAMDDlg ��Ϣ�������

BOOL CAMDDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CAMDDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CAMDDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CAMDDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//extern char card_No[18];
//extern char card_pwd[8];

char card_pwd[7];
char card_No[17];

void CAMDDlg::OnClickedLogin()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	int temp1 = 0;
	MYSQL myCont;
	mysql_init(&myCont);
	if (mysql_real_connect(&myCont, "localhost", "root", "", "mycont", 3306, NULL, 0))
	{
		mysql_query(&myCont, "SET NAMES GBK");
	loop:
		char sql[255] = { 0 };
		//char pwd[7];
		//printf("��������(�������λ���):");
		//fflush(stdin);
		//gets_s(pwd);
		UpdateData(TRUE);
		char cardNo[17] = {0};
		char pwd[7] = {0};
		WideCharToMultiByte(CP_ACP, 0, input_cardno.GetBuffer(0), input_cardno.GetLength(), cardNo, 16, 0, 0);
		strcpy_s(card_No,cardNo);
		WideCharToMultiByte(CP_ACP, 0, input_pwd.GetBuffer(0), input_pwd.GetLength(), pwd, 6, 0, 0);
		strcpy_s(card_pwd,pwd );
		sprintf_s(sql, "select * from cards where cardNo='%s'", cardNo);
		mysql_query(&myCont, sql);
		//deal with the result
		result = mysql_store_result(&myCont);
		printf("\n");
		if (mysql_num_rows(result))
		{
			while ((row = mysql_fetch_row(result)))
			{
				if (!strcmp(row[5], "���"))
				{
					if (!strcmp(row[7], "��ʧ״̬"))
					{
						MessageBox(_T("��ѿ�����ʧ��\n"), _T("����"));
					}
					else
					{
						if (!strcmp(row[3], pwd))
						{
							MessageBox(_T("������ȷ"), _T("��ϲ"));
							Functions page;
							page.DoModal();
							//return 1;
						}
						else
						{
							temp1++;
							MessageBox(_T("�������"), _T("����"));
							if (temp1 == 3)
							{
							char sql1[255] = { 0 };
							sprintf_s(sql1, "update cards set status='��ʧ' where cardNo='%s'", cardNo);
							mysql_query(&myCont, sql1);
							goto loop1;
							}
							goto loop;
						}
					}
				}
				else 
					MessageBox(_T("���Ŀ������ÿ����޷�ʹ��ATM"), _T("����"));
				
			}
		}
		else
			MessageBox(_T("�޴˿�"),_T("����"));
		//release the resource
		loop1:
		mysql_free_result(result);
		mysql_close(&myCont);
	}
	else
	{
		MessageBox(_T("���ݿ�����ʧ��\n"),  _T("����"));
	}
}


void CAMDDlg::OnClickedExit()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	SendMessage(WM_CLOSE, 0, 0);
}

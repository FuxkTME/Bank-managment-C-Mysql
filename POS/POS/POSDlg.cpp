
// POSDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "POS.h"
#include "POSDlg.h"
#include "afxdialogex.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "time.h"
//#include "stdafx.h"
#include<Windows.h>
#include <mysql.h>
#include <WinSock2.h>
#include <winsock.h>
#pragma comment(lib,"libmysql.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// CPOSDlg �Ի���



CPOSDlg::CPOSDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPOSDlg::IDD, pParent)
	, poscardno(_T(""))
	, pospwd(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPOSDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_E, poscardno);
	DDX_Text(pDX, IDC_EDIT2, pospwd);
}

BEGIN_MESSAGE_MAP(CPOSDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CPOSDlg::OnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CPOSDlg::OnClickedButton2)
END_MESSAGE_MAP()


// CPOSDlg ��Ϣ�������

BOOL CPOSDlg::OnInitDialog()
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

void CPOSDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CPOSDlg::OnPaint()
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
HCURSOR CPOSDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CPOSDlg::OnClickedButton1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	MYSQL mysql, *sock;   //����MySQL�ľ��
	MYSQL_RES* result;
	MYSQL_ROW row;
	MYSQL myCont;
	mysql_init(&myCont);//#1.��ʼ��
	if (mysql_real_connect(&myCont, "192.168.137.200", "Tobby", "1314", "bank", 3306, NULL, 0))//#2.�������ݿ�
	{
		mysql_query(&myCont, "SET NAMES GBK"); //#3.���ñ����ʽ
		char sql[255] = { 0 };
		int flag = 0;
		UpdateData(TRUE);
		char cardNo[17] = { 0 };
		char pwd[7] = { 0 };
		WideCharToMultiByte(CP_ACP, 0, poscardno.GetBuffer(0), poscardno.GetLength(), cardNo, 16, 0, 0);
		WideCharToMultiByte(CP_ACP, 0, pospwd.GetBuffer(0), pospwd.GetLength(), pwd, 6, 0, 0);
		sprintf_s(sql, "select * from cards where cardNo = '%s' and password = '%s'", cardNo, pwd);
		CString cs1;
		GetDlgItemText(IDC_EDIT3, cs1);
		double money = _ttof(cs1);
		mysql_query(&myCont, sql);
		result = mysql_store_result(&myCont);//#4.2.1�洢��ѯ���
		if (mysql_num_rows(result))
		{
			//printf("%s\n",sql_row[5]);
			while (row = mysql_fetch_row(result))
			{
				//printf("��������Ҫ���ѵĽ��:");
				//scanf("%lf", &i);

				double money1 = atof(row[8]);
				double money2 = atof(row[6]);
				if (strcmp(row[5], "���") == 0)
				{
					if (money < 0)
					{
						MessageBox(_T("error\n"));
					}
					else
					{
						money1 = money1 - money;
						if (money1 >= 0)
						{
							sprintf_s(sql, "update cards set balance ='%0.2lf' where cardNo = '%s'", money1, cardNo);
							mysql_query(&myCont, sql);
							MessageBox(_T("֧���ɹ�"));
							flag = 1;

						}
						else
						{
							MessageBox(_T("����!"));
						}

					}

				}
				if (strcmp(row[5], "���ÿ�") == 0)
				{
					if (money < 0)
					{
						MessageBox(_T("error"));
					}
					if (money >= 0)
					{


						money2 = money2 - money;
						if (money2 >= 0)
						{
							sprintf_s(sql, "update cards set  card_limit ='%0.2lf' where cardNo = '%s'", money2, cardNo);
							mysql_query(&myCont, sql);
							MessageBox(_T("֧���ɹ�!"));

							flag = 1;



						}
						else
						{
							MessageBox(_T("���㣡"));
						}

					}

				}

			}

		}
		else
			MessageBox(_T("���Ż����벻ƥ��!"));
		while (flag)
		{
			char sql[250];
			sprintf_s(sql, "select now()");
			mysql_query(&myCont, sql);
			result = mysql_store_result(&myCont);
			char s[30];
			while (row = mysql_fetch_row(result))
			{

				strcpy_s(s, row[0]);
				//printf("%s\n",s);
			}
			//time_t timep;
			//struct tm *p;
			//time (&timep);
			//char s[30];
			// strcpy(s,ctime(&timep));
			//printf("%s\n",s);
			char n[11] = { 0 };
			srand((int)time(NULL));
			int i;
			for (i = 0; i < 10; i++)
			{
				n[i] = rand() % 10 + '0';
			}
			//char sql[250];
			sprintf_s(sql, " insert into consumption values('%s','%s','%s','%lf')", cardNo, n, s, money);
			mysql_query(&myCont, sql);
			flag = 0;
			//result = mysql_store_result(&myCont);

		}
		mysql_free_result(result);//4.2.3�ͷŲ�ѯ���
		mysql_close(&myCont);
	}
}


void CPOSDlg::OnClickedButton2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	SendMessage(WM_CLOSE, 0, 0);
}

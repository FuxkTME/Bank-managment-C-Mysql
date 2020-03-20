
// AMDDlg.cpp : 实现文件
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


MYSQL mysql, *sock;   //声明MySQL的句柄
MYSQL_RES* result;
MYSQL_ROW row;

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CAMDDlg 对话框



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


// CAMDDlg 消息处理程序

BOOL CAMDDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CAMDDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
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
	// TODO:  在此添加控件通知处理程序代码
	// TODO:  在此添加控件通知处理程序代码

	int temp1 = 0;
	MYSQL myCont;
	mysql_init(&myCont);
	if (mysql_real_connect(&myCont, "localhost", "root", "", "mycont", 3306, NULL, 0))
	{
		mysql_query(&myCont, "SET NAMES GBK");
	loop:
		char sql[255] = { 0 };
		//char pwd[7];
		//printf("输入密码(你有三次机会):");
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
				if (!strcmp(row[5], "储蓄卡"))
				{
					if (!strcmp(row[7], "挂失状态"))
					{
						MessageBox(_T("请把卡还给失主\n"), _T("错误"));
					}
					else
					{
						if (!strcmp(row[3], pwd))
						{
							MessageBox(_T("密码正确"), _T("恭喜"));
							Functions page;
							page.DoModal();
							//return 1;
						}
						else
						{
							temp1++;
							MessageBox(_T("密码错误"), _T("错误"));
							if (temp1 == 3)
							{
							char sql1[255] = { 0 };
							sprintf_s(sql1, "update cards set status='挂失' where cardNo='%s'", cardNo);
							mysql_query(&myCont, sql1);
							goto loop1;
							}
							goto loop;
						}
					}
				}
				else 
					MessageBox(_T("您的卡是信用卡，无法使用ATM"), _T("错误"));
				
			}
		}
		else
			MessageBox(_T("无此卡"),_T("错误"));
		//release the resource
		loop1:
		mysql_free_result(result);
		mysql_close(&myCont);
	}
	else
	{
		MessageBox(_T("数据库连接失败\n"),  _T("错误"));
	}
}


void CAMDDlg::OnClickedExit()
{
	// TODO:  在此添加控件通知处理程序代码
	SendMessage(WM_CLOSE, 0, 0);
}

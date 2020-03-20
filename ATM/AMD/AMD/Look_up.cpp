// Look_up.cpp : 实现文件
//

#include "stdafx.h"
#include "AMD.h"
#include "Look_up.h"
#include "afxdialogex.h"
#include "stdlib.h"
#include "string.h"
//#include "stdafx.h"
#include "time.h"
#include<Windows.h>
#include <WinSock2.h>
#include <winsock.h>
#include <mysql.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// Look_up 对话框

IMPLEMENT_DYNAMIC(Look_up, CDialogEx)

Look_up::Look_up(CWnd* pParent /*=NULL*/)
	: CDialogEx(Look_up::IDD, pParent)
{

}

Look_up::~Look_up()
{
}

void Look_up::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Look_up, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &Look_up::OnClickedButton1)
END_MESSAGE_MAP()


// Look_up 消息处理程序

BOOL Look_up::OnInitDialog()
{
	MYSQL mysql, *sock;   //声明MySQL的句柄
	MYSQL_RES* result;
	MYSQL_ROW row;
	MYSQL myCont;
	mysql_init(&myCont);
	if (mysql_real_connect(&myCont, "localhost", "root", "", "mycont", 3306, NULL, 0))
	{
		mysql_query(&myCont, "SET NAMES GBK");
		char sql[255] = { 0 };
		sprintf_s(sql, "select balance from cards where cardNo='%s'", card_No);
		mysql_query(&myCont, sql);
		//deal with the result
		result = mysql_store_result(&myCont);
		printf("\n");
		while ((row = mysql_fetch_row(result)))
		{
			SetDlgItemText(Balance, CString(row[0]));
			printf("\n");
		}
		//release the resource
		mysql_free_result(result);
		mysql_close(&myCont);
	}
	return true;
}

void Look_up::OnClickedButton1()
{
	// TODO:  在此添加控件通知处理程序代码
	SendMessage(WM_CLOSE, 0, 0);
}

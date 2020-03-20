// Save_money.cpp : 实现文件
//

#include "stdafx.h"
#include "AMD.h"
#include "Save_money.h"
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

// Save_money 对话框

IMPLEMENT_DYNAMIC(Save_money, CDialogEx)

Save_money::Save_money(CWnd* pParent /*=NULL*/)
	: CDialogEx(Save_money::IDD, pParent)
{

}

Save_money::~Save_money()
{
}

void Save_money::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Save_money, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &Save_money::OnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &Save_money::OnClickedButton2)
END_MESSAGE_MAP()


// Save_money 消息处理程序


void Save_money::OnClickedButton1()
{
	// TODO:  在此添加控件通知处理程序代码
	MYSQL mysql, *sock;   //声明MySQL的句柄
	MYSQL_RES* result;
	MYSQL_ROW row, sql_row;
	MYSQL myCont;
	mysql_init(&myCont);
	if (mysql_real_connect(&myCont, "localhost", "root", "", "mycont", 3306, NULL, 0))
	{
		mysql_query(&myCont, "SET NAMES GBK");
		CString cs1;
		UpdateData(TRUE);
		GetDlgItemText(IDC_EDIT1, cs1);
		double money = _ttof(cs1);
		char sql[255] = { 0 };
		sprintf_s(sql, "select balance from cards where cardNo='%s'", card_No);
		mysql_query(&myCont, sql);
		result = mysql_store_result(&myCont);
		double money1;
		while ((row = mysql_fetch_row(result)))
		{
			money1 = atof(row[0]);
			money1 = money + money1;
		}
			char sql1[255] = { 0 };
			sprintf_s(sql1, "update cards set balance='%lf' where cardNo='%s'", money1, card_No);
			mysql_query(&myCont, sql1);

			char sql2[255] = { 0 };
			sprintf_s(sql2, "select now()");
			char s[30];
			mysql_query(&myCont, sql2);
			result = mysql_store_result(&myCont);
			while (sql_row = mysql_fetch_row(result))
			{

				strcpy_s(s, sql_row[0]);
			}
			char n[11] = { 0 };
			//createstring(n, 10);
			srand((int)time(NULL));
			int i;
			for (i = 0; i <10; i++)
			{
				n[i] = rand() % 10 + '0';//随机卡的每一位数字
			}
			char sql3[250] = { 0 };
			sprintf_s(sql3, " insert into in_come values('%s','%s','%s','%lf')", card_No, n, s, money);
			mysql_query(&myCont, sql3);

			CString cs2;
			cs2.Format(_T("%.2f"), money1);
			SetDlgItemText(IDC_EDIT2, cs2);
			MessageBox(_T("存款成功"), _T("恭喜"));
		//release the resource
		mysql_free_result(result);
		mysql_close(&myCont);
	}
}


void Save_money::OnClickedButton2()
{
	// TODO:  在此添加控件通知处理程序代码
	SendMessage(WM_CLOSE, 0, 0);
}

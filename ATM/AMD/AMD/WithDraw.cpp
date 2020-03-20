// WithDraw.cpp : 实现文件
//
		
#include "stdafx.h"
#include "AMD.h"
#include "WithDraw.h"
#include "afxdialogex.h"
#include "stdlib.h"
#include "string.h"
#include "time.h"
#include<Windows.h>
#include <WinSock2.h>
#include <winsock.h>
#include <mysql.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// WithDraw 对话框

IMPLEMENT_DYNAMIC(WithDraw, CDialogEx)

WithDraw::WithDraw(CWnd* pParent /*=NULL*/)
	: CDialogEx(WithDraw::IDD, pParent)
{

}

WithDraw::~WithDraw()
{
}

void WithDraw::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(WithDraw, CDialogEx)
	ON_BN_CLICKED(Withdarw_c, &WithDraw::OnClickedWithdarwC)
	ON_BN_CLICKED(Back1, &WithDraw::OnClickedBack1)
END_MESSAGE_MAP()


// WithDraw 消息处理程序


void WithDraw::OnClickedWithdarwC()
{
	// TODO:  在此添加控件通知处理程序代码
	MYSQL mysql, *sock;   //声明MySQL的句柄
	MYSQL_RES* result;
	MYSQL_ROW row;
	MYSQL_ROW sql_row;

	MYSQL myCont;
	mysql_init(&myCont);
	if (mysql_real_connect(&myCont, "localhost", "root", "", "mycont", 3306, NULL, 0))
	{
		mysql_query(&myCont, "SET NAMES GBK");
		CString cs1;
		UpdateData(TRUE);
		GetDlgItemText(Money_with, cs1);
		double money = _ttof(cs1);;
		char sql[255] = { 0 };
		sprintf_s(sql, "select balance from cards where cardNo='%s'", card_No);
		mysql_query(&myCont, sql);
		result = mysql_store_result(&myCont);
		while ((row = mysql_fetch_row(result)))
		{
			if ((atof(row[0])<money))
			{
				CString cs3;
				cs3.Format(_T("%.2f"),atof(row[0]));
				SetDlgItemText(Balance1, cs3);
				MessageBox(_T("余额不足"), _T("错误"));
			}
			else
			{
				double money1 = atof(row[0]);
				money1 = money1 - money;
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
				char sql3[250];
				sprintf_s(sql3, " insert into consumption values('%s','%s','%s','%lf')", card_No, n, s,money);
				mysql_query(&myCont, sql3);
				sprintf_s(sql2, "update cards set balance='%lf' where cardNo='%s'", money, card_No);
				CString cs2;
				cs2.Format(_T("%.2f"), money1);
				SetDlgItemText(Balance1, cs2);
				MessageBox(_T("取款成功"), _T("恭喜"));
			}
		}
		//release the resource
		mysql_free_result(result);
		mysql_close(&myCont);
	}
}


void WithDraw::OnClickedBack1()
{
	// TODO:  在此添加控件通知处理程序代码
	SendMessage(WM_CLOSE, 0, 0);
}






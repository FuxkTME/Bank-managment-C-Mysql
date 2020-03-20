// Transfer_m.cpp : 实现文件
//

#include "stdafx.h"
#include "AMD.h"
#include "Transfer_m.h"
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


// Transfer_m 对话框

IMPLEMENT_DYNAMIC(Transfer_m, CDialogEx)

Transfer_m::Transfer_m(CWnd* pParent /*=NULL*/)
	: CDialogEx(Transfer_m::IDD, pParent)
	, card_no_f(_T(""))
	, card_no_s(_T(""))
{

}

Transfer_m::~Transfer_m()
{
}

void Transfer_m::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT3, card_no_f);
	DDX_Text(pDX, IDC_EDIT4, card_no_s);
}


BEGIN_MESSAGE_MAP(Transfer_m, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &Transfer_m::OnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &Transfer_m::OnClickedButton2)
END_MESSAGE_MAP()


// Transfer_m 消息处理程序


void Transfer_m::OnClickedButton1()
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
		UpdateData(TRUE);
		mysql_query(&myCont, "SET NAMES GBK");
		char card_no[18] = { 0 };
		char card_no_confirm[18] = {0};
		WideCharToMultiByte(CP_ACP, 0, card_no_f.GetBuffer(0), card_no_f.GetLength(), card_no, 17, 0, 0);
		WideCharToMultiByte(CP_ACP, 0, card_no_s.GetBuffer(0), card_no_s.GetLength(), card_no_confirm, 17, 0, 0);
		if (strcmp(card_no, card_no_confirm))
		{
			MessageBox(_T("卡号不一致"));
		}
		char sql[255] = { 0 };
		sprintf_s(sql, "select * from cards where cardNo='%s'", card_no);
		mysql_query(&myCont, sql);
		//deal with the result
		result = mysql_store_result(&myCont);
		if (mysql_num_rows(result))
		{
			row = mysql_fetch_row(result);
			if (!strcmp(row[7], "挂失状态"))
			{
				MessageBox(_T("卡已被冻结，转账失败"), _T("错误"));
			}
			else if(!strcmp(row[5], "信用卡"))
			{
				MessageBox(_T("卡是信用卡，转账失败"), _T("错误"));
			}
			else
			{
				double money1, money2;
				CString cs1;
				UpdateData(TRUE);
				GetDlgItemText(IDC_EDIT1, cs1);
				double money = _ttof(cs1);;
				char sql1[255] = { 0 };
				sprintf_s(sql1, "select balance from cards where cardNo='%s'", card_No);
				mysql_query(&myCont, sql1);
				result = mysql_store_result(&myCont);
				printf("\n");
				row = mysql_fetch_row(result);
				if (atof(row[0])<money)
				{
					CString cs3;
					cs3.Format(_T("%.2f"), atof(row[0]));
					SetDlgItemText(IDC_EDIT2, cs3);
					MessageBox(_T("余额不足"), _T("错误"));
				}
				else
				{
					money1 = atof(row[0]) - money;
					double money3 = atof(row[0]);
					char sql2[255] = { 0 };
					sprintf_s(sql2, "select balance from cards where cardNo='%s'", card_no);
					mysql_query(&myCont, sql2);
					result = mysql_store_result(&myCont);
					printf("\n");
					row = mysql_fetch_row(result);
					money2 = atof(row[0]) + money;

					char sql3[255] = { 0 };
					sprintf_s(sql3, "update cards set balance='%lf' where cardNo='%s'", money1, card_No);
					mysql_query(&myCont, sql3);
					char sql4[255] = { 0 };
					sprintf_s(sql4, "update cards set balance='%lf' where cardNo='%s'", money2, card_no);
					mysql_query(&myCont, sql4);

					char sql5[255] = { 0 };
					sprintf_s(sql5, "select now()");
					char s[30];
					mysql_query(&myCont, sql5);
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
						n[i] = rand() % 10 + '0';
					}
					char sql6[250] = {0};
					char sql7[250] = { 0 };
					sprintf_s(sql6, " insert into consumption values('%s','%s','%s','%lf')", card_No, n, s, money3);
					sprintf_s(sql7, " insert into in_come values('%s','%s','%s','%lf')", card_no, n, s, money);
					mysql_query(&myCont, sql6);
					mysql_query(&myCont, sql7);

					CString cs2;
					cs2.Format(_T("%.2f"), money1);
					SetDlgItemText(IDC_EDIT2, cs2);
					MessageBox(_T("转账成功"), _T("恭喜"));
				}
			}
		}
		else
			MessageBox(_T("无此卡"), _T("错误"));
		//puts(temmmp);
		mysql_free_result(result);
		mysql_close(&myCont);

		//  }
	}
}


void Transfer_m::OnClickedButton2()
{
	// TODO:  在此添加控件通知处理程序代码
	SendMessage(WM_CLOSE, 0, 0);
}

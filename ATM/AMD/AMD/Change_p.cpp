// Change_p.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "AMD.h"
#include "Change_p.h"
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


// Change_p �Ի���

IMPLEMENT_DYNAMIC(Change_p, CDialogEx)

Change_p::Change_p(CWnd* pParent /*=NULL*/)
	: CDialogEx(Change_p::IDD, pParent)
	, pwd_f(_T(""))
	, pwd_s(_T(""))
{

}

Change_p::~Change_p()
{
}

void Change_p::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, pwd_f);
	DDX_Text(pDX, IDC_EDIT2, pwd_s);
}


BEGIN_MESSAGE_MAP(Change_p, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &Change_p::OnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &Change_p::OnClickedButton2)
END_MESSAGE_MAP()


// Change_p ��Ϣ�������


void Change_p::OnClickedButton1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	MYSQL mysql, *sock;   //����MySQL�ľ��
	MYSQL_RES* result;
	MYSQL_ROW row;
	MYSQL myCont;
	mysql_init(&myCont);
	if (mysql_real_connect(&myCont, "localhost", "root", "", "mycont", 3306, NULL, 0))
	{
		mysql_query(&myCont, "SET NAMES GBK");
		char new_password[8] = {0};
		char new_password_confirm[8] = {0};
		UpdateData(TRUE);
		WideCharToMultiByte(CP_ACP, 0, pwd_f.GetBuffer(0), pwd_f.GetLength(), new_password, 8, 0, 0);
		WideCharToMultiByte(CP_ACP, 0, pwd_s.GetBuffer(0), pwd_s.GetLength(), new_password_confirm, 8, 0, 0);
		if (strcmp(new_password, new_password_confirm))
		{
			MessageBox(_T("���벻һ��"), _T("����"));
		}
		char sql[255] = { 0 };
		sprintf_s(sql, "update cards set password='%s' where cardNo='%s'", new_password, card_No);
		mysql_query(&myCont, sql);
		MessageBox(_T("������ɹ�"), _T("����"));

		mysql_close(&myCont);
	}
}


void Change_p::OnClickedButton2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	SendMessage(WM_CLOSE, 0, 0);
}

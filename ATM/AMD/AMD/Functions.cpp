// Functions.cpp : 实现文件
//

#include "stdafx.h"
#include "AMD.h"
#include "Functions.h"
#include "afxdialogex.h"
#include "Look_up.h"
#include "Withdraw.h"
#include "Save_money.h"
#include "Transfer_m.h"
#include "Change_p.h"


// Functions 对话框

IMPLEMENT_DYNAMIC(Functions, CDialogEx)

Functions::Functions(CWnd* pParent /*=NULL*/)
	: CDialogEx(Functions::IDD, pParent)
{

}

Functions::~Functions()
{
}

void Functions::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Functions, CDialogEx)
	//ON_BN_CLICKED(IDC_BUTTON1, &Functions::OnBnClickedButton1)
	ON_BN_CLICKED(Lookup, &Functions::OnClickedLookup)
	ON_BN_CLICKED(Withdarw, &Functions::OnClickedWithdarw)
	ON_BN_CLICKED(Transfer, &Functions::OnClickedTransfer)
	ON_BN_CLICKED(Save, &Functions::OnClickedSave)
	ON_BN_CLICKED(Change, &Functions::OnClickedChange)
	ON_BN_CLICKED(EXIT, &Functions::OnClickedExit)
END_MESSAGE_MAP()


// Functions 消息处理程序


void Functions::OnClickedLookup()
{
	// TODO:  在此添加控件通知处理程序代码
	Look_up page;
	page.DoModal();

}


void Functions::OnClickedWithdarw()
{
	// TODO:  在此添加控件通知处理程序代码
	WithDraw page;
	page.DoModal();
}


void Functions::OnClickedTransfer()
{
	// TODO:  在此添加控件通知处理程序代码
	Transfer_m page;
	page.DoModal();
}


void Functions::OnClickedSave()
{
	// TODO:  在此添加控件通知处理程序代码
	Save_money page;
	page.DoModal();
}


void Functions::OnClickedChange()
{
	// TODO:  在此添加控件通知处理程序代码
	Change_p page;
	page.DoModal();
}


void Functions::OnClickedExit()
{
	// TODO:  在此添加控件通知处理程序代码
	SendMessage(WM_CLOSE, 0, 0);
}

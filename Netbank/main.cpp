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

#define N 10

MYSQL mysql, *sock;   //声明MySQL的句柄
MYSQL_RES* result;
MYSQL_ROW row;

int Login(char* p)
{
    {
        int temp1=0;
        MYSQL myCont;
        mysql_init(&myCont);
        if(mysql_real_connect(&myCont,"localhost", "1", "1234", "mycont",3306,NULL,0))
        {
            mysql_query(&myCont,"SET NAMES GBK");
loop:
            char sql[255]= {0};
            sprintf(sql,"select * from cards where cardNo='%s'",p);
            char pwd[7];
            printf("输入密码(你有三次机会):");
            fflush(stdin);
            gets(pwd);
            mysql_query(&myCont,sql);
            //deal with the result
            result=mysql_store_result(&myCont);
            printf("\n");
            if(mysql_num_rows(result))
            {
                while((row=mysql_fetch_row(result)))
                {
                    if(!strcmp(row[7],"挂失状态"))
                    {
                        printf("请把卡还给失主\n");
                        return 0;
                    }
                    else
                    {
                        if(!strcmp(row[3],pwd))
                        {
                            printf("密码正确\n");
                            return 1;
                        }
                        else
                        {
                            temp1++;
                            printf("密码第%d次错误\n",temp1);
                            if(temp1==3)
                                goto loop1;
                            goto loop;
                        }
                    }
                }
            }
            else
                printf("无此卡\n");
            //release the resource
loop1:
            {
                char sql1[255]= {0};
                sprintf(sql1,"update cards set status='挂失状态' where cardNo='%s'",p);
                mysql_query(&myCont,sql1);
            }
            mysql_free_result(result);
            mysql_close(&myCont);
        }
    }
}

void Lookup(char *p)
{
    int temp;
loop:
    {
        MYSQL myCont;
        mysql_init(&myCont);
        if(mysql_real_connect(&myCont,"localhost", "1", "1234", "mycont",3306,NULL,0))
        {
            mysql_query(&myCont,"SET NAMES GBK");
            //printf("输入你要查询的姓名:");
            //char name[17]= {""};
            //fflush(stdin);
            //gets(name);
            char sql[255]= {0};
            sprintf(sql,"select * from consumption where cardNo='%s' order by trade_time",p);
            mysql_query(&myCont,sql);
            //deal with the result
            result=mysql_store_result(&myCont);
            printf("\n");
            if(mysql_num_rows(result))
            {
                printf("卡号：            账单号：    交易时间：          交易金额：   \n");
                while((row=mysql_fetch_row(result)))
                {
                printf("%s||%s||%s||%s||\n",row[0],row[1],row[2],row[3]);
                }
            }
            else
                printf("无支出记录!\n");
            //release the resource
            mysql_free_result(result);
            mysql_close(&myCont);
        }
    }
}

void Lookup2(char *p)
{
    int temp;
loop:
    {
        MYSQL myCont;
        mysql_init(&myCont);
        if(mysql_real_connect(&myCont,"localhost", "1", "1234", "mycont",3306,NULL,0))
        {
            mysql_query(&myCont,"SET NAMES GBK");
            //printf("输入你要查询的姓名:");
            //char name[17]= {""};
            //fflush(stdin);
            //gets(name);
            char sql[255]= {0};
            sprintf(sql,"select * from in_come where cardNo='%s' order by trade_time",p);
            mysql_query(&myCont,sql);
            //deal with the result
            result=mysql_store_result(&myCont);
            printf("\n");
            if(mysql_num_rows(result))
            {
                printf("卡号：            账单号：    交易时间：          交易金额：   \n");
                while((row=mysql_fetch_row(result)))
                {
                    printf("%s||%s||%s||%s||\n",row[0],row[1],row[2],row[3]);
                }
            }
            else
                printf("无收入记录!\n");
            //release the resource
            mysql_free_result(result);
            mysql_close(&myCont);
        }
    }
}

void Balance(char* p)
{
    MYSQL myCont;
    mysql_init(&myCont);
    if(mysql_real_connect(&myCont,"localhost", "1", "1234", "mycont",3306,NULL,0))
    {
        mysql_query(&myCont,"SET NAMES GBK");
        char sql[255]= {0};
        sprintf(sql,"select balance from cards where cardNo='%s'",p);
        mysql_query(&myCont,sql);
        //deal with the result
        result=mysql_store_result(&myCont);
        printf("\n");
        while((row=mysql_fetch_row(result)))
        {
            printf("余额：");
            puts(row[0]);
            printf("\n");
        }
        //release the resource
        mysql_free_result(result);
        mysql_close(&myCont);
    }
}

void Limit(char* p)
{
    MYSQL myCont;
    mysql_init(&myCont);
    if(mysql_real_connect(&myCont,"localhost", "1", "1234", "mycont",3306,NULL,0))
    {
        mysql_query(&myCont,"SET NAMES GBK");
        char sql[255]= {0};
        sprintf(sql,"select card_limit from cards where cardNo='%s'",p);
        mysql_query(&myCont,sql);
        //deal with the result
        result=mysql_store_result(&myCont);
        printf("\n");
        while((row=mysql_fetch_row(result)))
        {
            printf("限额：");
            puts(row[0]);
            printf("\n");
        }
        //release the resource
        mysql_free_result(result);
        mysql_close(&myCont);
    }
}

void Transfer(char* p)
{
    MYSQL myCont;
    mysql_init(&myCont);
    if(mysql_real_connect(&myCont,"localhost", "1", "1234", "mycont",3306,NULL,0))
    {
        mysql_query(&myCont,"SET NAMES GBK");
loop1:
        printf("输入你要转账的卡号：");
        char card_no[17];
        char card_no_confirm[17];
        char pwd[7];
        fflush(stdin);
        gets(card_no);
        printf("再输一遍：");
        gets(card_no_confirm);
        if(strcmp(card_no,card_no_confirm))
        {
            printf("卡号不一致\n");
            goto loop1;
        }
        char sql[255]= {0};
        sprintf(sql,"select status from cards where cardNo='%s'",card_no);
        mysql_query(&myCont,sql);
        //deal with the result
        result=mysql_store_result(&myCont);
        printf("\n");
        if(mysql_num_rows(result))
        {
            row=mysql_fetch_row(result);
            if(!strcmp(row[0],"挂失状态"))
            {
                printf("卡已被冻结，转账失败\n");
                goto loop1;
            }
            else
                goto loop;
        }
        else
            printf("无此卡\n");
loop:
        printf("输入转账的金额：");
        double money,money1,money2;
        scanf("%lf",&money);
        char sql1[255]= {0};
        sprintf(sql1,"select balance from cards where cardNo='%s'",p);
        mysql_query(&myCont,sql1);
        result=mysql_store_result(&myCont);
        printf("\n");
        row=mysql_fetch_row(result);
        if(atof(row[0])<money)
        {
            printf("余额不足\n");
            printf("\n");
            printf("穷逼\n");
            goto loop;
        }
        else
        {
            money1=atof(row[0])-money;
        }
        char sql2[255]= {0};
        sprintf(sql2,"select balance from cards where cardNo='%s'",card_no);
        mysql_query(&myCont,sql2);
        result=mysql_store_result(&myCont);
        printf("\n");
        row=mysql_fetch_row(result);
        money2=atof(row[0])+money;

        char sql3[255]= {0};
        sprintf(sql3,"update cards set balance='%lf' where cardNo='%s'",money1,p);
        mysql_query(&myCont,sql3);
        char sql4[255]= {0};
        sprintf(sql4,"update cards set balance='%lf' where cardNo='%s'",money2,card_no);
        mysql_query(&myCont,sql4);
        printf("转账成功\n");
        printf("\n");
        printf("当前余额:\n");
        printf("%0.2f",money1);
        //puts(temmmp);
        mysql_free_result(result);
        mysql_close(&myCont);

        //  }
    }
}

int main()
{
    int n;
    printf("是否登陆？\n");
loop1:
    printf("0.登陆：\n");
    printf("1.退出：\n");
    scanf("%d",&n);
    if(n==0)
    {
        printf("输入卡号:");
        char cardNo[17]= {""};
        fflush(stdin);
        gets(cardNo);
        if(Login(cardNo)==1)
        {
loop:
            {
                printf("请选择操作:\n");
                printf("1:查询支出\n");
                printf("2:查询收入\n");
                printf("3:查询余额\n");
                printf("4:查询限额\n");
                printf("5:转账\n");
                printf("0:退出\n");
                printf("\n");

                int operateType;
                scanf("%d",&operateType);

                switch(operateType)
                {
                case 0:
                    printf("退出\n");
                    break;
                case 1:
                    Lookup(cardNo);
                    printf("\n");
                    goto loop;
                case 2:
                    Lookup2(cardNo);
                    printf("\n");
                    goto loop;
                case 3:
                    Balance(cardNo);
                    printf("\n");
                    goto loop;
                case 4:
                    {
                    Limit(cardNo);
                    printf("\n");
                    goto loop;
                    }
                case 5:
                    Transfer(cardNo);
                    printf("\n");
                    goto loop;
                default:
                    printf("输入错误，重新输入\n");
                    goto loop;
                }
            }
        }
        else
            printf("登陆失败\n");
    }
    else if(n==1)
        return 0;
    else
    {
        printf("Error\n");
        goto loop1;
    }
}

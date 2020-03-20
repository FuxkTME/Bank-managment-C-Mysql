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

MYSQL mysql, *sock;   //����MySQL�ľ��
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
            printf("��������(�������λ���):");
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
                    if(!strcmp(row[7],"��ʧ״̬"))
                    {
                        printf("��ѿ�����ʧ��\n");
                        return 0;
                    }
                    else
                    {
                        if(!strcmp(row[3],pwd))
                        {
                            printf("������ȷ\n");
                            return 1;
                        }
                        else
                        {
                            temp1++;
                            printf("�����%d�δ���\n",temp1);
                            if(temp1==3)
                                goto loop1;
                            goto loop;
                        }
                    }
                }
            }
            else
                printf("�޴˿�\n");
            //release the resource
loop1:
            {
                char sql1[255]= {0};
                sprintf(sql1,"update cards set status='��ʧ״̬' where cardNo='%s'",p);
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
            //printf("������Ҫ��ѯ������:");
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
                printf("���ţ�            �˵��ţ�    ����ʱ�䣺          ���׽�   \n");
                while((row=mysql_fetch_row(result)))
                {
                printf("%s||%s||%s||%s||\n",row[0],row[1],row[2],row[3]);
                }
            }
            else
                printf("��֧����¼!\n");
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
            //printf("������Ҫ��ѯ������:");
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
                printf("���ţ�            �˵��ţ�    ����ʱ�䣺          ���׽�   \n");
                while((row=mysql_fetch_row(result)))
                {
                    printf("%s||%s||%s||%s||\n",row[0],row[1],row[2],row[3]);
                }
            }
            else
                printf("�������¼!\n");
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
            printf("��");
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
            printf("�޶");
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
        printf("������Ҫת�˵Ŀ��ţ�");
        char card_no[17];
        char card_no_confirm[17];
        char pwd[7];
        fflush(stdin);
        gets(card_no);
        printf("����һ�飺");
        gets(card_no_confirm);
        if(strcmp(card_no,card_no_confirm))
        {
            printf("���Ų�һ��\n");
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
            if(!strcmp(row[0],"��ʧ״̬"))
            {
                printf("���ѱ����ᣬת��ʧ��\n");
                goto loop1;
            }
            else
                goto loop;
        }
        else
            printf("�޴˿�\n");
loop:
        printf("����ת�˵Ľ�");
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
            printf("����\n");
            printf("\n");
            printf("���\n");
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
        printf("ת�˳ɹ�\n");
        printf("\n");
        printf("��ǰ���:\n");
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
    printf("�Ƿ��½��\n");
loop1:
    printf("0.��½��\n");
    printf("1.�˳���\n");
    scanf("%d",&n);
    if(n==0)
    {
        printf("���뿨��:");
        char cardNo[17]= {""};
        fflush(stdin);
        gets(cardNo);
        if(Login(cardNo)==1)
        {
loop:
            {
                printf("��ѡ�����:\n");
                printf("1:��ѯ֧��\n");
                printf("2:��ѯ����\n");
                printf("3:��ѯ���\n");
                printf("4:��ѯ�޶�\n");
                printf("5:ת��\n");
                printf("0:�˳�\n");
                printf("\n");

                int operateType;
                scanf("%d",&operateType);

                switch(operateType)
                {
                case 0:
                    printf("�˳�\n");
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
                    printf("���������������\n");
                    goto loop;
                }
            }
        }
        else
            printf("��½ʧ��\n");
    }
    else if(n==1)
        return 0;
    else
    {
        printf("Error\n");
        goto loop1;
    }
}

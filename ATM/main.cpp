#include "stdio.h"
#include "stdlib.h"
#include "string.h"
//#include "stdafx.h"
#include "time.h"
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
        if(mysql_real_connect(&myCont,"192.168.137.200","Tobby","1314","bank",3306,NULL,0))
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
                    if(!strcmp(row[70],"��ʧ״̬"))
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

void Balance(char* p)
{
    MYSQL myCont;
    mysql_init(&myCont);
    if(mysql_real_connect(&myCont,"localhost","1","1234","mycont",3306,NULL,0))
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

void Withdraw(char* p)
{
    MYSQL myCont;
    mysql_init(&myCont);
    if(mysql_real_connect(&myCont,"192.168.137.200","Tobby","1314","bank",3306,NULL,0))
    {
        mysql_query(&myCont,"SET NAMES GBK");
        printf("��Ҫȡ����Ǯ:");
        double money;;
        scanf("%lf",&money);
        char sql[255]= {0};
        sprintf(sql,"select balance from cards where cardNo='%s'",p);
        mysql_query(&myCont,sql);
        result=mysql_store_result(&myCont);
        printf("\n");
        while((row=mysql_fetch_row(result)))
        {
            if((atof(row[0])<money))
            {
                printf("��");
                puts(row[0]);
                printf("\n");
                printf("���\n");
            }
            else
            {
                money=atof(row[0])-money;
                printf("�����ɹ�\n");
                printf("\n");
                goto loop;
            }
        }
        //release the resource
loop:
        {
            char sql1[255]= {0};
            sprintf(sql1,"update cards set balance='%lf' where cardNo='%s'",money,p);
            mysql_query(&myCont,sql1);
            printf("ȡǮ�ɹ�\n");
            printf("��%0.2f\n",money);
        }
        mysql_free_result(result);
        mysql_close(&myCont);
    }
}

void Save(char* p)
{
    MYSQL myCont;
    mysql_init(&myCont);
    if(mysql_real_connect(&myCont,"192.168.137.200","Tobby","1314","bank",3306,NULL,0))
    {
        mysql_query(&myCont,"SET NAMES GBK");
        printf("��Ҫ�����Ǯ:");
        double money;
        scanf("%lf",&money);
        char sql[255]= {0};
        sprintf(sql,"select balance from cards where cardNo='%s'",p);
        mysql_query(&myCont,sql);
        result=mysql_store_result(&myCont);
        while((row=mysql_fetch_row(result)))
        {
            money=money+atof(row[0]);
            goto loop;
        }
loop:
        {
            char sql[255]= {0};
            sprintf(sql,"update cards set balance='%lf' where cardNo='%s'",money,p);
            mysql_query(&myCont,sql);
            printf("��Ǯ�ɹ�\n");
            printf("��%0.2f  \n",money);

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
    if(mysql_real_connect(&myCont,"192.168.137.200","Tobby","1314","bank",3306,NULL,0))
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

void chg_pwd(char* p)
{
    MYSQL myCont;
    mysql_init(&myCont);
    if(mysql_real_connect(&myCont,"192.168.137.200","Tobby","1314","bank",3306,NULL,0))
    {
        mysql_query(&myCont,"SET NAMES GBK");
loop1:
        printf("�����룺");
        char new_password[17];
        char new_password_confirm[17];
        fflush(stdin);
        gets(new_password);
        printf("����һ�飺");
        gets(new_password_confirm);
        if(strcmp(new_password,new_password_confirm))
        {
            printf("���벻һ��\n");
            goto loop1;
        }
        char sql[255]= {0};
        sprintf(sql,"update cards set password='%s' where cardNo='%s'",new_password,p);
        mysql_query(&myCont,sql);
        printf("\n");
        printf("������ɹ�\n");

        mysql_free_result(result);
        mysql_close(&myCont);
    }
}
void GUI()
{
    printf("�������ԣ�");
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
                printf("1:��ѯ���\n");
                printf("2:ȡǮ\n");
                printf("3:��Ǯ\n");
                printf("4:ת��\n");
                printf("5:������\n");
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
                    Balance(cardNo);
                    printf("\n");
                    goto loop;
                case 2:
                    Withdraw(cardNo);
                    printf("\n");
                    goto loop;
                case 3:
                    Save(cardNo);
                    printf("\n");
                    goto loop;
                case 4:
                    Transfer(cardNo);
                    printf("\n");
                    goto loop;
                case 5:
                    chg_pwd(cardNo);
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



//

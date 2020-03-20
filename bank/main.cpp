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

enum cardType
{
    DEPOSIT=0,
    CREDIT=1
};//����CardType����
enum cardStatus
{
    FREEZING=0,
    NORMAL=1
};
struct card
{
    char cardNo[17];
    char name[17];
    char phone_num[12];
    char id[19];
    char password[7];
    cardType type;
    double limit;
    cardStatus status;
    double balance;
};


card cards;
char status[7],type[7];
//int currentIndex = 0;

void createString(char* Dest, int length)
{
    int i;
    srand((int)time(NULL));
    for (i = 0; i <length; i++)
    {
        Dest[i]=rand()%10+'0';//�������ÿһλ����
    }
}

void Lookup( )
{
    int temp;
loop:
    {
        MYSQL myCont;
        mysql_init(&myCont);
        if(mysql_real_connect(&myCont,"localhost","1","1234","mycont",3306,NULL,0))
        {
            mysql_query(&myCont,"SET NAMES GBK");
            char* sql="select * from cards where name='";
            char dest[100]= {""};
            strcat(dest,sql);
            printf("������Ҫ��ѯ������:");
            char name[17]= {""};
            fflush(stdin);
            gets(name);
            strcat(dest,name);
            strcat(dest,"'");
            if(mysql_query(&myCont,dest))
            {
                printf("�޴��û�!\n");
                goto loop1;
            }
            //deal with the result
            result=mysql_store_result(&myCont);
            printf("\n");
            if(mysql_num_rows(result))
            {
                while((row=mysql_fetch_row(result)))
                {
                    printf("������%s\n���֤�ţ�%s\n���ţ�%s\n���룺%s\n�ֻ����룺%s\n",row[0],row[1],row[2],row[3],row[4]);
                    if(*row[5]=='0')
                        printf("��������:���\n");
                    else
                        printf("��������:���ÿ�\n");
                    printf("�����޶");
                    puts(row[6]);
                    if(*row[7]=='0')
                        printf("���п�״̬:��ʧ״̬\n");
                    else
                        printf("���п�״̬:����״̬\n");
                    printf("��");
                    puts(row[8]);
                    printf("\n");
                }
            }
            else
                printf("�޴��û�!\n");
            //release the resource
            mysql_free_result(result);
            mysql_close(&myCont);
        }
loop1:
        {
            printf("\n");
            printf("�Ƿ����������\n��:0;��:1\n");
            scanf("%d",&temp);
            switch(temp)
            {
            case 0:
                goto loop;
            case 1:
                return ;
            default:
                printf("Error!\n");
                goto loop1;
            }
        }
    }
}

void Lost()
{
    int temp,temp1,flag=1;
    while(flag==1)
    {
        MYSQL myCont;
        mysql_init(&myCont);
        if(mysql_real_connect(&myCont,"localhost","1","1234","mycont",3306,NULL,0))
        {
loop1:
            {
                mysql_query(&myCont,"SET NAMES GBK");
                char* sql="select status from cards where cardNo='";
                char dest[100]= {""};
                strcat(dest,sql);
                printf("���뿨��:");
                char cardNo[17]= {""};
                fflush(stdin);
                gets(cardNo);
                strcat(dest,cardNo);
                strcat(dest,"'");
                //puts(dest);
                if(mysql_query(&myCont,dest))
                {
                    printf("�޴��û�!\n");
                    goto loop1;
                }
                //deal with the result
                result=mysql_store_result(&myCont);
                printf("\n");
                if(mysql_num_rows(result))
                {
                    while((row=mysql_fetch_row(result)))
                    {
loop2:
                        {
                            int res;
                            char sql2[255]= {0};
                            char* lost="update cards set status=1 where cardNo='";
                            char* unlost="update cards set status=0 where cardNo='";
                            char temmp[100]= {""};
                            char temmmp[100]= {""};
                            strcat(temmp,lost);
                            strcat(temmmp,unlost);
                            strcat(temmp,cardNo);
                            strcat(temmp,"'");
                            strcat(temmmp,cardNo);
                            strcat(temmmp,"'");
                            //puts(temmmp);
                            if(*row[0]=='0')//��ѯ����״̬
                            {
                                printf("���п�״̬:��ʧ״̬\n");
                                printf("\n");
                                printf("�Ƿ�Ҫ���н��ʧ������\n��:0;��:1\n");
                                scanf("%d",&temp1);
                                switch(temp1)
                                {
                                case 0:
                                    res=mysql_query(&myCont,temmp);
                                    if(!res)
                                    {
                                        printf("���ʧ�ɹ�\n");
                                    }
                                    goto loop3;
                                case 1:
                                    goto loop3;
                                default:
                                    printf("Error\n");
                                    goto loop2;
                                }
                            }
                            else
                            {
                                printf("���п�״̬:����״̬\n");
                                printf("\n");
                                printf("�Ƿ�Ҫ���й�ʧ����?\n��:0;��:1\n");
                                scanf("%d",&temp1);
                                switch(temp1)
                                {
                                case 0:
                                    res=mysql_query(&myCont,temmmp);
                                    if(!res)
                                    {
                                        printf("��ʧ�ɹ�\n");
                                    }
                                    goto loop3;
                                case 1:
                                    goto loop3;
                                default:
                                    printf("Error\n");
                                    goto loop2;
                                }
                            }
                        }
                    }
                }
                else
                    printf("�޴��û�!\n");
            }
        }

        //release the resource
        mysql_free_result(result);
        mysql_close(&myCont);

loop3:
        {
            printf("\n");
            printf("�Ƿ����������\n��:0;��:1\n");
            scanf("%d",&temp);
            switch(temp)
            {
            case 0:
                flag=1;
                return ;
            case 1:
                flag=0;
                return ;
            default:
                printf("Error!\n");
                goto loop3;
            }
        }
    }
}


void Delete()
{
    MYSQL myCont;
    mysql_init(&myCont);
    if(mysql_real_connect(&myCont,"localhost","root","","mycont",3306,NULL,0))
    {
        int temp,res,flag=1;
        while(flag==1)
        {
loop1:
            {
                mysql_query(&myCont,"SET NAMES GBK");
                char* sql="select * from cards where cardNo='";
                char dest[100]= {""};
                strcat(dest,sql);
                printf("���뿨��:");
                char cardNo[17]= {""};
                fflush(stdin);
                gets(cardNo);
                strcat(dest,cardNo);
                strcat(dest,"'");
                //puts(dest);
                if(mysql_query(&myCont,dest))
                {
                    printf("�޴��û�!\n");
                    goto loop1;
                }
                //deal with the result
                result=mysql_store_result(&myCont);
                printf("\n");
                if(mysql_num_rows(result))
                    goto loop2;
                else
                {
                    printf("�޴��û�\n");
                    goto loop3;
                }
loop2:
                {
                    char* delete_="delete from cards where cardNo='";
                    char temmp[100]= {""};
                    strcat(temmp,delete_);
                    strcat(temmp,cardNo);
                    strcat(temmp,"'");
                    printf("��ȷ���Ƿ�ע��\n");
                    printf("0:ע��\n");
                    printf("1:ȡ��\n");
                    scanf("%d",&temp);
                    switch(temp)
                    {
                    case 0:
                        res=mysql_query(&myCont,temmp);
                        if(!res)
                        {
                            printf("ע���ɹ�\n");
                        }
                        return ;
                    case 1:
                        goto loop3;
                        return ;
                    default:
                        printf("Error");
                        goto loop2;
                    }
                }
loop3:
                {
                    printf("\n");
                    printf("�Ƿ����������\n��:0;��:1\n");
                    scanf("%d",&temp);
                    switch(temp)
                    {
                    case 0:
                        flag=1;
                        return ;
                    case 1:
                        flag=0;
                        return ;
                    default:
                        printf("Error!\n");
                        goto loop3;
                    }
                }
            }
        }
    }
}

void Run()
{
    int temp;
    MYSQL myCont;
    mysql_init(&myCont);
    if(mysql_real_connect(&myCont,"localhost","root","","mycont",3306,NULL,0))
    {
        mysql_query(&myCont,"SET NAMES GBK");
        printf("�Ƿ�Ҫɾ����·��\n");
        printf("��(1),��(0)");
        scanf("%d",&temp);
        switch(temp)
        {
        case(0):
            printf("������\n");
            return ;
        case(1):
            printf("�����Ŷ���ǾͿ�ʼ��\n");
            char sql[255]= {0};
            sprintf(sql,"delete from cards;");
            int res=mysql_query(&myCont,sql);
            if(!res)
            {
                printf("��·�ɹ�\n");
            }

        }
        mysql_free_result(result);
        mysql_close(&myCont);
    }
}

void createCard()//����
{
    int temp,temp1,flag=1;
loop:
    {
        memset(&cards,0,sizeof(cards));
        createString(cards.cardNo,16);
        printf("�������û�������");
        scanf("%s",cards.name);
        printf("�������û����֤��: ");
        scanf("%s",cards.id);
        printf("�������û��绰���룺");
        scanf("%s",cards.phone_num);
        printf("�������û����룺");
        scanf("%s",cards.password);
loop4:
        {
            printf("�����뿨������(����0Ϊ�����1Ϊ���ÿ�): ");
            scanf("%d",&temp);
            switch(temp)
            {
            case(0):
                cards.type=(cardType)0;
                goto loop2;
            case(1):
                cards.type=(cardType)1;
                goto loop1;
            default:
                printf("�������ʹ���\n");
                goto loop4;
            }
        }
        cards.limit=0;
loop1:
        {
            printf("���������ÿ����: ");
            scanf("%lf",&cards.limit);
        }
loop2:
        {
            printf("���������п���״̬(����0Ϊ��ʧ״̬������Ϊ����״̬): ");
            scanf("%d",&temp);
            switch(temp)
            {
            case(0):
                cards.status=(cardStatus)0;
                break;
            case(1):
                cards.status=(cardStatus)1;
                break;
            default:
                printf("�������ʹ���\n");
                goto loop2;
            }
        }
    }
    cards.balance=0;
    printf("\n");
    printf("�û�����:%s\n�û����֤��:%s\n�û�����:%s\n�û�����:%s\n�û��绰����:%s\n", cards.name,cards.id,cards.cardNo,cards.password,cards.phone_num);
    if(cards.type==(enum cardType)0)
    {
        printf("��������:���\n");
        strcpy(type,"���");
    }
    else
    {
        printf("��������:���ÿ�\n");
        strcpy(type,"���ÿ�");
    }
    printf("���Ķ��:%0.2f\n",cards.limit);
    if(cards.status==(enum cardStatus)0)
    {
        printf("���п�״̬:��ʧ״̬\n");
        strcpy(status,"��ʧ");
    }
    else
    {
         printf("���п�״̬:����״̬\n");
         strcpy(status,"����");
    }
    printf("��%0.2f \n",cards.balance);
    //printf("%c_%c_",cards[currentIndex].status[0],cards[currentIndex].status[1]);
    //currentIndex++;//�������±�����
    MYSQL myCont;
    mysql_init(&myCont);
    if(mysql_real_connect(&myCont,"localhost","1","1234","mycont",3306,NULL,0))
    {
        mysql_query(&myCont,"SET NAMES GBK");
        char sql[255]= {0};
        sprintf(sql,"insert into cards values('%s','%s','%s','%s','%s','%s','%lf','%s','%lf')",cards.name,cards.id,cards.cardNo,cards.password,cards.phone_num,type,cards.limit,status,cards.balance);

        int res=mysql_query(&myCont,sql);
        if(!res)
        {
            printf("\n");
            printf("�����ɹ�\n");
            printf("\n");
        }
    }

loop5:
    {
        printf("�Ƿ����������\n��:0;��:1\n");
        scanf("%d",&temp);
        switch(temp)
        {
        case 0:
            goto loop;
        case 1:
            return ;
        default:
            printf("Error!\n");
            goto loop5;
        }
    }
}
int main()
{

loop:
    {
        printf("��ѡ�����:\n");
        printf("1:����\n");
        printf("2:��ѯ\n");
        printf("3:��ʧ����ʧ\n");
        printf("4:ע��\n");
        printf("9:��·ģʽ\n");
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
            createCard();
            printf("\n");
            //Save();
            goto loop;
        case 2:
            Lookup();
            printf("\n");
            goto loop;
        case 3:
            Lost();
            printf("\n");
            goto loop;
        case 4:
            Delete();
            printf("\n");
            goto loop;
        case 9:
            Run();
            break;
        default:
            printf("���������������\n");
            goto loop;
        }
        return 0;
    }
}

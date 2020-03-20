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

enum cardType
{
    DEPOSIT=0,
    CREDIT=1
};//定义CardType类型
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
        Dest[i]=rand()%10+'0';//随机卡的每一位数字
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
            printf("输入你要查询的姓名:");
            char name[17]= {""};
            fflush(stdin);
            gets(name);
            strcat(dest,name);
            strcat(dest,"'");
            if(mysql_query(&myCont,dest))
            {
                printf("无此用户!\n");
                goto loop1;
            }
            //deal with the result
            result=mysql_store_result(&myCont);
            printf("\n");
            if(mysql_num_rows(result))
            {
                while((row=mysql_fetch_row(result)))
                {
                    printf("姓名：%s\n身份证号：%s\n卡号：%s\n密码：%s\n手机号码：%s\n",row[0],row[1],row[2],row[3],row[4]);
                    if(*row[5]=='0')
                        printf("卡的类型:储蓄卡\n");
                    else
                        printf("卡的类型:信用卡\n");
                    printf("卡的限额：");
                    puts(row[6]);
                    if(*row[7]=='0')
                        printf("银行卡状态:挂失状态\n");
                    else
                        printf("银行卡状态:正常状态\n");
                    printf("余额：");
                    puts(row[8]);
                    printf("\n");
                }
            }
            else
                printf("无此用户!\n");
            //release the resource
            mysql_free_result(result);
            mysql_close(&myCont);
        }
loop1:
        {
            printf("\n");
            printf("是否继续操作？\n是:0;否:1\n");
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
                printf("输入卡号:");
                char cardNo[17]= {""};
                fflush(stdin);
                gets(cardNo);
                strcat(dest,cardNo);
                strcat(dest,"'");
                //puts(dest);
                if(mysql_query(&myCont,dest))
                {
                    printf("无此用户!\n");
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
                            if(*row[0]=='0')//查询卡的状态
                            {
                                printf("银行卡状态:挂失状态\n");
                                printf("\n");
                                printf("是否要进行解挂失操作？\n是:0;否:1\n");
                                scanf("%d",&temp1);
                                switch(temp1)
                                {
                                case 0:
                                    res=mysql_query(&myCont,temmp);
                                    if(!res)
                                    {
                                        printf("解挂失成功\n");
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
                                printf("银行卡状态:正常状态\n");
                                printf("\n");
                                printf("是否要进行挂失操作?\n是:0;否:1\n");
                                scanf("%d",&temp1);
                                switch(temp1)
                                {
                                case 0:
                                    res=mysql_query(&myCont,temmmp);
                                    if(!res)
                                    {
                                        printf("挂失成功\n");
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
                    printf("无此用户!\n");
            }
        }

        //release the resource
        mysql_free_result(result);
        mysql_close(&myCont);

loop3:
        {
            printf("\n");
            printf("是否继续操作？\n是:0;否:1\n");
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
                printf("输入卡号:");
                char cardNo[17]= {""};
                fflush(stdin);
                gets(cardNo);
                strcat(dest,cardNo);
                strcat(dest,"'");
                //puts(dest);
                if(mysql_query(&myCont,dest))
                {
                    printf("无此用户!\n");
                    goto loop1;
                }
                //deal with the result
                result=mysql_store_result(&myCont);
                printf("\n");
                if(mysql_num_rows(result))
                    goto loop2;
                else
                {
                    printf("无此用户\n");
                    goto loop3;
                }
loop2:
                {
                    char* delete_="delete from cards where cardNo='";
                    char temmp[100]= {""};
                    strcat(temmp,delete_);
                    strcat(temmp,cardNo);
                    strcat(temmp,"'");
                    printf("请确认是否注销\n");
                    printf("0:注销\n");
                    printf("1:取消\n");
                    scanf("%d",&temp);
                    switch(temp)
                    {
                    case 0:
                        res=mysql_query(&myCont,temmp);
                        if(!res)
                        {
                            printf("注销成功\n");
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
                    printf("是否继续操作？\n是:0;否:1\n");
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
        printf("是否要删库跑路？\n");
        printf("是(1),否(0)");
        scanf("%d",&temp);
        switch(temp)
        {
        case(0):
            printf("你真怂\n");
            return ;
        case(1):
            printf("你好勇哦，那就开始吧\n");
            char sql[255]= {0};
            sprintf(sql,"delete from cards;");
            int res=mysql_query(&myCont,sql);
            if(!res)
            {
                printf("跑路成功\n");
            }

        }
        mysql_free_result(result);
        mysql_close(&myCont);
    }
}

void createCard()//开户
{
    int temp,temp1,flag=1;
loop:
    {
        memset(&cards,0,sizeof(cards));
        createString(cards.cardNo,16);
        printf("请输入用户姓名：");
        scanf("%s",cards.name);
        printf("请输入用户身份证号: ");
        scanf("%s",cards.id);
        printf("请输入用户电话号码：");
        scanf("%s",cards.phone_num);
        printf("请输入用户密码：");
        scanf("%s",cards.password);
loop4:
        {
            printf("请输入卡的类型(输入0为储蓄卡，1为信用卡): ");
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
                printf("输入类型错误\n");
                goto loop4;
            }
        }
        cards.limit=0;
loop1:
        {
            printf("请输入信用卡额度: ");
            scanf("%lf",&cards.limit);
        }
loop2:
        {
            printf("请输入银行卡的状态(输入0为挂失状态，其他为正常状态): ");
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
                printf("输入类型错误\n");
                goto loop2;
            }
        }
    }
    cards.balance=0;
    printf("\n");
    printf("用户姓名:%s\n用户身份证号:%s\n用户卡号:%s\n用户密码:%s\n用户电话号码:%s\n", cards.name,cards.id,cards.cardNo,cards.password,cards.phone_num);
    if(cards.type==(enum cardType)0)
    {
        printf("卡的类型:储蓄卡\n");
        strcpy(type,"储蓄卡");
    }
    else
    {
        printf("卡的类型:信用卡\n");
        strcpy(type,"信用卡");
    }
    printf("卡的额度:%0.2f\n",cards.limit);
    if(cards.status==(enum cardStatus)0)
    {
        printf("银行卡状态:挂失状态\n");
        strcpy(status,"挂失");
    }
    else
    {
         printf("银行卡状态:正常状态\n");
         strcpy(status,"正常");
    }
    printf("余额：%0.2f \n",cards.balance);
    //printf("%c_%c_",cards[currentIndex].status[0],cards[currentIndex].status[1]);
    //currentIndex++;//开户完下标增加
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
            printf("开户成功\n");
            printf("\n");
        }
    }

loop5:
    {
        printf("是否继续操作？\n是:0;否:1\n");
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
        printf("请选择操作:\n");
        printf("1:开户\n");
        printf("2:查询\n");
        printf("3:挂失与解挂失\n");
        printf("4:注销\n");
        printf("9:跑路模式\n");
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
            printf("输入错误，重新输入\n");
            goto loop;
        }
        return 0;
    }
}

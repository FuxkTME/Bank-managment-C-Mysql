#include <iostream>
#include <iostream>
#include"math.h"
#include<windows.h>
#include <mysql.h>
#pragma comment(lib,"libmysql.lib")
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#define N 10
using namespace std;
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
char n[17];

void createstring(char* dest,int len)
{

    int i;

    srand(time(0));

            for( i=0;i<len;i++)
            //printf("%3d",rand()%9+1);
           {
               *dest++=rand()%10+'0';
                //printf("%d",a[j][i]);
           }
           //printf("您的卡号：");
          // printf("%d",dest);
           //printf("\n");

}



 void depositmoney()
 {
     int flag =0;
     char num[17]={0};
     char pwd[7]={0};
    double i;
     printf("=======================================================================================================================\n");
    printf("输入您的卡号:");
    scanf("%s",num);
     printf("输入您的密码:");
    scanf("%s",pwd);
     MYSQL myCont;
	MYSQL_RES *result;
	MYSQL_ROW sql_row;
	int res;
	double l;

	mysql_init(&myCont);//#1.初始化
	if (mysql_real_connect(&myCont, "localhost", "admin","12345", "bank", 3306, NULL, 0))//#2.连接数据库
	{
		mysql_query(&myCont, "SET NAMES GBK"); //#3.设置编码格式
		char sql[255] = {0};
	   sprintf(sql,"select * from cards where cardNo = '%s' and password = '%s'",num,pwd);
       int res = mysql_query(&myCont,sql);
		result = mysql_store_result(&myCont);//#4.2.1存储查询结果
		if (mysql_num_rows(result))
            {

                    //printf("%s\n",sql_row[5]);
                while (sql_row = mysql_fetch_row(result))
                {
                    printf("请输入您要消费的金额:");
                    scanf("%lf",&i);
                     if(strcmp(sql_row[5],"储蓄卡")==0)
                    {
                    if(i < 0)
                        {
                            printf("error\n");
                            printf("=======================================================================================================================\n");
                        }
                        if (i >= 0)
                        {


                            l=atof(sql_row[8])-i;
                            if(l>=0)
                            {
                                sprintf(sql,"update cards set balance ='%0.2lf' where cardNo = '%s'",l,num);
                                int res = mysql_query(&myCont,sql);
                                printf("支付成功!\n");
                                  printf("=======================================================================================================================\n");
                                flag =1;

                            }
                            else
                            {
                               printf("余额不足!\n");
                                 printf("=======================================================================================================================\n");
                            }

                    }

                }
                else
                {
                        if(i < 0)
                    {
                        printf("error\n");
                          printf("=======================================================================================================================\n");
                    }
                if (i >= 0)
                    {


                            l=atof(sql_row[6])-i;
                            if(l>=0)
                            {
                                sprintf(sql,"update cards set  card_limit ='%0.2lf' where cardNo = '%s'",l,num);
                                int res = mysql_query(&myCont,sql);
                                printf("支付成功!\n");
                                flag = 1;
                                  printf("=======================================================================================================================\n");


                            }
                            else
                            {
                               printf("余额不足!\n");
                                 printf("=======================================================================================================================\n");
                            }

                    }

                }

                }

            }
            else
                printf("卡号或密码不匹配!\n");

            }
                    while(flag)
                     {
                         char sql[250];
                         sprintf(sql,"select now()");
                         res = mysql_query(&myCont,sql);
                        result = mysql_store_result(&myCont);
                         char s[30];
                        while (sql_row = mysql_fetch_row(result))
                        {

                        strcpy(s,sql_row[0]);
                        //printf("%s\n",s);
                        }
                        //time_t timep;
                        //struct tm *p;
                        //time (&timep);
                         //char s[30];
                       // strcpy(s,ctime(&timep));
                        //printf("%s\n",s);
                        char n[11] = {0};
                        createstring(n,10);
                        //char sql[250];
                        sprintf(sql," insert into consumption values('%s','%s','%s','%lf')",num,n,s,i);
                         res = mysql_query(&myCont,sql);
                         flag = 0;
                        //result = mysql_store_result(&myCont);

                    }
               mysql_free_result(result);//4.2.3释放查询结果
                mysql_close(&myCont);

    }




int main(int argc, char* argv[])
{
   // cout << "Hello world!" << endl;
    //return 0;
    printf("欢迎使用！\n");
     int oprate2;
   loop:{
            depositmoney();
        }
    printf("1：继续\n");
    printf("2：离开\n");
    scanf("%d",&oprate2);
    switch(oprate2)
    {
        case 1:
            goto loop;
            break;
        case 2:

            break;
            default:

            break;
    }


}

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
           //printf("���Ŀ��ţ�");
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
    printf("�������Ŀ���:");
    scanf("%s",num);
     printf("������������:");
    scanf("%s",pwd);
     MYSQL myCont;
	MYSQL_RES *result;
	MYSQL_ROW sql_row;
	int res;
	double l;

	mysql_init(&myCont);//#1.��ʼ��
	if (mysql_real_connect(&myCont, "localhost", "admin","12345", "bank", 3306, NULL, 0))//#2.�������ݿ�
	{
		mysql_query(&myCont, "SET NAMES GBK"); //#3.���ñ����ʽ
		char sql[255] = {0};
	   sprintf(sql,"select * from cards where cardNo = '%s' and password = '%s'",num,pwd);
       int res = mysql_query(&myCont,sql);
		result = mysql_store_result(&myCont);//#4.2.1�洢��ѯ���
		if (mysql_num_rows(result))
            {

                    //printf("%s\n",sql_row[5]);
                while (sql_row = mysql_fetch_row(result))
                {
                    printf("��������Ҫ���ѵĽ��:");
                    scanf("%lf",&i);
                     if(strcmp(sql_row[5],"���")==0)
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
                                printf("֧���ɹ�!\n");
                                  printf("=======================================================================================================================\n");
                                flag =1;

                            }
                            else
                            {
                               printf("����!\n");
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
                                printf("֧���ɹ�!\n");
                                flag = 1;
                                  printf("=======================================================================================================================\n");


                            }
                            else
                            {
                               printf("����!\n");
                                 printf("=======================================================================================================================\n");
                            }

                    }

                }

                }

            }
            else
                printf("���Ż����벻ƥ��!\n");

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
               mysql_free_result(result);//4.2.3�ͷŲ�ѯ���
                mysql_close(&myCont);

    }




int main(int argc, char* argv[])
{
   // cout << "Hello world!" << endl;
    //return 0;
    printf("��ӭʹ�ã�\n");
     int oprate2;
   loop:{
            depositmoney();
        }
    printf("1������\n");
    printf("2���뿪\n");
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

#include <stdio.h>
 #include <stdlib.h>
 #include <winsock.h>
 #include <mysql.h>  //����MySQL����Ҫ��ͷ�ļ�
 #include <WinSock2.h> //Socket������MySQLҲ��Ҫ�õ�


 MYSQL mysql, *sock;   //����MySQL�ľ��

 int main(void)
 {
     const char * host = "127.0.0.1";  //��Ϊ����Ϊ�������ԣ�������д���Ǳ���IP
     const char * user = "root";       //�����Ϊ����û�����������MySQL���û���
     const char * passwd = "root"; //�����Ϊ����û�����
     const char * db = "bookstore";      //�����Ϊ��Ҫ���ӵ����ݿ������
     unsigned int port = 3306;           //����MySQL�ķ������Ķ˿ڣ������û���޸Ĺ��Ļ�����3306��
     const char * unix_socket = NULL;    //unix_socket����unix�µģ�����Windows�£����ԾͰ�������ΪNULL
     unsigned long client_flag = 0;      //�������һ��Ϊ0

     const char * i_query = "select * from user"; //��ѯ���

     MYSQL_RES * result;                          //���������� www.2cto.com
     MYSQL_ROW row;                               //������ǽ�����е�һ��

     mysql_init(&mysql);                          //����֮ǰ����ʹ�������������ʼ��
     if ( (sock = mysql_real_connect(&mysql, host, user, passwd, db, port, unix_socket, client_flag) ) == NULL ) //����MySQL
     {
         printf("����ʧ�ܣ�ԭ����: \n");
         fprintf(stderr, " %s\n", mysql_error(&mysql));
         exit(1);
     }
     else
     {
         fprintf(stderr, "����MySQL�ɹ�����\n");
     }

     if ( mysql_query(&mysql, i_query) != 0 )       //������ӳɹ�����ʼ��ѯ
     {
         fprintf(stderr, "��ѯʧ�ܣ�\n");
         exit(1);
     }
     else
     {
         if ( (result = mysql_store_result(&mysql)) == NULL ) //�����ѯ�Ľ��
         {
             fprintf(stderr, "��������ʧ�ܣ�\n");
             exit(1);
         }
         else
         {
             while ( (row = mysql_fetch_row(result)) != NULL ) //��ȡ������е����ݣ����ص�����һ�С���Ϊ��������ʱ����ǰ���α��ڵ�һ�С�֮ǰ��
             {
                 printf("name is %s\t", row[0]);               //��ӡ��ǰ�еĵ�һ�е�����
                 printf("age is %s\t\n", row[1]);              //��ӡ��ǰ�еĵڶ��е�����
             }
         }

     }
     mysql_free_result(result);                                //�ͷŽ����
     mysql_close(sock);                                        //�ر�����
     system("pause");
     exit(EXIT_SUCCESS);
 }

/*
 * =====================================================================================
 *
 *       Filename:  1.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/06/2013 01:21:26 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lemon (zyl), lemon_wonder@163.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include<mysql/mysql.h>
#include<cstdio>

int main()

{

     MYSQL mysql;

     MYSQL_RES *res;

     MYSQL_ROW row;

     char query[] = "select * from person;";

     int t,r;

     mysql_init(&mysql);

     if(!mysql_real_connect(&mysql,"localhost","root",
                     "go","test",0,NULL,0))
     {
         printf("Error connecting to database:%s\n",mysql_error(&mysql));
     }

     else
         printf("Connected........");

     char temp[] = "insert into person values(14, 'Lisa');";
     mysql_query(&mysql, temp);
     t=mysql_query(&mysql,query);

     if(t)
     {

         printf("Error making query:%s\n",mysql_error(&mysql));

     }
     else
     {
         printf("Query made ....\n");

         res = mysql_use_result(&mysql);

         if(res)
         {
             for(r=0;r<=mysql_field_count(&mysql);r++)
             {
                 row = mysql_fetch_row(res);

                 if(row<0) break;

                 for(t=0;t<mysql_num_fields(res);t++)

                     printf("%s ",row[t]);

                 printf("\n");

             }

         }
         mysql_free_result(res);
     }
     mysql_close(&mysql);

     return 0;

 }


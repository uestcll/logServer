/*
 * =====================================================================================
 *
 *       Filename:  CLSQL.h
 *
 *    Description: 
 *
 *        Version:  1.0
 *        Created:  2013/9/13 12:17:36
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lemon (lemon), lemon_wonder@163.com
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef CLSQL_H
#define CLSQL_H

#include <mysql/mysql.h>
class CLSQL
{
    public:
        static CLSQL* getInstance();
        void connectSQL(const char *hostname, const char *username, const char *password, const char *dbname, const int port);
        int querySQL(const char *query);
        MYSQL_RES* getResult();
    private:
        explicit CLSQL();
        ~CLSQL();

    private:
        static CLSQL *m_pSQL;
        MYSQL m_sql;
        MYSQL_RES *m_result;
        MYSQL_FIELD *m_fd;
        MYSQL_ROW m_row;
        //char m_querybuffer[300];
};
#endif

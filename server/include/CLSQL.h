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
#include <iostream>
#include <vector>
#include <string>
using namespace std;
//#include "LibNetWork.h"

class CLSQL
{
    public:
        static CLSQL* getInstance();
        void connectSQL(const char *hostname, const char *username, const char *password, const char *dbname);
        int querySQL(const char *query);
        void fetchResult();
        vector<string> getResult();
        void closeSQL();
        void clearResult();
        void setParameter(string hostname, string name, string password, string databasename);
    private:
        explicit CLSQL();
        ~CLSQL();

    private:
        static CLSQL *m_pSQL;
        MYSQL m_sql;
        MYSQL_RES *m_res;
        MYSQL_ROW m_row;
        vector<string> m_store;
        string m_hostname;
        string m_name;
        string m_password;
        string m_databasename;
};

#endif

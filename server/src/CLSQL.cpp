/*
 * =====================================================================================
 *
 *       Filename:  CLSQL.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013/9/15 20:43:01
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lemon (lemon), lemon_wonder@163.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include "../include/CLSQL.h"

CLSQL* CLSQL::m_pSQL = NULL;

CLSQL* CLSQL::getInstance()
{
    if(NULL == m_pSQL)
    {
        m_pSQL = new CLSQL();
    }

    return m_pSQL;
}

void CLSQL::connectSQL(const char *hostname, const char *username, const char *password, const char *dbname)
{
    mysql_init(m_sql);
    mysql_real_connect(m_sql, hostname, username, password, dbname, 0, NULL, 0);
}

int CLSQL::querySQL(const char *query)
{
    return mysql_query(m_sql, query);
}

void CLSQL::fetchResult()
{
     m_sqlres = mysql_store_result(&m_sql);
     if(m_sqlres)
     {
         while((m_row = mysql_fetch_row(m_sqlres)))
         {}
     }

}

vector<string> CLSQL::getResult()
{
    fetchResult();
    int cnt = 0;
    while(cnt < mysql_field_count(m_sql))
    {
        m_result.push_back(m_row[cnt]);
        cnt++;
    }

    return m_result;
}

CLSQL::CLSQL()
{

}

CLSQL::~CLSQL()
{

}

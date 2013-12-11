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

void CLSQL::connectSQL()
{
    if("" == m_hostname)
    {
        cerr << "error connecting to database : " << mysql_error(&m_sql) << endl;
        return;
    }
    mysql_init(&m_sql);
    if(!mysql_real_connect(&m_sql, m_hostname.c_str(), m_name, m_password, m_databasename, 0, NULL, 0))
    {
        cerr << "error connecting to database : " << mysql_error(&m_sql) << endl;
    }
}

int CLSQL::querySQL(const char *query)
{
    int ret = mysql_query(&m_sql, query);
    if(ret)
    {
        cerr << "error query : " << mysql_error(&m_sql) << endl;
    }

    return ret;
}

void CLSQL::fetchResult()
{
     m_res = mysql_use_result(&m_sql);
     if(m_res)
     {
         for(int i = 0; i < mysql_field_count(&m_sql); ++i)
         {
             m_row = mysql_fetch_row(m_res);
             if(m_row < 0) 
                 break;
             for(int j = 0; j < mysql_num_fields(m_res); ++j)
             {
                 string s = "";
                 s = m_row[j];
                 m_store.push_back(s);
             }
         }
     }
     mysql_free_result(m_res);
}

vector<string> CLSQL::getResult()
{
    clearResult();
    fetchResult();
    
    return m_store;
}

void CLSQL::closeSQL()
{
    mysql_close(&m_sql);
}

void CLSQL::clearResult()
{
    m_store.clear();
}

CLSQL::CLSQL()
{

}

CLSQL::~CLSQL()
{
    mysql_close(&m_sql);
}

void CLSQL::setParameter(string hostname, string name, string password, string databasename)
{
    m_hostname = hostname;
    m_name = name;
    m_password = password;
    m_databasename = databasename;
}

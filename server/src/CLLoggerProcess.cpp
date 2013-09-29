/*
 * =====================================================================================
 *
 *       Filename:  CLLoggerProcess.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  09/29/2013 04:22:08 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lemon (zyl), lemon_wonder@163.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include "../include/CLLoggerProcess.h"

CLLoggerProcess::CLLoggerProcess()
{
}

CLLoggerProcess::~CLLoggerProcess()
{
}

void CLLoggerProcess::work()
{
    string query;
    query = "insert into lemon values";
    query += m_request.readbuffer;
    CLSQL *pSQL = CLSQL::getInstance();
    pSQL->querySQL(query.c_str());
}

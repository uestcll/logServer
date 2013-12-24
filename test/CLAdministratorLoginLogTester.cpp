/*
 * =====================================================================================
 *
 *       Filename:  CLAdministratorLoginLogTester.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  12/23/2013 10:25:33 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lemon (lemon), lemon_wonder@163.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <gtest/gtest.h>
#include "../Message/CLAdministratorLoginLog.h"
#include "../Message/CLLogHead.h"
#include "../server/include/CLSQL.h"

TEST(CLAdministratorLoginLog, serializeAnddeserialize)
{
	CLLogHead head;
    char *ch = new char[6];
    memcpy(ch, "hello", 5);
    ch[5] = '\0';
    head.init(110, 1, 5, ch, 1, 1);
    CLAdministratorLoginLog Log;
    Log.init(1, 2, 4, 5, ch);
    char *buffer = Log.serialize();
    CLAdministratorLoginLog testLog;
    testLog.deserialize(buffer);
    EXPECT_TRUE(testLog == Log);
    delete[] buffer;
    string query;
    query = head.insertToSQL("CLAdministratorLoginLog");
    query += Log.insertToSQL();
    CLSQL *pSQL = CLSQL::getInstance();
    pSQL->querySQL(query.c_str());
    query = "select * from CLAdministratorLoginLog limit 1 offset 0;";
    pSQL->querySQL(query.c_str());
    pSQL->getResult();
    CLLogHead temphead;
    int n = temphead.getResultFromSQL();
    EXPECT_TRUE(temphead == head);
    CLAdministratorLoginLog templog;
    templog.getResultFromSQL(n);
    EXPECT_TRUE(templog == Log);
}

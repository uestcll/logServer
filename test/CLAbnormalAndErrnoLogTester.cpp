/*
 * =====================================================================================
 *
 *       Filename:  CLAbnormalAndErrnoLogTester.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  12/11/13 17:08:20
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:   (), 
 *        Company:  NDSL UESTC
 *
 * =====================================================================================
 */
#include <gtest/gtest.h>
#include "../Message/CLAbnormalAndErrnoLog.h"
#include "../Message/CLLogHead.h"
#include "../server/include/CLSQL.h"

TEST(CLAbnormalAndErrnoLog, serializeAnddeserialize)
{
    CLLogHead head;
    char *ch = new char[6];
    memcpy(ch, "hello", 5);
    ch[5] = '\0';
    head.init(300, 1, 5, ch, 1, 1);
    char *buffer = head.serialize();
    delete[] buffer;
    memcpy(ch, "nice!", 5);
    CLAbnormalAndErrnoLog Log;
    Log.init(5, ch);
    buffer = Log.serialize();
    CLAbnormalAndErrnoLog testLog;
    testLog.deserialize(buffer);
    EXPECT_TRUE(testLog == Log);
    delete[] buffer;
    string query;
    query = head.insertToSQL("CLAbnormalAndErrnoLog");
    query += Log.insertToSQL();
    CLSQL *pSQL = CLSQL::getInstance();
    pSQL->querySQL(query.c_str());
    query = "select * from CLAbnormalAndErrnoLog limit 1 offset 0;";
    pSQL->querySQL(query.c_str());
    pSQL->getResult();
    CLLogHead temphead;
    int n = temphead.getResultFromSQL();
    EXPECT_TRUE(temphead == head);
    CLAbnormalAndErrnoLog templog;
    templog.getResultFromSQL(n);
    EXPECT_TRUE(templog == Log);
}

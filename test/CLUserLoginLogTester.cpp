#include <gtest/gtest.h>
#include "../Message/CLUserLoginLog.h"
#include "../Message/CLLogHead.h"
#include "../server/include/CLSQL.h"

TEST(CLUserLoginLog, serializeAnddeserialize)
{
    CLLogHead head;
    char *ch = new char[6];
    memcpy(ch, "hello", 5);
    ch[5] = '\0';
    head.init(2, 1, 5, ch, 1, 1);
    CLUserLoginLog Log;
    Log.init(1, 2, 4, 11, "192.168.1.1");
    char *buffer = Log.serialize();
    CLUserLoginLog testLog;
    testLog.deserialize(buffer);
    EXPECT_TRUE(testLog == Log);
    delete[] buffer;
    string query;
    query = head.insertToSQL("CLUserLoginLog");
    query += Log.insertToSQL();
    CLSQL *pSQL = CLSQL::getInstance();
    pSQL->querySQL(query.c_str());
    query = "select * from CLUserLoginLog limit 1 offset 0;";
    pSQL->querySQL(query.c_str());
    pSQL->getResult();
    CLLogHead temphead;
    int n = temphead.getResultFromSQL();
    EXPECT_TRUE(temphead == head);
    CLUserLoginLog templog;
    templog.getResultFromSQL(n);
    EXPECT_TRUE(templog == Log);
}
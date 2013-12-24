#include <gtest/gtest.h>
#include "../Message/CLSubordinateAccountLog.h"
#include "../Message/CLLogHead.h"
#include "../server/include/CLSQL.h"

TEST(CLSubordinateAccountLog, serializeAnddeserialize)
{
    CLLogHead head;
    char *ch = new char[6];
    memcpy(ch, "hello", 5);
    ch[5] = '\0';
    head.init(104, 1, 5, ch, 1, 1);
    CLSubordinateAccountLog Log;
    Log.init(1, 2, 3, 4);
    char *buffer = Log.serialize();
    CLSubordinateAccountLog testLog;
    testLog.deserialize(buffer);
    EXPECT_TRUE(testLog == Log);
    delete[] buffer;
    string query;
    query = head.insertToSQL("CLSubordinateAccountLog");
    query += Log.insertToSQL();
    CLSQL *pSQL = CLSQL::getInstance();
    pSQL->querySQL(query.c_str());
    query = "select * from CLSubordinateAccountLog limit 1 offset 0;";
    pSQL->querySQL(query.c_str());
    pSQL->getResult();
    CLLogHead temphead;
    int n = temphead.getResultFromSQL();
    EXPECT_TRUE(temphead == head);
    CLSubordinateAccountLog templog;
    templog.getResultFromSQL(n);
    EXPECT_TRUE(templog == Log);
}
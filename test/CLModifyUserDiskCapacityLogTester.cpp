#include <gtest/gtest.h>
#include "../Message/CLModifyUserDiskCapacityLog.h"
#include "../Message/CLLogHead.h"
#include "../server/include/CLSQL.h"

TEST(CLModifyUserDiskCapacityLog, serializeAnddeserialize)
{
    CLLogHead head;
    char *ch = new char[6];
    memcpy(ch, "hello", 5);
    ch[5] = '\0';
    head.init(126, 1, 5, ch, 1, 1);
    CLModifyUserDiskCapacityLog Log;
    Log.init(1, 2, 3, 4, 5, 6, 7);
    char *buffer = Log.serialize();
    CLModifyUserDiskCapacityLog testLog;
    testLog.deserialize(buffer);
    EXPECT_TRUE(testLog == Log);
    delete[] buffer;
    string query;
    query = head.insertToSQL("CLModifyUserDiskCapacityLog");
    query += Log.insertToSQL();
    CLSQL *pSQL = CLSQL::getInstance();
    pSQL->querySQL(query.c_str());
    query = "select * from CLModifyUserDiskCapacityLog limit 1 offset 0;";
    pSQL->querySQL(query.c_str());
    pSQL->getResult();
    CLLogHead temphead;
    int n = temphead.getResultFromSQL();
    EXPECT_TRUE(temphead == head);
    CLModifyUserDiskCapacityLog templog;
    templog.getResultFromSQL(n);
    EXPECT_TRUE(templog == Log);
}
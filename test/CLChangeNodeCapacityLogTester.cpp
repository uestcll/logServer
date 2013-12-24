#include <gtest/gtest.h>
#include "../Message/CLChangeNodeCapacityLog.h"
#include "../Message/CLLogHead.h"
#include "../server/include/CLSQL.h"

TEST(CLChangeNodeCapacityLog, serializeAnddeserialize)
{
	CLLogHead head;
    char *ch = new char[6];
    memcpy(ch, "hello", 5);
    ch[5] = '\0';
    head.init(202, 1, 5, ch, 1, 1);
    CLChangeNodeCapacityLog Log;
    Log.init(4, 11, "192.168.1.1", 5, "lemon", 10, 20);
    char *buffer = Log.serialize();
    CLChangeNodeCapacityLog testLog;
    testLog.deserialize(buffer);
    EXPECT_TRUE(testLog == Log);
    delete[] buffer;
    string query;
    query = head.insertToSQL("CLChangeNodeCapacityLog");
    query += Log.insertToSQL();
    CLSQL *pSQL = CLSQL::getInstance();
    pSQL->querySQL(query.c_str());
    query = "select * from CLChangeNodeCapacityLog limit 1 offset 0;";
    pSQL->querySQL(query.c_str());
    pSQL->getResult();
    CLLogHead temphead;
    int n = temphead.getResultFromSQL();
    EXPECT_TRUE(temphead == head);
    CLChangeNodeCapacityLog templog;
    templog.getResultFromSQL(n);
    EXPECT_TRUE(templog == Log);
}
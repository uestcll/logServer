#include <gtest/gtest.h>
#include "../Message/CLServerStatusLog.h"
#include "../Message/CLLogHead.h"
#include "../server/include/CLSQL.h"

TEST(CLServerStatusLog, serializeAnddeserialize)
{
    CLLogHead head;
    char *ch = new char[6];
    memcpy(ch, "hello", 5);
    ch[5] = '\0';
    head.init(200, 1, 5, ch, 1, 1);
    CLServerStatusLog Log;
    Log.init(4, 11, "192.168.1.1", 3, "Tom", 80, 100, 4000);
    char *buffer = Log.serialize();
    CLServerStatusLog testLog;
    testLog.deserialize(buffer);
    EXPECT_TRUE(testLog == Log);
    delete[] buffer;
    string query;
    query = head.insertToSQL("CLServerStatusLog");
    query += Log.insertToSQL();
    CLSQL *pSQL = CLSQL::getInstance();
    pSQL->querySQL(query.c_str());
    query = "select * from CLServerStatusLog limit 1 offset 0;";
    pSQL->querySQL(query.c_str());
    pSQL->getResult();
    CLLogHead temphead;
    int n = temphead.getResultFromSQL();
    EXPECT_TRUE(temphead == head);
    CLServerStatusLog templog;
    templog.getResultFromSQL(n);
    EXPECT_TRUE(templog == Log);
}
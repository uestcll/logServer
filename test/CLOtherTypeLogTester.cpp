#include <gtest/gtest.h>
#include "../Message/CLOtherTypeLog.h"
#include "../Message/CLLogHead.h"
#include "../server/include/CLSQL.h"

TEST(CLOtherTypeLog, serializeAnddeserialize)
{
    CLLogHead head;
    char *ch = new char[6];
    memcpy(ch, "hello", 5);
    ch[5] = '\0';
    head.init(400, 1, 5, ch, 1, 1);
    CLOtherTypeLog Log;
    Log.init(5, "hello");
    char *buffer = Log.serialize();
    CLOtherTypeLog testLog;
    testLog.deserialize(buffer);
    EXPECT_TRUE(testLog == Log);
    delete[] buffer;
    string query;
    query = head.insertToSQL("CLOtherTypeLog");
    query += Log.insertToSQL();
    CLSQL *pSQL = CLSQL::getInstance();
    pSQL->querySQL(query.c_str());
    query = "select * from CLOtherTypeLog limit 1 offset 0;";
    pSQL->querySQL(query.c_str());
    pSQL->getResult();
    CLLogHead temphead;
    int n = temphead.getResultFromSQL();
    EXPECT_TRUE(temphead == head);
    CLOtherTypeLog templog;
    templog.getResultFromSQL(n);
    EXPECT_TRUE(templog == Log);
}
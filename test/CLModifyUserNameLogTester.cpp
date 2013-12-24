#include <gtest/gtest.h>
#include "../Message/CLModifyUserNameLog.h"
#include "../Message/CLLogHead.h"
#include "../server/include/CLSQL.h"

TEST(CLModifyUserNameLog, serializeAnddeserialize)
{
    CLLogHead head;
    char *ch = new char[6];
    memcpy(ch, "hello", 5);
    ch[5] = '\0';
    head.init(122, 1, 5, ch, 1, 1);
    CLModifyUserNameLog Log;
    Log.init(1, 2, 3, 4, 5, "lemon", 4, "love");
    char *buffer = Log.serialize();
    CLModifyUserNameLog testLog;
    testLog.deserialize(buffer);
    EXPECT_TRUE(testLog == Log);
    delete[] buffer;
    string query;
    query = head.insertToSQL("CLModifyUserNameLog");
    query += Log.insertToSQL();
    CLSQL *pSQL = CLSQL::getInstance();
    pSQL->querySQL(query.c_str());
    query = "select * from CLModifyUserNameLog limit 1 offset 0;";
    pSQL->querySQL(query.c_str());
    pSQL->getResult();
    CLLogHead temphead;
    int n = temphead.getResultFromSQL();
    EXPECT_TRUE(temphead == head);
    CLModifyUserNameLog templog;
    templog.getResultFromSQL(n);
    EXPECT_TRUE(templog == Log);
}
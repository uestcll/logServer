#include <gtest/gtest.h>
#include "../Message/CLModifyPasswordLog.h"
#include "../Message/CLLogHead.h"
#include "../server/include/CLSQL.h"

TEST(CLModifyPasswordLog, serializeAnddeserialize)
{
    CLLogHead head;
    char *ch = new char[6];
    memcpy(ch, "hello", 5);
    ch[5] = '\0';
    head.init(118, 1, 5, ch, 1, 1);
    CLModifyPasswordLog Log;
    Log.init(11, 12);
    char *buffer = Log.serialize();
    delete[] buffer;
    string query;
    query = head.insertToSQL("CLModifyPasswordLog");
    query += Log.insertToSQL();
    CLSQL *pSQL = CLSQL::getInstance();
    pSQL->querySQL(query.c_str());
    query = "select * from CLModifyPasswordLog limit 1 offset 0;";
    pSQL->querySQL(query.c_str());
    pSQL->getResult();
    CLLogHead temphead;
    int n = temphead.getResultFromSQL();
    EXPECT_TRUE(temphead == head);
    CLModifyPasswordLog templog;
    templog.getResultFromSQL(n);
    EXPECT_TRUE(templog == Log);
}
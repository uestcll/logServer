#include <gtest/gtest.h>
#include "../Message/CLDiskForUserLog.h"
#include "../Message/CLLogHead.h"
#include "../server/include/CLSQL.h"

TEST(CLDiskForUserLog, serializeAnddeserialize)
{
	CLLogHead head;
    char *ch = new char[6];
    memcpy(ch, "hello", 5);
    ch[5] = '\0';
    head.init(114, 1, 5, ch, 1, 1);
    CLDiskForUserLog Log;
    Log.init(7, 8, 9, 10, 11);
    char *buffer = Log.serialize();
    CLDiskForUserLog testLog;
    testLog.deserialize(buffer);
    EXPECT_TRUE(testLog == Log);
    delete[] buffer;
    string query;
    query = head.insertToSQL("CLDiskForUserLog");
    query += Log.insertToSQL();
    CLSQL *pSQL = CLSQL::getInstance();
    pSQL->querySQL(query.c_str());
    query = "select * from CLDiskForUserLog limit 1 offset 0;";
    pSQL->querySQL(query.c_str());
    pSQL->getResult();
    CLLogHead temphead;
    int n = temphead.getResultFromSQL();
    EXPECT_TRUE(temphead == head);
    CLDiskForUserLog templog;
    templog.getResultFromSQL(n);
    EXPECT_TRUE(templog == Log);
}
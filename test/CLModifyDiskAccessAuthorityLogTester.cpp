#include <gtest/gtest.h>
#include "../Message/CLModifyDiskAccessAuthorityLog.h"
#include "../Message/CLLogHead.h"
#include "../server/include/CLSQL.h"

TEST(CLModifyDiskAccessAuthorityLog, serializeAnddeserialize)
{
	CLLogHead head;
    char *ch = new char[6];
    memcpy(ch, "hello", 5);
    ch[5] = '\0';
    head.init(120, 1, 5, ch, 1, 1);
    CLModifyDiskAccessAuthorityLog Log;
    Log.init(4, 5, 6);
    char *buffer = Log.serialize();
    CLModifyDiskAccessAuthorityLog testLog;
    testLog.deserialize(buffer);
    EXPECT_TRUE(testLog == Log);
    delete[] buffer;
    string query;
    query = head.insertToSQL("CLModifyDiskAccessAuthorityLog");
    query += Log.insertToSQL();
    CLSQL *pSQL = CLSQL::getInstance();
    pSQL->querySQL(query.c_str());
    query = "select * from CLModifyDiskAccessAuthorityLog limit 1 offset 0;";
    pSQL->querySQL(query.c_str());
    pSQL->getResult();
    CLLogHead temphead;
    int n = temphead.getResultFromSQL();
    EXPECT_TRUE(temphead == head);
    CLModifyDiskAccessAuthorityLog templog;
    templog.getResultFromSQL(n);
    EXPECT_TRUE(templog == Log);
}
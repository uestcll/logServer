#include <gtest/gtest.h>
#include "../Message/CLChangeNodeDiskLog.h"
#include "../Message/CLLogHead.h"
#include "../server/include/CLSQL.h"

TEST(CLChangeNodeDiskLog, serializeAnddeserialize)
{
	CLLogHead head;
    char *ch = new char[6];
    memcpy(ch, "hello", 5);
    ch[5] = '\0';
    head.init(206, 1, 5, ch, 1, 1);
    CLChangeNodeDiskLog Log;
    Log.init(4, 11, "192.167.1.8", 5, "lemon", 20, 30);
    char *buffer = Log.serialize();
    delete[] buffer;
    string query;
    query = head.insertToSQL("CLChangeNodeDiskLog");
    query += Log.insertToSQL();
    CLSQL *pSQL = CLSQL::getInstance();
    pSQL->querySQL(query.c_str());
    query = "select * from CLChangeNodeDiskLog limit 1 offset 0;";
    pSQL->querySQL(query.c_str());
    pSQL->getResult();
    CLLogHead temphead;
    int n = temphead.getResultFromSQL();
    EXPECT_TRUE(temphead == head);
    CLChangeNodeDiskLog templog;
    templog.getResultFromSQL(n);
    EXPECT_TRUE(templog == Log);
}
#include <gtest/gtest.h>
#include "../Message/CLDiskForDepartmentLog.h"
#include "../Message/CLLogHead.h"
#include "../server/include/CLSQL.h"

TEST(CLDiskForDepartmentLog, serializeAnddeserialize)
{
	CLLogHead head;
    char *ch = new char[6];
    memcpy(ch, "hello", 5);
    ch[5] = '\0';
    head.init(116, 1, 5, ch, 1, 1);
    CLDiskForDepartmentLog Log;
    Log.init(7, 8, 9, 10);
    char *buffer = Log.serialize();
    CLDiskForDepartmentLog testLog;
    testLog.deserialize(buffer);
    EXPECT_TRUE(testLog == Log);
    delete[] buffer;
    string query;
    query = head.insertToSQL("CLDiskForDepartmentLog");
    query += Log.insertToSQL();
    CLSQL *pSQL = CLSQL::getInstance();
    pSQL->querySQL(query.c_str());
    query = "select * from CLDiskForDepartmentLog limit 1 offset 0;";
    pSQL->querySQL(query.c_str());
    pSQL->getResult();
    CLLogHead temphead;
    int n = temphead.getResultFromSQL();
    EXPECT_TRUE(temphead == head);
    CLDiskForDepartmentLog templog;
    templog.getResultFromSQL(n);
    EXPECT_TRUE(templog == Log);
}
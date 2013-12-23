#include <gtest/gtest.h>
#include "../Message/CLSubordinateDepartmentAccountLog.h"
#include "../Message/CLLogHead.h"
#include "../server/include/CLSQL.h"

TEST(CLSubordinateDepartmentAccountLog, serializeAnddeserialize)
{
    CLLogHead head;
    char *ch = new char[6];
    memcpy(ch, "hello", 5);
    ch[5] = '\0';
    head.init(108, 1, 5, ch, 1, 1);
    CLSubordinateDepartmentAccountLog Log;
    Log.init(1, 2, 3);
    char *buffer = Log.serialize();
    delete[] buffer;
    string query;
    query = head.insertToSQL("CLSubordinateDepartmentAccountLog");
    query += Log.insertToSQL();
    CLSQL *pSQL = CLSQL::getInstance();
    pSQL->querySQL(query.c_str());
    query = "select * from CLSubordinateDepartmentAccountLog limit 1 offset 0;";
    pSQL->querySQL(query.c_str());
    pSQL->getResult();
    CLLogHead temphead;
    int n = temphead.getResultFromSQL();
    EXPECT_TRUE(temphead == head);
    CLSubordinateDepartmentAccountLog templog;
    templog.getResultFromSQL(n);
    EXPECT_TRUE(templog == Log);
}
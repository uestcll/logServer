#include <gtest/gtest.h>
#include "../Message/CLModifyDepartmentNameLog.h"
#include "../Message/CLLogHead.h"
#include "../server/include/CLSQL.h"

TEST(CLModifyDepartmentNameLog, serializeAnddeserialize)
{
	CLLogHead head;
    char *ch = new char[6];
    memcpy(ch, "hello", 5);
    ch[5] = '\0';
    head.init(121, 1, 5, ch, 1, 1);
    CLModifyDepartmentNameLog Log;
    Log.init(3, 4, 5, 4, "Mary", 3, "Ann");
    char *buffer = Log.serialize();
    CLModifyDepartmentNameLog testLog;
    testLog.deserialize(buffer);
    EXPECT_TRUE(testLog == Log);
    delete[] buffer;
    string query;
    query = head.insertToSQL("CLModifyDepartmentNameLog");
    query += Log.insertToSQL();
    CLSQL *pSQL = CLSQL::getInstance();
    pSQL->querySQL(query.c_str());
    query = "select * from CLModifyDepartmentNameLog limit 1 offset 0;";
    pSQL->querySQL(query.c_str());
    pSQL->getResult();
    CLLogHead temphead;
    int n = temphead.getResultFromSQL();
    EXPECT_TRUE(temphead == head);
    CLModifyDepartmentNameLog templog;
    templog.getResultFromSQL(n);
    EXPECT_TRUE(templog == Log);
}
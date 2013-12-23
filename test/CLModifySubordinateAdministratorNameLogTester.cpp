#include <gtest/gtest.h>
#include "../Message/CLModifySubordinateAdministratorNameLog.h"
#include "../Message/CLLogHead.h"
#include "../server/include/CLSQL.h"

TEST(CLModifySubordinateAdministratorNameLog, serializeAnddeserialize)
{
    CLLogHead head;
    char *ch = new char[6];
    memcpy(ch, "hello", 5);
    ch[5] = '\0';
    head.init(123, 1, 5, ch, 1, 1);
    CLModifySubordinateAdministratorNameLog Log;
    Log.init(1, 2, 3, 4, 5, "Peter", 1, "A");
    char *buffer = Log.serialize();
    delete[] buffer;
    string query;
    query = head.insertToSQL("CLModifySubordinateAdministratorNameLog");
    query += Log.insertToSQL();
    CLSQL *pSQL = CLSQL::getInstance();
    pSQL->querySQL(query.c_str());
    query = "select * from CLModifySubordinateAdministratorNameLog limit 1 offset 0;";
    pSQL->querySQL(query.c_str());
    pSQL->getResult();
    CLLogHead temphead;
    int n = temphead.getResultFromSQL();
    EXPECT_TRUE(temphead == head);
    CLModifySubordinateAdministratorNameLog templog;
    templog.getResultFromSQL(n);
    EXPECT_TRUE(templog == Log);
}
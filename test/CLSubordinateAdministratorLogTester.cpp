#include <gtest/gtest.h>
#include "../Message/CLSubordinateAdministratorLog.h"
#include "../Message/CLLogHead.h"
#include "../server/include/CLSQL.h"

TEST(CLSubordinateAdministratorLog, serializeAnddeserialize)
{
    CLLogHead head;
    char *ch = new char[6];
    memcpy(ch, "hello", 5);
    ch[5] = '\0';
    head.init(100, 1, 5, ch, 1, 1);
    CLSubordinateAdministratorLog Log;
    Log.init(1, 2, 3, 4);
    char *buffer = Log.serialize();
    delete[] buffer;
    string query;
    query = head.insertToSQL("CLSubordinateAdministratorLog");
    query += Log.insertToSQL();
    CLSQL *pSQL = CLSQL::getInstance();
    pSQL->querySQL(query.c_str());
    query = "select * from CLSubordinateAdministratorLog limit 1 offset 0;";
    pSQL->querySQL(query.c_str());
    pSQL->getResult();
    CLLogHead temphead;
    int n = temphead.getResultFromSQL();
    EXPECT_TRUE(temphead == head);
    CLSubordinateAdministratorLog templog;
    templog.getResultFromSQL(n);
    EXPECT_TRUE(templog == Log);
}
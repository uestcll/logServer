#include <gtest/gtest.h>
#include "../Message/CLAllSubordinateAccountAuthorityManagerLog.h"
#include "../Message/CLLogHead.h"
#include "../server/include/CLSQL.h"

TEST(CLAllSubordinateAccountAuthorityManagerLog, serializeAnddeserialize)
{
	CLLogHead head;
    char *ch = new char[6];
    memcpy(ch, "hello", 5);
    ch[5] = '\0';
    head.init(106, 1, 5, ch, 1, 1);
    CLAllSubordinateAccountAuthorityManagerLog Log;
    Log.init(1, 2, 3);
    char *buffer = Log.serialize();
    delete[] buffer;
    string query;
    query = head.insertToSQL("CLAllSubordinateAccountAuthorityManagerLog");
    query += Log.insertToSQL();
    CLSQL *pSQL = CLSQL::getInstance();
    pSQL->querySQL(query.c_str());
    query = "select * from CLAllSubordinateAccountAuthorityManagerLog limit 1 offset 0;";
    pSQL->querySQL(query.c_str());
    pSQL->getResult();
    CLLogHead temphead;
    int n = temphead.getResultFromSQL();
    EXPECT_TRUE(temphead == head);
    CLAllSubordinateAccountAuthorityManagerLog templog;
    templog.getResultFromSQL(n);
    EXPECT_TRUE(templog == Log);
}
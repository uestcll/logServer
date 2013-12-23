#include <gtest/gtest.h>
#include "../Message/CLServerUpdatePublicKeyLog.h"
#include "../Message/CLLogHead.h"
#include "../server/include/CLSQL.h"

TEST(CLServerUpdatePublicKeyLog, serializeAnddeserialize)
{
    CLLogHead head;
    char *ch = new char[6];
    memcpy(ch, "hello", 5);
    ch[5] = '\0';
    head.init(201, 1, 5, ch, 1, 1);
    CLServerUpdatePublicKeyLog Log;
    Log.init(4, 11, "192.168.1.1", 3, "Tom");
    char *buffer = Log.serialize();
    delete[] buffer;
    string query;
    query = head.insertToSQL("CLServerUpdatePublicKeyLog");
    query += Log.insertToSQL();
    CLSQL *pSQL = CLSQL::getInstance();
    pSQL->querySQL(query.c_str());
    query = "select * from CLServerUpdatePublicKeyLog limit 1 offset 0;";
    pSQL->querySQL(query.c_str());
    pSQL->getResult();
    CLLogHead temphead;
    int n = temphead.getResultFromSQL();
    EXPECT_TRUE(temphead == head);
    CLServerUpdatePublicKeyLog templog;
    templog.getResultFromSQL(n);
    EXPECT_TRUE(templog == Log);
}
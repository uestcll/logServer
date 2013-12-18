/*
 * =====================================================================================
 *
 *       Filename:  CLAdministraotrAuthorityManagerLogTester.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  12/18/2013 10:18:59 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lemon (lemon), lemon_wonder@163.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <gtest/gtest.h>
#include "../Message/CLAdministratorAuthorityManagerLog.h"
#include "../Message/CLLogHead.h"
#include "../server/include/CLSQL.h"

TEST(CLAdministratorAuthorityManagerLog, serializeAnddeserialize)
{
    CLLogHead head;
    char *ch = new char[6];
    memcpy(ch, "hello", 5);
    ch[5] = '\0';
    head.init(102, 1, 5, ch, 1, 1);
    CLAdministratorAuthorityManagerLog Log;
    Log.init(2, 3, 4, 5);
    string query;
    query = head.insertToSQL("CLAdministratorAuthorityManagerLog");
    query += Log.insertToSQL();
    CLSQL *pSQL = CLSQL::getInstance();
    pSQL->querySQL(query.c_str());
    query = "select * from CLAdministratorAuthorityManagerLog limit 1 offset 0;";
    pSQL->querySQL(query.c_str());
    pSQL->getResult();
    CLLogHead temphead;
    int n = temphead.getResultFromSQL();
    EXPECT_TRUE(temphead == head);
    CLAdministratorAuthorityManagerLog templog;
    templog.getResultFromSQL(n);
    EXPECT_TRUE(templog == Log);
}

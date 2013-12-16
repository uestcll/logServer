/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  12/11/13 17:04:08
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:   (), 
 *        Company:  NDSL UESTC
 *
 * =====================================================================================
 */
#include <gtest/gtest.h>
#include "../server/include/CLSQL.h"

int main(int argc, char* argv[])
{
    CLSQL *pSQL = CLSQL::getInstance();
    pSQL->setParameter("localhost", "root", "go", "Log");
    pSQL->connectSQL();
    testing::InitGoogleTest(&argc, argv);

    int r = RUN_ALL_TESTS();
    pSQL->closeSQL();

    return r;
}

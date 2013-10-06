/*
 * =====================================================================================
 *
 *       Filename:  testSQL.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/06/2013 01:48:32 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lemon (zyl), lemon_wonder@163.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>
#include "CLSQL.h"
using namespace std;

int main(int argc, char *argv[])
{
    CLSQL *pSQL = CLSQL::getInstance();
    pSQL->connectSQL("localhost", "root", "go", "test");
    pSQL->querySQL("insert into person values(20, 'bling');");
    return 0;
}

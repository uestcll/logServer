/*
 * =====================================================================================
 *
 *       Filename:  CLSQL.h
 *
 *    Description: 
 *
 *        Version:  1.0
 *        Created:  2013/9/13 12:17:36
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lemon (lemon), lemon_wonder@163.com
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef CLSQL_H
#define CLSQL_H

class CLSQL
{
    public:
        static CLSQL *getInstance();

    private:
        explicit CLSQL();
        ~CLSQL();

    private:
        static CLSQL *m_sql;
};
#endif

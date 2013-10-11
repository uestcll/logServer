#ifndef CLMODIFYPASSWORDLOG_H
#define CLMODIFYPASSWORDLOG_H

#include "LibNetWork.h"
#include "CLMessage.h"
#include "CLPraseManager.h"
#include "CLSQL.h"

class CLModifyPassWordLog : public CLMessage
{
    public:
        void init(int id)
        {
            CLPraseManager *manager = CLPraseManager::getInstance();
            manager->registerHandle(id, this);

        }

        char* serialize()
        {
            char *buffer = new char[8];
            memcpy(buffer, &administratorID, 4);
            memcpy(buffer + 4, &departmentID, 4);
            return buffer;
        }

        void deserialize(char *buffer)
        {
            administratorID = *((int*)buffer);
            departmentID = *((int*)(buffer + 4);
        }

        int getLength()
        {
            return 8;
        }

         virtual void insertToSQL()
        {
            CLSQL *pSQL = CLSQL::getInstance();
            pSQL->connectSQL("localhost", "root", "uestc8020", "log");
            char query[1000];
            memset(query, 0, sizeof(query));
            sprintf(query, "insert into userAccessDiskLog values(%d, %d)", administratorID, departmentID);
            CLSQL *pSQL = CLSQL::getInstance();
            pSQL->querySQL(query);
            pSQL->closeSQL();
    }

    public:
        int administratorID;
        int departmentID;
};

#endif

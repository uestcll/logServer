#ifndef CLUSERACCESSDISKLOG_H
#define CLUSERACCESSDISKLOG_H

#include "LibNetWork.h"

class CLUserAccessDiskLog
{
public:
	explicit CLUserAccessDiskLog()
    {}
	~CLUserAccessDiskLog()
    {}
    /*void init(int id)
    {
        CLPraseManager *manager = CLPraseManager::getInstance();
        manager->registerHandle(id, this);

    }
    */
    char* serialize()
    {
        int len = 28;
        char *buffer = new char[len];
        memcpy(buffer, &userID, 4);
        memcpy(buffer + 4, &departmentIDOfUser, 4);
        memcpy(buffer + 8, &diskID, 4);
        memcpy(buffer + 12, &position, 8);
        memcpy(buffer + 20, &range, 8);
    }
    void deserialize(char *buffer)
    {
        userID = *((int*)buffer);
        departmentIDOfUser = (*(int*)(buffer + 4));
        diskID = *((int*)(buffer + 8));
        position = *((long long*)(buffer + 12));
        range = *((long long*)(buffer + 20));
    }

    int getLength()
    {
        return 12 + 16;
    }
    /*virtual void insertToSQL()
    {
        char query[1000];
        memset(query, 0, sizeof(query));
        sprintf(query, "insert into userAccessDiskLog values(%d, %d, %d, %lld, %lld)", userID, departmentIDOfUser, diskID, position, range);
        CLSQL *pSQL = CLSQL::getInstance();
        pSQL->querySQL(query);
    }*/

public:
    int userID;
    int departmentIDOfUser;
    int diskID;
    long long position;
    long long range; 
};

#endif

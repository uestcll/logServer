#ifndef CLUSERACCESSDISKLOG_H
#define CLUSERACCESSDISKLOG_H

#include "LibNetWork.h"
#include "CLMessage.h"
#include "CLPraseManager.h"
#include "CLSQL.h"

class CLUserAccessDiskLog : public CLMessage
{
public:
	explicit CLUserAccessDiskLog()
    {}
	~CLUserAccessDiskLog()
    {}
    
    void init(int id)
    {
        CLPraseManager *manager = CLPraseManager::getInstance();
        manager->registerHandle(id, this);

    }
    char* serialize()
    {
        int len = 28;
        char *buffer = new char[len];
        memcpy(buffer, &userID, 4);
        memcpy(buffer + 4, &departmentIDOfUser, 4);
        memcpy(buffer + 8, &diskID, 4);
        memcpy(buffer + 12, &position, 8);
        memcpy(buffer + 20, &range, 8);

        return buffer;
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
    virtual void insertToSQL()
    {
        CLSQL *pSQL = CLSQL::getInstance();
    pSQL->connectSQL("localhost", "root", "go", "log");
        char query[1000];
        memset(query, 0, sizeof(query));
        sprintf(query, "insert into test values(%d, %d, %d, %lld, %lld);", userID, departmentIDOfUser, diskID, position, range);
        pSQL->querySQL(query);
        pSQL->closeSQL();
    }

public:
    int userID;
    int departmentIDOfUser;
    int diskID;
    long long position;
    long long range; 
};

#endif

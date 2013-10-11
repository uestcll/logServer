#ifndef CLUSERACCESSDISKLOG_H
#define CLUSERACCESSDISKLOG_H

#include <cstring>
#include <iostream>
using namespace std;

class CLUserAccessDiskLog
{
public:
	explicit CLUserAccessDiskLog()
    {}
	~CLUserAccessDiskLog()
    {}
    
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

public:
    int userID;
    int departmentIDOfUser;
    int diskID;
    long long position;
    long long range; 
};

#endif

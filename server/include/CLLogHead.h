#ifndef CLLOGHEAD_H
#define CLLOGHEAD_H

#include "CLHead.h"
#include "CLSQL.h"
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <iostream>
#include <sstream>
using namespace std;

class CLLogHead : public CLHead
{
public:
	explicit CLLogHead() : logType(-1), lengthOfLoad(0), lengthOfRemark(0), remark(NULL), eventOccurTimeSec(0), eventOccurTimeUsec(0)
	{
	}
	~CLLogHead()
	{
        if(NULL != remark)
            delete[] remark;
	}
	char* serialize()
	{
		int len = 12 + lengthOfRemark + 16;
		char *buffer = new char[len];
		memcpy(buffer, &logType, 4);
		memcpy(buffer + 4, &lengthOfLoad, 4);
		memcpy(buffer + 8, &lengthOfRemark, 4);
		memcpy(buffer + 12, remark, lengthOfRemark);
		memcpy(buffer + 12 + lengthOfRemark, &eventOccurTimeSec, 8);
		memcpy(buffer + 20 + lengthOfRemark, &eventOccurTimeUsec, 8);
		return buffer;
	}

	void deserialize(char *buffer)
	{
		int len = 4;
		logType = *((int*)buffer);
		buffer += len;
		lengthOfLoad = *((int*)buffer);
		buffer += len;
		lengthOfRemark = *((int*)buffer);
		buffer += len;
		len = lengthOfRemark;
		remark = new char[len + 1];
		memcpy(remark, buffer, len);
        remark[len] = '\0';
		buffer += len;
		len = 8;
		memcpy(&eventOccurTimeSec, buffer, len);
		buffer += len;
		memcpy(&eventOccurTimeUsec, buffer, len);
	}

	int getLength()
	{
		return 12 + lengthOfRemark + 16;
	}
	string insertToSQL(string tablename)
	{
		/*
		CLSQL *pSQL = CLSQL::getInstance();
		pSQL->connectSQL("localhost", "root", "go", "log");
		char query[1000];
		memset(query, 0, sizeof(query));
		sprintf(query, "insert into %s values(%d, %d, %s, %lld, %lld);",
				logType, lengthOfLoad, remark, eventOccurTimeSec, eventOccurTimeUsec);
		pSQL->querySQL(query);
		pSQL->closeSQL();
		*/
        stringstream ss;
		string query;
		ss << "insert into " << tablename << " values(" << logType << ", " << lengthOfLoad <<
			    ", " << lengthOfRemark << ", " << "\"" << remark << "\"" << ", " << eventOccurTimeSec << ", " << eventOccurTimeUsec << ", ";
        query = ss.str();
		return query;
	}
	int getResultFromSQL()
	{
		CLSQL *pSQL = CLSQL::getInstance();
		string temp = pSQL->m_store[0];
		logType = atoi(temp.c_str());
		temp = pSQL->m_store[1];
		lengthOfLoad = atoi(temp.c_str());
		temp = pSQL->m_store[2];
		lengthOfRemark = atoi(temp.c_str());
        temp = pSQL->m_store[3];
		remark = new char[lengthOfRemark + 1];
		memcpy(remark, temp.c_str(), lengthOfRemark);
		remark[lengthOfRemark] = '\0';
		temp = pSQL->m_store[4];
		eventOccurTimeSec = atoi(temp.c_str());
		temp = pSQL->m_store[5];
        eventOccurTimeUsec = atoi(temp.c_str());

		return 6;
	}
    void init(int type, int lengthofload, int lengthofremark,
              char *remark, long long sec, long long usec)
    {
        logType = type;
        lengthOfLoad = lengthofload;
        lengthOfRemark = lengthofremark;
        if(NULL != this->remark)
        {
            delete[] this->remark;
        }
        this->remark = new char[lengthofremark + 1];
        memcpy(this->remark, remark, lengthofremark);
        this->remark[lengthofremark] = '\0';
        eventOccurTimeSec = sec;
        eventOccurTimeUsec = usec;
    }
    bool operator==(const CLLogHead &head) const
    {
        if(logType != head.logType)
            return false;
        if(lengthOfLoad != head.lengthOfLoad)
            return false;
        if(lengthOfRemark != head.lengthOfRemark)
            return false;
        if(strcmp(remark, head.remark) != 0)
            return false;
        if(eventOccurTimeSec != head.eventOccurTimeSec)
            return false;
        if(eventOccurTimeUsec != head.eventOccurTimeUsec)
            return false;

        return true;
    }
	
public:
	int logType;
	int lengthOfLoad;
	int lengthOfRemark;
	char *remark;
	long long eventOccurTimeSec;
	long long eventOccurTimeUsec;
};

#endif

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
	string insertToSQL()
	{
		/*
		CLSQL *pSQL = CLSQL::getInstance();
		pSQL->connectSQL("localhost", "root", "go", "log");
		char query[1000];
		memset(query, 0, sizeof(query));
		sprintf(query, "insert into test values(%d, %d, %d, %lld, %lld);", userID, departmentIDOfUser, diskID, position, range);
		pSQL->querySQL(query);
		pSQL->closeSQL();
		*/
		string query;
		query = userID + ", " + departmentIDOfUser + ", " + diskID + ", "
				+ position + ", " + range + ");";
		return query;
	}
	void getResultFromSQL(int offset)
	{
		CLSQL *pSQL = CLSQL::getInstance();
		//pSQL->connectSQL("localhost", "root", "go", "log");
		//pSQL->fetchResult();
		string temp = pSQL->m_store[offset + 0];
		userID = atoi(temp.c_str());
		string temp = pSQL->m_store[offset + 1];
		departmentIDOfUser = atoi(temp.c_str());
		string temp = pSQL->m_store[offset + 2];
		diskID = atoi(temp.c_str());
		string temp = pSQL->m_store[offset + 3];
		position = atoi(temp.c_str());
		string temp = pSQL->m_store[offset + 4];
		range = atoi(temp.c_str());
		//pSQL->closeSQL();
	}

	#ifdef SERVER
	void register(CLPraseManager *pManager)
	{
		pManager->registerHandle(this, 0, "CLUserAccessDiskLog");
		pManager->registerHandle(this, 1, "CLUserAccessDiskLog");
	}
	#endif

public:
	int userID;
	int departmentIDOfUser;
	int diskID;
	long long position;
	long long range; 
};

#endif
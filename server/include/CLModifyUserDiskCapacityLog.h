#ifndef CLMODIFYUSERDISKCAPACITYLOG_H
#define CLMODIFYUSERDISKCAPACITYLOG_H

#include <cstdio>
#include <cstdlib>
#include <cstring>

class CLModifyUserDiskCapacityLog : public CLMessage
{
public:
	char *serialize()
	{
		int len = 36;
		char *buffer = new char[len];
		memcpy(buffer, &administrarorID, 4);
		memcpy(buffer + 4, &departmentID, 4);
		memcpy(buffer + 8, &userID, 4);
		memcpy(buffer + 12, &departmentIDOfUser, 4);
		memcpy(buffer + 16, &diskID, 4);
		memcpy(buffer + 20, &capacityBeforeModify, 8);
		memcpy(buffer + 28, &capacityAfterModify, 8);
		return buffer;
	}
	void deserialize(char *buffer)
	{
		memcpy(&administrarorID, buffer, 4);
		memcpy(&departmentID, buffer + 4, 4);
		memcpy(&userID, buffer + 8, 4);
		memcpy(&departmentIDOfUser, buffer + 12, 4);
		memcpy(&diskID, buffer + 16, 4);
		memcpy(&capacityBeforeModify, buffer + 20, 8);
		memcpy(&capacityAfterModify, buffer + 28, 8);
	}
	string insertToSQL()
	{
		/*
		CLSQL *pSQL = CLSQL::getInstance();
		pSQL->connectSQL("localhost", "root", "go", "log");
		char query[1000];
		memset(query, 0, sizeof(query));
		sprintf(query, "insert into test values(%d, %d, %d, %d, %d, %lld, %lld);", 
			administratorID, departmentID, userID, departmentIDOfUser, diskID,
			capacityBeforeModify, capacityAfterModify);
		pSQL->querySQL(query);
		pSQL->closeSQL();
		*/
		string query;
		query = administrarorID + ", " + departmentID + ", " + userID + ", "
				+ departmentIDOfUser + ", " + diskID + ", " + capacityBeforeModify
				+ ", " + capacityAfterModify + ");";
		return query;
	}
	void getResultFromSQL(int offset)
	{
		CLSQL *pSQL = CLSQL::getInstance();
		//pSQL->connectSQL("localhost", "root", "go", "log");
		//pSQL->fetchResult();
		string temp = pSQL->m_store[offset + 0];
		administrarorID = atoi(temp.c_str());
		temp = pSQL->m_store[offset + 1];
		departmentID = atoi(temp.c_str());
		temp = pSQL->m_store[offset + 2];
		userID = atoi(temp.c_str());
		temp = pSQL->m_store[offset + 3];
		departmentIDOfUser = atoi(temp.c_str());
		temp = pSQL->m_store[offset + 4];
		diskID = atoi(temp.c_str());
		temp = pSQL->m_store[offset + 5];
		capacityBeforeModify = atoi(temp.c_str());
		temp = pSQL->m_store[offset + 6];
		capacityAfterModify = atoi(temp.c_str());
		//pSQL->closeSQL();
	}
	int getLength()
	{
		return 36;
	}
private:
	int administrarorID;
	int departmentID;
	int userID;
	int departmentIDOfUser;
	int diskID;
	long long capacityBeforeModify;
	long long capacityAfterModify;
};
#endif
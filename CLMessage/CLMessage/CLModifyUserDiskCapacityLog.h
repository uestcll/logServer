#ifndef CLMODIFYUSERDISKCAPACITYLOG_H
#define CLMODIFYUSERDISKCAPACITYLOG_H

#include <cstdio>
#include <cstdlib>
#include <cstring>

class CLModifyUserDiskCapacityLog
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
	void insertToSQL()
	{
		CLSQL *pSQL = CLSQL::getInstance();
		pSQL->connectSQL("localhost", "root", "go", "log");
		char query[1000];
		memset(query, 0, sizeof(query));
		sprintf(query, "insert into test values(%d, %d, %d, %d, %d, %lld, %lld);", 
			administratorID, departmentID, userID, departmentIDOfUser, diskID,
			capacityBeforeModify, capacityAfterModify);
		pSQL->querySQL(query);
		pSQL->closeSQL();
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
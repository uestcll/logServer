#ifndef CLMODIFYSHAREDISKCAPACITYLOG_H
#define CLMODIFYSHAREDISKCAPACITYLOG_H

#include <cstdio>
#include <cstdlib>
#include <cstring>

class CLModifyShareDiskCapacityLog
{
public:
	char *serialize()
	{
		int len = 32;
		char *buffer = new char[len];
		memcpy(buffer, &administrarorID, 4);
		memcpy(buffer + 4, &departmentID, 4);
		memcpy(buffer + 8, &sharedDiskID, 4);
		memcpy(buffer + 12, &departmentIDOfDisk, 4);
		memcpy(buffer + 16, &capacityBeforeModify, 8);
		memcpy(buffer + 24, &capacityAfterModify, 8);
		return buffer;
	}
	void deserialize(char *buffer)
	{
		memcpy(&administrarorID, buffer, 4);
		memcpy(&departmentID, buffer + 4, 4);
		memcpy(&sharedDiskID, buffer + 8, 4);
		memcpy(&departmentIDOfDisk, buffer + 12, 4);
		memcpy(&capacityBeforeModify, buffer + 16, 8);
		memcpy(&capacityAfterModify, buffer + 24, 8);
	}
	void insertToSQL()
	{
		CLSQL *pSQL = CLSQL::getInstance();
		pSQL->connectSQL("localhost", "root", "go", "log");
		char query[1000];
		memset(query, 0, sizeof(query));
		sprintf(query, "insert into test values(%d, %d, %d, %d, %lld, %lld);", 
			administratorID, departmentID, sharedDiskID, departmentIDOfDisk,
			capacityBeforeModify, capacityAfterModify);
		pSQL->querySQL(query);
		pSQL->closeSQL();
	}
	int getLength()
	{
		return 32;
	}
private:
	int administrarorID;
	int departmentID;
	int sharedDiskID;
	int departmentIDOfDisk;
	long long capacityBeforeModify;
	long long capacityAfterModify;
};

#endif
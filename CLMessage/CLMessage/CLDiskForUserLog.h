#ifndef CLDISKFORUSERLOG_H
#define CLDISKFORUSERLOG_H

#include <cstdio>
#include <cstdlib>
#include <cstirng>

class CLDiskForUserLog
{
public:
	char *serialize()
	{
		int len = 20;
		char *buffer = new char[len];
		memcpy(buffer, &administratorID, 4);
		memcpy(buffer + 4, &departmentID, 4);
		memcpy(buffer + 8, &userID, 4);
		memcpy(buffer + 12, &departmentIDOfUser, 4);
		memcpy(buffer + 16, &diskID, 4);

		return buffer;
	}
	void deserialize(char *buffer)
	{
		memcpy(&administratorID, buffer, 4);
		memcpy(&departmentID, buffer + 4, 4);
		memcpy(&userID, buffer + 8, 4);
		memcpy(&departmentIDOfUser, buffer + 12, 4);
		memcpy(&diskID, buffer + 16, 4);
	}
	void insertToSQL()
	{
		CLSQL *pSQL = CLSQL::getInstance();
		pSQL->connectSQL("localhost", "root", "go", "log");
		char query[1000];
		memset(query, 0, sizeof(query));
		sprintf(query, "insert into test values(%d, %d, %d, %d, %d);", 
			administratorID, departmentID, userID,
			departmentIDOfUser, diskID);
		pSQL->querySQL(query);
		pSQL->closeSQL();
	}
private:
	int administratorID;
	int departmentID:
	int userID;
	int departmentIDOfUser;
	int diskID;
};
#endif
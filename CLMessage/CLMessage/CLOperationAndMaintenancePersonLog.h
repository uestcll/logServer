#ifndef CLOPERATIONANDMAINTENANCEPERSONLOG_H
#define CLOPERATIONANDMAINTENANCEPERSONLOG_H

#include <cstdio>
#include <cstdlib>
#include <cstring>

class CLOperationAndMaintenancePersonLog
{
public:
	char *serialize()
	{
		int len = 12;
		char *buffer = new char[len];
		memcpy(buffer, &administratorID, 4);
		memcpy(buffer + 4, &departmentID, 4);
		memcpy(buffer + 8, &operationStaffID, 4);
	}
	void deserialize(char *buffer)
	{
		memcpy(&administratorID, buffer, 4);
		memcpy(&departmentID, buffer + 4, 4);
		memcpy(&operationStaffID, buffer + 8, 4);
	}
	void insertToSQL()
	{
		CLSQL *pSQL = CLSQL::getInstance();
		pSQL->connectSQL("localhost", "root", "go", "log");
		char query[1000];
		memset(query, 0, sizeof(query));
		sprintf(query, "insert into test values(%d, %d, %d);", 
			administratorID, departmentID, operationStaffID);
		pSQL->querySQL(query);
		pSQL->closeSQL();
	}
private:
	int administratorID;
	int departmentID;
	int operationStaffID;
};
#endif
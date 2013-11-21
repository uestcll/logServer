#ifndef CLADMINISTRATORAUTHORITYMANAGERLOG_H
#define CLADMINISTRATORAUTHORITYMANAGERLOG_H

#include <cstdio>
#include <cstdlib>
#include <cstring>

class CLAdministraotrAuthorityManagerLog
{
public:
	char *serialize()
	{
		int len = 16;
		char *buffer = new char[16];
		memcpy(buffer, &administratorID, 4);
		memcpy(buffer + 4, &departmentID, 4);
		memcpy(buffer + 8, &subordinateDepartmentID, 4);
		memcpy(buffer + 12, &subordinateAdministratorID, 4);

		return buffer;
	}

	void deserialize(char *buffer)
	{
		memcpy(&administratorID, buffer, 4);
		memcpy(&departmentID, buffer + 4, 4);
		memcpy(&subordinateDepartmentID, buffer + 8, 4);
		memcpy(&subordinateAdministratorID, buffer + 12, 4);
	}

	void insertToSQL()
	{
		CLSQL *pSQL = CLSQL::getInstance();
		pSQL->connectSQL("localhost", "root", "go", "log");
		char query[1000];
		memset(query, 0, sizeof(query));
		sprintf(query, "insert into test values(%d, %d, %d, %d);", 
			administratorID, departmentID, subordinateAdministrator, 
			subordinateDepartmentID);
		pSQL->querySQL(query);
		pSQL->closeSQL();
	}
	int getLength()
	{
		return 16;
	}

private:
	int administratorID;
	int departmentID;
	int subordinateDepartmentID;
	int subordinateAdministratorID;
};
#endif
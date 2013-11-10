#ifndef CLMODIFYSUBORDINATEADMINISTRATORNAMELOG_H
#define CLMODIFYSUBORDINATEADMINISTRATORNAMELOG_H

#include <cstdio>
#include <cstdlib>
#include <cstring>

class CLModifySubordinateAdministratorNameLog
{
public:
	char *serialize()
	{
		int len = 24 + lengthOfNameBeforeModify + lengthOfNameAfterModify;
		char *buffer = new char[len];
		memcpy(buffer, &administratorID, 4);
		memcpy(buffer + 4, &departmentID, 4);
		memcpy(buffer + 8, &subordinateAdministorID, 4);
		memcpy(buffer + 12, &subordinateDepartmentID, 4);
		memcpy(buffer + 16, &lengthOfNameBeforeModify, 4);
		memcpy(buffer + 20, nameBeforeModify, lengthOfNameBeforeModify);
		memcpy(buffer + 20 + lengthOfNameBeforeModify, &lengthOfNameAfterModify, 4);
		memcpy(buffer + 24 + lengthOfNameBeforeModify, nameAfterModify, lengthOfNameAfterModify);

		return buffer;
	}
	void deserialize(char *buffer)
	{
		memcpy(&administratorID, buffer, 4);
		memcpy(&departmentID, buffer + 4, 4);
		memcpy(&subordinateAdministorID, buffer + 8, 4);
		memcpy(&subordinateDepartmentID, buffer + 12, 4);
		memcpy(&lengthOfNameBeforeModify, buffer + 16, 4);
		nameBeforeModify = new char[lengthOfNameBeforeModify + 1];
		memcpy(nameBeforeModify, buffer + 20, lengthOfNameBeforeModify);
		nameBeforeModify[lengthOfNameBeforeModify] = '\0';
		memcpy(&lengthOfNameAfterModify, buffer + 20 + lengthOfNameBeforeModify, 4);
		nameAfterModify = new char[lengthOfNameAfterModify + 1];
		memcpy(nameAfterModify, buffer + 24 + lengthOfNameBeforeModify, lengthOfNameAfterModify);
	}
	void insertToSQL()
	{
		CLSQL *pSQL = CLSQL::getInstance();
		pSQL->connectSQL("localhost", "root", "go", "log");
		char query[1000];
		memset(query, 0, sizeof(query));
		sprintf(query, "insert into test values(%d, %d, %d, %d, %s, %s);", 
			administratorID, departmentID, subordinateAdministorID, 
			subordinateDepartmentID, nameBeforeModify, nameAfterModify);
		pSQL->querySQL(query);
		pSQL->closeSQL();
	}
	int getLength()
	{
		return 24 + lengthOfNameBeforeModify + lengthOfNameAfterModify;
	}
private:
	int administratorID;
	int departmentID;
	int subordinateAdministorID;
	int subordinateDepartmentID;
	int lengthOfNameBeforeModify;
	char *nameBeforeModify;
	int lengthOfNameAfterModify;
	char *nameAfterModify;
};

#endif
#ifndef CLMODIFYDEPARTMENTNAMELOG_H
#define CLMODIFYDEPARTMENTNAMELOG_H

#include <cstdio>
#include <cstdlib>
#include <cstring>

class CLModifyDepartmentNameLog
{
public:
	char *serialize()
	{
		int len = 20 + lengthOfNameBeforeModify + lengthOfNameAfterModify;
		char *buffer = new char[len];
		memcpy(buffer, &administrarorID, 4);
		memcpy(buffer + 4, &departmentID, 4);
		memcpy(buffer + 8, &departmentIDOfNameModify, 4);
		memcpy(buffer + 12, &lengthOfNameBeforeModify, 4);
		memcpy(buffer + 16, nameBeforeModify, lengthOfNameBeforeModify);
		memcpy(buffer + 16 + lengthOfNameBeforeModify, &lengthOfNameAfterModify, 4);
		memcpy(buffer + 20, nameAfterModify, lengthOfNameAfterModify);

		return buffer;
	}
	void deserialize(char *buffer)
	{
		memcpy(&administrarorID, buffer, 4);
		memcpy(&departmentID, buffer + 4, 4);
		memcpy(&departmentIDOfNameModify, buffer + 8, 4);
		memcpy(&lengthOfNameBeforeModify, buffer + 12, 4);
		nameBeforeModify = new char[lengthOfNameBeforeModify + 1];
		memcpy(nameBeforeModify, buffer + 16, lengthOfNameBeforeModify);
		nameBeforeModify[lengthOfNameBeforeModify] = '\0';
		memcpy(&lengthOfNameAfterModify, buffer + 16 + lengthOfNameBeforeModify, 4);
		nameAfterModify = new char[lengthOfNameAfterModify + 1];
		memcpy(nameAfterModify, buffer + 20 + lengthOfNameBeforeModify, lengthOfNameAfterModify);
	}
	void insertToSQL()
	{
		CLSQL *pSQL = CLSQL::getInstance();
		pSQL->connectSQL("localhost", "root", "go", "log");
		char query[1000];
		memset(query, 0, sizeof(query));
		sprintf(query, "insert into test values(%d, %d, %d, %s, %s);", 
			administratorID, departmentID, departmentIDOfNameModify,
			nameBeforeModify, nameAfterModify);
		pSQL->querySQL(query);
		pSQL->closeSQL();
	}
	int getLength()
	{
		return 20 + lengthOfNameAfterModify + lengthOfNameBeforeModify;
	}
private:
	int administrarorID;
	int departmentID;
	int departmentIDOfNameModify;
	int lengthOfNameBeforeModify;
	char *nameBeforeModify;
	int lengthOfNameAfterModify;
	char *nameAfterModify;
};

#endif
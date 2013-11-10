#ifndef CLADMINISTRATORLOGINLOG_H
#define CLADMINISTRATORLOGINLOG_H

#include <cstdio>
#include <cstdlib>
#include <cstring>

class CLAdministratorLoginLog
{
public:
	char *serialize()
	{
		int len = 16 + IPLength;
		char *buffer = new char[len];
		memcpy(buffer, &administratorID, 4);
		memcpy(buffer + 4, &departmentID, 4);
		memcpy(buffer + 8, &IPType, 4);
		memcpy(buffer + 12, &IPLength, 4);
		memcpy(buffer + 16, &loginIPAdress, IPLength);

		return buffer;
	}
	void deserialize(char *buffer)
	{
		memcpy(&administratorID, buffer, 4);
		memcpy(&departmentID, buffer + 4, 4);
		memcpy(&IPType, buffer + 8, 4);
		memcpy(&IPLength, buffer + 12, 4);
		loginIPAdress = new char[IPLength + 1];
		memcpy(loginIPAdress, buffer + 16, IPLength);
		loginIPAdress[IPLength] = '\0';
	}
	void insertToSQL()
	{
		CLSQL *pSQL = CLSQL::getInstance();
		pSQL->connectSQL("localhost", "root", "go", "log");
		char query[1000];
		memset(query, 0, sizeof(query));
		sprintf(query, "insert into test values(%d, %d, %d, %s);", 
			administratorID, departmentID, IPType, loginIPAdress);
		pSQL->querySQL(query);
		pSQL->closeSQL();
	}
private:
	int administratorID;
	int departmentID;
	int IPType;
	int IPLength;
    char *loginIPAdress;
};
#endif
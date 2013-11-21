#ifndef CLUSERLOGINLOG_H
#define CLUSERLOGINLOG_H

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>

class CLUserLoginLog
{
public:
	char *serialize()
	{
		int len = 16 + IPlength;
		char *buffer = new char[len];
		memcpy(buffer, &userID, 4);
		memcpy(buffer + 4, &departmentIDOfUser, 4);
		memcpy(buffer + 8, &IPType, 4);
		memcpy(buffer + 12, &IPlength, 4);
		memcpy(buffer + 16, &loginIPAdress, IPlength);

		return buffer;
	}

	void deserialize(char *buffer)
	{
		memcpy(&userID, buffer, 4);
		memcpy(&departmentIDOfUser, buffer + 4, 4);
		memcpy(&IPType, buffer + 8, 4);
		memcpy(&IPlength, buffer + 12, 4);
		loginIPAdress = new char[IPlength + 1];
		memcpy(&loginIPAdress, buffer + 16, IPlength);
		loginIPAdress[IPlength] = '\0';
	}

	int getLength()
	{
		return 16 + IPlength;
	}

	void insertToSQL()
	{
		CLSQL *pSQL = CLSQL::getInstance();
		pSQL->connectSQL("localhost", "root", "go", "log");
		char query[1000];
		memset(query, 0, sizeof(query));
		sprintf(query, "insert into test values(%d, %d, %d, %s);", 
			    userID, departmentIDOfUser, IPType, loginIPAdress);
		pSQL->querySQL(query);
		pSQL->closeSQL();
	}

private:
	int userID;
	int departmentIDOfUser;
    int IPType;
	int IPlength;
	char* loginIPAdress;
};
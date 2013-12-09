#ifndef CLDISKFORUSERLOG_H
#define CLDISKFORUSERLOG_H

#include <cstdio>
#include <cstdlib>
#include <cstirng>

class CLDiskForUserLog : public CLMessage
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

	int getLength()
	{
		return 20;
	}
	string insertToSQL()
	{
		/*
		CLSQL *pSQL = CLSQL::getInstance();
		pSQL->connectSQL("localhost", "root", "go", "log");
		char query[1000];
		memset(query, 0, sizeof(query));
		sprintf(query, "insert into test values(%d, %d, %d, %d, %d);", 
			administratorID, departmentID, userID,
			departmentIDOfUser, diskID);
		pSQL->querySQL(query);
		pSQL->closeSQL();
		*/
		string query;
		query = administratorID + ", " + departmentID + ", " + userID + ", "
				departmentIDOfUser + ", " + diskID + ");";
		return query;
	}
	void getResultFromSQL(int offset)
	{
		CLSQL *pSQL = CLSQL::getInstance();
		//pSQL->connectSQL("localhost", "root", "go", "log");
		//pSQL->fetchResult();
		string temp = pSQL->m_store[offset + 0];
		administratorID = atoi(temp.c_str());
		temp = pSQL->m_store[offset + 1];
		departmentID = atoi(temp.c_str());
		temp = pSQL->m_store[offset + 2];
		userID = atoi(temp.c_str());
		temp = pSQL->m_store[offset + 3];
		departmentIDOfUser = atoi(temp.c_str());
		temp = pSQL->m_store[offset + 4];
		diskID = atoi(temp.c_str());
		//pSQL->closeSQL();
	}
private:
	int administratorID;
	int departmentID:
	int userID;
	int departmentIDOfUser;
	int diskID;
};
#endif
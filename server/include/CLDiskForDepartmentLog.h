#ifndef CLDISKFORDEPARTMENTLOG_H
#define CLDISKFORDEPARTMENTLOG_H

#include <cstdio>
#include <cstdlib>
#include <cstring>

class CLDiskForDepartmentLog
{
public:
	char *serialize()
	{
		int len = 16;
		char *buffer = new char[len];
		memcpy(buffer, &administratorID, 4);
		memcpy(buffer + 4, &departmentID, 4);
		memcpy(buffer + 8, departmentIDOfDisk, 4);
		memcpy(buffer + 12, sharedDiskID, 4);

		return buffer;
	}
	void deserialize(char *buffer)
	{
		memcpy(&administratorID, buffer, 4);
		memcpy(&departmentID, buffer + 4, 4);
		memcpy(departmentIDOfDisk, buffer + 8, 4);
		memcpy(sharedDiskID, buffer + 12, 4);
	}

	void insertToSQL()
	{
		CLSQL *pSQL = CLSQL::getInstance();
		pSQL->connectSQL("localhost", "root", "go", "log");
		char query[1000];
		memset(query, 0, sizeof(query));
		sprintf(query, "insert into test values(%d, %d, %d, %d);", 
			administratorID, departmentID, departmentIDOfDisk,
			sharedDiskID);
		pSQL->querySQL(query);
		pSQL->closeSQL();
	}
	void getResultFromSQL()
	{
		CLSQL *pSQL = CLSQL::getInstance();
		pSQL->connectSQL("localhost", "root", "go", "log");
		pSQL->fetchResult();
		string temp = pSQL->m_store[0];
		administratorID = atoi(temp.c_str());
		temp = pSQL->m_store[1];
		departmentID = atoi(temp.c_str());
		temp = pSQL->m_store[2];
		departmentIDOfDisk = atoi(temp.c_str());
		temp = pSQL->m_store[3];
		sharedDiskID = atoi(temp.c_str());
		pSQL->closeSQL();
	}
	int getLength()
	{
		return 16;
	}
private:
	int administratorID;
	int departmentID;
	int departmentIDOfDisk;
	int sharedDiskID;
};

#endif
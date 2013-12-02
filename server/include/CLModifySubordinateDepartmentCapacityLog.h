#ifndef CLMODIFYSUBORDINATEDEPARTMENTCAPACITYLOG_H
#define CLMODIFYSUBORDINATEDEPARTMENTCAPACITYLOG_H

#include <cstdio>
#include <cstdlib>
#include <cstring>

class CLModifySubordinateDepartmentCapacityLog
{
public:
	char *serialize()
	{
		int len = 28;
		char *buffer = new char[len];
		memcpy(buffer, &administrarorID, 4);
		memcpy(buffer + 4, &departmentID, 4);
		memcpy(buffer + 8, &subordinateDepartmentID, 4);
		memcpy(buffer + 12, &capacityBeforeModify, 8);
		memcpy(buffer + 20, &capacityAfterModify, 8);

		return buffer;
	}
	void deserialize(char *buffer)
	{
		memcpy(&administrarorID, buffer, 4);
		memcpy(&departmentID, buffer + 4, 4);
		memcpy(&subordinateDepartmentID, buffer + 8, 4);
		memcpy(&capacityBeforeModify, buffer + 12, 8);
		memcpy(&capacityAfterModify, buffer + 20, 8);
	}
	void insertToSQL()
	{
		CLSQL *pSQL = CLSQL::getInstance();
		pSQL->connectSQL("localhost", "root", "go", "log");
		char query[1000];
		memset(query, 0, sizeof(query));
		sprintf(query, "insert into test values(%d, %d, %d, %lld, %lld);", 
			administratorID, departmentID, subordinateDepartmentID,
			capacityBeforeModify, capacityAfterModify);
		pSQL->querySQL(query);
		pSQL->closeSQL();
	}
	void getResultFromSQL()
	{
		CLSQL *pSQL = CLSQL::getInstance();
		pSQL->connectSQL("localhost", "root", "go", "log");
		pSQL->fetchResult();
		string temp = pSQL->m_store[0];
		administrarorID = atoi(temp.c_str());
		temp = pSQL->m_store[1];
		departmentID = atoi(temp.c_str());
		temp = pSQL->m_store[2];
		subordinateDepartmentID = atoi(temp.c_str());
		temp = pSQL->m_store[3];
		capacityBeforeModify = atoi(temp.c_str());
		temp = pSQL->m_store[4];
		capacityAfterModify = atoi(temp.c_str());
		pSQL->closeSQL();
	}
	int getLength()
	{
		return 28;
	}
private:
	int administrarorID;
	int departmentID:
	int subordinateDepartmentID;
	long long capacityBeforeModify;
	long long capacityAfterModify;
};

#endif
#ifndef CLDISKFORDEPARTMENTLOG_H
#define CLDISKFORDEPARTMENTLOG_H

#include <cstdio>
#include <cstdlib>
#include <cstring>

class CLDiskForDepartmentLog : public CLMessage
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

	string insertToSQL()
	{
		/*
		CLSQL *pSQL = CLSQL::getInstance();
		pSQL->connectSQL("localhost", "root", "go", "log");
		char query[1000];
		memset(query, 0, sizeof(query));
		sprintf(query, "insert into test values(%d, %d, %d, %d);", 
			administratorID, departmentID, departmentIDOfDisk,
			sharedDiskID);
		pSQL->querySQL(query);
		pSQL->closeSQL();
		*/
		string query;
		query = administratorID + ", " + departmentID + ", " + departmentIDOfDisk + ", "
				sharedDiskID + ");";
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
		departmentIDOfDisk = atoi(temp.c_str());
		temp = pSQL->m_store[offset + 3];
		sharedDiskID = atoi(temp.c_str());
		//pSQL->closeSQL();
	}
	int getLength()
	{
		return 16;
	}

	#ifdef SERVER
	void register(CLPraseManager *pManager)
	{
		pManager->registerHandle(this, 116, "CLDiskForDepartmentLog");
		pManager->registerHandle(this, 117, "CLDiskForDepartmentLog");
	}
	#endif

private:
	int administratorID;
	int departmentID;
	int departmentIDOfDisk;
	int sharedDiskID;
};

#endif
#ifndef CLDISKFORDEPARTMENTLOG_H
#define CLDISKFORDEPARTMENTLOG_H

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <iostream>
#include <sstream>
#include "CLMessage.h"
#ifdef SERVER
#include "../server/include/CLSQL.h"
#include "../server/include/CLPraseManager.h"
#endif

class CLDiskForDepartmentLog : public CLMessage
{
public:
	CLDiskForDepartmentLog() : administratorID(0), departmentID(0), departmentIDOfDisk(0),
	sharedDiskID(0)
	{}
	~CLDiskForDepartmentLog()
	{}
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
	int getLength()
	{
		return 16;
	}
	#ifdef SERVER
	string insertToSQL()
	{
		stringstream ss;
		string query;
		ss << administratorID << ", " << departmentID << ", " << departmentIDOfDisk << ", "
				sharedDiskID << ");";
		query = ss.str();
		return query;
	}
	void getResultFromSQL(int offset)
	{
		CLSQL *pSQL = CLSQL::getInstance();
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
	void registerIt(CLPraseManager *pManager)
	{
		pManager->registerHandle(this, 116, "CLDiskForDepartmentLog");
		pManager->registerHandle(this, 117, "CLDiskForDepartmentLog");
	}
	#endif

	void init(int id1, int id2, int id3, int id4)
	{
		administratorID = id1;
		departmentID = id2;
		departmentIDOfDisk = id3;
		sharedDiskID = id4;
	}
	bool operator==(const CLDiskForDepartmentLog &Log) const
	{
		if(administratorID != Log.administratorID)
			return false;
		if(departmentID != Log.departmentID)
			return false;
		if(departmentIDOfDisk != Log.departmentIDOfDisk)
			return false;
		if(sharedDiskID != Log.sharedDiskID)
			return false;

		return true;
	}

private:
	int administratorID;
	int departmentID;
	int departmentIDOfDisk;
	int sharedDiskID;
};

#endif
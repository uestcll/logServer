#ifndef CLMODIFYSHAREDISKCAPACITYLOG_H
#define CLMODIFYSHAREDISKCAPACITYLOG_H

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

class CLModifyShareDiskCapacityLog : public CLMessage
{
public:
	CLModifyShareDiskCapacityLog() : administratorID(0), departmentID(0), sharedDiskID(0), departmentIDOfDisk(0), capacityBeforeModify(0), capacityAfterModify(0)
	{}
	~CLModifyShareDiskCapacityLog()
	{}
	char *serialize()
	{
		int len = 32;
		char *buffer = new char[len];
		memcpy(buffer, &administratorID, 4);
		memcpy(buffer + 4, &departmentID, 4);
		memcpy(buffer + 8, &sharedDiskID, 4);
		memcpy(buffer + 12, &departmentIDOfDisk, 4);
		memcpy(buffer + 16, &capacityBeforeModify, 8);
		memcpy(buffer + 24, &capacityAfterModify, 8);
		return buffer;
	}
	void deserialize(char *buffer)
	{
		memcpy(&administratorID, buffer, 4);
		memcpy(&departmentID, buffer + 4, 4);
		memcpy(&sharedDiskID, buffer + 8, 4);
		memcpy(&departmentIDOfDisk, buffer + 12, 4);
		memcpy(&capacityBeforeModify, buffer + 16, 8);
		memcpy(&capacityAfterModify, buffer + 24, 8);
	}
	int getLength()
	{
		return 32;
	}

	#ifdef SERVER
	string insertToSQL()
	{
		stringstream ss;
		string query;
		ss << administratorID << ", " << departmentID << ", " << sharedDiskID << ", "
		   << departmentIDOfDisk << ", " << capacityBeforeModify << ", "
		   << capacityAfterModify << ");";
		query = ss.str();
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
		sharedDiskID = atoi(temp.c_str());
		temp = pSQL->m_store[offset + 3];
		departmentIDOfDisk = atoi(temp.c_str());
		temp = pSQL->m_store[offset + 4];
		capacityBeforeModify = atoi(temp.c_str());
		temp = pSQL->m_store[offset + 5];
		capacityAfterModify = atoi(temp.c_str());
		//pSQL->closeSQL();
	}

	void registerIt(CLPraseManager *pManager)
	{
		pManager->registerHandle(this, 125, "CLModifyShareDiskCapacityLog");
	}
	#endif

	void init(int id1, int id2, int id3, int id4, long long c1, long long c2)
	{
		administratorID = id1;
		departmentID = id2;
		sharedDiskID = id3;
		departmentIDOfDisk = id4;
		capacityBeforeModify = c1;
		capacityAfterModify = c2;
	}
	bool operator==(const CLModifyShareDiskCapacityLog &Log) const
	{
		if(administratorID != Log.administrarorID)
			return false;
		if(departmentID != Log.departmentID)
			return false;
		if(sharedDiskID != Log.sharedDiskID)
			return false;
		if(departmentIDOfDisk != Log.departmentIDOfDisk)
			return false;
		if(capacityBeforeModify != Log.capacityBeforeModify)
			return false;
		if(capacityAfterModify != Log.capacityAfterModify)
			return false;

		return true;
	}
private:
	int administratorID;
	int departmentID;
	int sharedDiskID;
	int departmentIDOfDisk;
	long long capacityBeforeModify;
	long long capacityAfterModify;
};

#endif

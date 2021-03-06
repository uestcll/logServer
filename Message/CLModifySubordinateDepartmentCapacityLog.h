#ifndef CLMODIFYSUBORDINATEDEPARTMENTCAPACITYLOG_H
#define CLMODIFYSUBORDINATEDEPARTMENTCAPACITYLOG_H

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

class CLModifySubordinateDepartmentCapacityLog : public CLMessage
{
public:
	CLModifySubordinateDepartmentCapacityLog() : administratorID(0), departmentID(0), subordinateDepartmentID(0), capacityBeforeModify(0), capacityAfterModify(0)
	{}
	~CLModifySubordinateDepartmentCapacityLog()
	{}

	char *serialize()
	{
		int len = 28;
		char *buffer = new char[len];
		memcpy(buffer, &administratorID, 4);
		memcpy(buffer + 4, &departmentID, 4);
		memcpy(buffer + 8, &subordinateDepartmentID, 4);
		memcpy(buffer + 12, &capacityBeforeModify, 8);
		memcpy(buffer + 20, &capacityAfterModify, 8);

		return buffer;
	}
	void deserialize(char *buffer)
	{
		memcpy(&administratorID, buffer, 4);
		memcpy(&departmentID, buffer + 4, 4);
		memcpy(&subordinateDepartmentID, buffer + 8, 4);
		memcpy(&capacityBeforeModify, buffer + 12, 8);
		memcpy(&capacityAfterModify, buffer + 20, 8);
	}
	int getLength()
	{
		return 28;
	}
	#ifdef SERVER
	string insertToSQL()
	{
		stringstream ss;
		string query;
		ss << administratorID << ", " << departmentID << ", " << subordinateDepartmentID
		   << ", " << capacityBeforeModify << ", " << capacityAfterModify << ");";
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
		subordinateDepartmentID = atoi(temp.c_str());
		temp = pSQL->m_store[offset + 3];
		capacityBeforeModify = atoi(temp.c_str());
		temp = pSQL->m_store[offset + 4];
		capacityAfterModify = atoi(temp.c_str());
		//pSQL->closeSQL();
	}
	void registerIt(CLPraseManager *pManager)
	{
		pManager->registerHandle(this, 124, "CLModifySubordinateDepartmentCapacityLog");
	}
	#endif

	void init(int id1, int id2, int id3, int c1, int c2)
	{
		administratorID = id1;
		departmentID = id2;
		subordinateDepartmentID = id3;
		capacityBeforeModify = c1;
		capacityAfterModify = c2;
	}
	bool operator==(const CLModifySubordinateDepartmentCapacityLog &Log) const
	{
		if(administratorID != Log.administratorID)
			return false;
		if(departmentID != Log.departmentID)
			return false;
		if(subordinateDepartmentID != Log.subordinateDepartmentID)
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
	int subordinateDepartmentID;
	long long capacityBeforeModify;
	long long capacityAfterModify;
};

#endif
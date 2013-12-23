#ifndef CLMODIFYUSERDISKCAPACITYLOG_H
#define CLMODIFYUSERDISKCAPACITYLOG_H

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

class CLModifyUserDiskCapacityLog : public CLMessage
{
public:
	CLModifyUserDiskCapacityLog() : administratorID(0), departmentID(0), userID(0), departmentIDOfUser(0), diskID(0), capacityBeforeModify(0), capacityAfterModify(0)
	{}
	~CLModifyUserDiskCapacityLog()
	{}
	char *serialize()
	{
		int len = 36;
		char *buffer = new char[len];
		memcpy(buffer, &administratorID, 4);
		memcpy(buffer + 4, &departmentID, 4);
		memcpy(buffer + 8, &userID, 4);
		memcpy(buffer + 12, &departmentIDOfUser, 4);
		memcpy(buffer + 16, &diskID, 4);
		memcpy(buffer + 20, &capacityBeforeModify, 8);
		memcpy(buffer + 28, &capacityAfterModify, 8);
		return buffer;
	}
	void deserialize(char *buffer)
	{
		memcpy(&administratorID, buffer, 4);
		memcpy(&departmentID, buffer + 4, 4);
		memcpy(&userID, buffer + 8, 4);
		memcpy(&departmentIDOfUser, buffer + 12, 4);
		memcpy(&diskID, buffer + 16, 4);
		memcpy(&capacityBeforeModify, buffer + 20, 8);
		memcpy(&capacityAfterModify, buffer + 28, 8);
	}
	int getLength()
	{
		return 36;
	}

	#ifdef SERVER
	string insertToSQL()
	{
		stringstream ss;
		string query;
		ss << administratorID << ", " << departmentID << ", " << userID << ", "
		   << departmentIDOfUser << ", " << diskID << ", " << capacityBeforeModify
		   << ", " << capacityAfterModify << ");";
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
		userID = atoi(temp.c_str());
		temp = pSQL->m_store[offset + 3];
		departmentIDOfUser = atoi(temp.c_str());
		temp = pSQL->m_store[offset + 4];
		diskID = atoi(temp.c_str());
		temp = pSQL->m_store[offset + 5];
		capacityBeforeModify = atoi(temp.c_str());
		temp = pSQL->m_store[offset + 6];
		capacityAfterModify = atoi(temp.c_str());
		//pSQL->closeSQL();
	}
	void registerIt(CLPraseManager *pManager)
	{
		pManager->registerHandle(this, 126, "CLModifyUserDiskCapacityLog");
	}
	#endif

	void init(int id1, int id2, int id3, int id4, int id5, int c1, int c2)
	{
		administratorID = id1;
		departmentID = id2;
		userID = id3;
		departmentIDOfUser = id4;
		diskID = id5;
		capacityBeforeModify = c1;
		capacityAfterModify = c2;
	}
	bool operator==(const CLModifyUserDiskCapacityLog &Log) const
	{
		if(administratorID != Log.administratorID)
			return false;
		if(departmentID != Log.departmentID)
			return false;
		if(userID != Log.userID)
			return false;
		if(departmentIDOfUser != Log.departmentIDOfUser)
			return false;
		if(diskID != Log.diskID)
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
	int userID;
	int departmentIDOfUser;
	int diskID;
	long long capacityBeforeModify;
	long long capacityAfterModify;
};
#endif
#ifndef CLDISKFORUSERLOG_H
#define CLDISKFORUSERLOG_H

#include <cstdio>
#include <cstdlib>
#include <cstirng>
#include <string>
#include <iostream>
#include <sstream>
#include "CLMessage.h"
#ifdef SERVER
#include "../server/include/CLSQL.h"
#include "../server/include/CLPraseManager.h"
#endif

class CLDiskForUserLog : public CLMessage
{
public:
	CLDiskForUserLog() : administratorID(0), departmentID(0), userID(0), departmentIDOfUser(0), diskID(0)
	{}
	~CLDiskForUserLog()
	{}
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
	#ifdef SERVER
	string insertToSQL()
	{
		stringstream ss;
		string query;
		ss << administratorID << ", " << departmentID << ", " << userID << ", "
				departmentIDOfUser << ", " << diskID << ");";
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
		//pSQL->closeSQL();
	}
	void registerIt(CLPraseManager *pManager)
	{
		pManager->registerHandle(this, 114, "CLDiskForUserLog");
		pManager->registerHandle(this, 115, "CLDiskForUserLog");
	}
	#endif

private:
	int administratorID;
	int departmentID:
	int userID;
	int departmentIDOfUser;
	int diskID;
};
#endif
#ifndef CLMODIFYDISKACCESSAUTHORITYLOG_H
#define CLMODIFYDISKACCESSAUTHORITYLOG_H

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

class CLModifyDiskAccessAuthorityLog : public CLMessage
{
public:
	CLModifyDiskAccessAuthorityLog() : administratorID(0), departmentID(0), diskID(0)
	{}
	~CLModifyDiskAccessAuthorityLog()
	{}
	char *serialize()
	{
		int len = 12;
		char *buffer = new char[len];
		memcpy(buffer, &administratorID, 4);
		memcpy(buffer + 4, &departmentID, 4);
		memcpy(buffer + 8, &diskID, 4);

		return buffer;
	}

	void deserialize(char *buffer)
	{
		memcpy(&administratorID, buffer, 4);
		memcpy(&departmentID, buffer + 4, 4);
		memcpy(&diskID, buffer + 8, 4);
	}
	int getLength()
	{
		return 12;
	}

	#ifdef SERVER
	string insertToSQL()
	{
		stringstream ss;
		string query;
		ss << administratorID << ", " << departmentID << ", " << diskID << ");";
		query = ss.str();
		return query;
	}
	void getResultFromSQL(int offset)
	{
		CLSQL *pSQL = CLSQL::getInstance();
		//pSQL->connectSQL("localhost", "root", "go", "log");
		//pSQL->fetchResult();
		string temp = pSQL->m_store[offset + 0];
		administrarorID = atoi(temp.c_str());
		temp = pSQL->m_store[offset + 1];
		departmentID = atoi(temp.c_str());
		temp = pSQL->m_store[offset + 2];
		diskID = atoi(temp.c_str());
	}
	void registerIt(CLPraseManager *pManager)
	{
		pManager->registerHandle(this, 120, "CLModifyDiskAccessAuthorityLog");
	}
	#endif

private:
	int administratorID;
	int departmentID;
	int diskID;
};

#endif
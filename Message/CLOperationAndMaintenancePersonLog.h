#ifndef CLOPERATIONANDMAINTENANCEPERSONLOG_H
#define CLOPERATIONANDMAINTENANCEPERSONLOG_H

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

class CLOperationAndMaintenancePersonLog : public CLMessage
{
public:
	CLOperationAndMaintenancePersonLog() : administratorID(0), departmentID(0), operationStaffID(0)
	{}
	~CLOperationAndMaintenancePersonLog()
	{}
	char *serialize()
	{
		int len = 12;
		char *buffer = new char[len];
		memcpy(buffer, &administratorID, 4);
		memcpy(buffer + 4, &departmentID, 4);
		memcpy(buffer + 8, &operationStaffID, 4);
        return buffer;
	}
	void deserialize(char *buffer)
	{
		memcpy(&administratorID, buffer, 4);
		memcpy(&departmentID, buffer + 4, 4);
		memcpy(&operationStaffID, buffer + 8, 4);
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
		ss << administratorID << ", " << departmentID << ", " << operationStaffID << ");";
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
		operationStaffID = atoi(temp.c_str());
		//pSQL->closeSQL();
	}
	void registerIt(CLPraseManager *pManager)
	{
		pManager->registerHandle(this, 112, "CLOperationAndMaintenancePersonLog");
		pManager->registerHandle(this, 113, "CLOperationAndMaintenancePersonLog");
	}
	#endif

	void init(int id1, int id2, int id3)
	{
		administratorID = id1;
		departmentID = id2;
		operationStaffID = id3;
	}
	bool operator==(const CLOperationAndMaintenancePersonLog &Log) const
	{
		if(administratorID != Log.administratorID)
			return false;
		if(departmentID != Log.departmentID)
			return false;
		if(operationStaffID != Log.operationStaffID)
			return false;

		return true;
	}

private:
	int administratorID;
	int departmentID;
	int operationStaffID;
};
#endif

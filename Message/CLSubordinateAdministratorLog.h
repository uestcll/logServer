#ifndef CLSUBORDINATEADMINSTRATORLOG_H
#define CLSUBORDINATEADMINSTRATORLOG_H

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

class CLSubordinateAdministratorLog : public CLMessage
{
public:
	CLSubordinateAdministratorLog() : administratorID(0), departmentID(0), subordinateAdministrator(0), subordinateDepartmentID(0)
	{}
	~CLSubordinateAdministratorLog()
	{}
	char* serialize()
	{
		char *buffer = new char[16];
		memcpy(buffer, &administratorID, 4);
		memcpy(buffer + 4, &departmentID, 4);
		memcpy(buffer + 8, &subordinateAdministrator, 4);
		memcpy(buffer + 12, &subordinateDepartmentID, 4);

		return buffer;
	}

	void deserialize(char *buffer)
	{
		memcpy(&administratorID, buffer, 4);
		memcpy(&departmentID, buffer + 4, 4);
		memcpy(&subordinateAdministrator, buffer + 8, 4);
		memcpy(&subordinateDepartmentID, buffer + 12, 4);
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
		ss << administratorID << ", " << departmentID << ", " << subordinateAdministrator
				<< ", " << subordinateDepartmentID << ");";
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
		string temp = pSQL->m_store[offset + 1];
		departmentID = atoi(temp.c_str());
		string temp = pSQL->m_store[offset + 2];
		subordinateDepartmentID = atoi(temp.c_str());
		string temp = pSQL->m_store[offset + 3];
		subordinateDepartmentID = atoi(temp.c_str());
		//pSQL->closeSQL();
	}
	void registerIt(CLPraseManager *pManager)
	{
		pManager->registerHandle(this, 100, "CLSubordinateAdministratorLog");
		pManager->registerHandle(this, 101, "CLSubordinateAdministratorLog");
	}
	#endif
	
private:
	int administratorID;
	int departmentID;
	int subordinateAdministrator;
    int subordinateDepartmentID;
};

#endif
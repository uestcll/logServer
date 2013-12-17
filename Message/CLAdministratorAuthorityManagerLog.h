#ifndef CLADMINISTRATORAUTHORITYMANAGERLOG_H
#define CLADMINISTRATORAUTHORITYMANAGERLOG_H

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <iostream>
#include <sstream>
#include "CLMEssage.h"

#ifdef SERVER
#include "../server/include/CLSQL.h"
#include "../server/include/CLPraseManager.h"
#endif

using namespace std;

class CLAdministraotrAuthorityManagerLog : public CLMessage
{
public:
	explicit CLAdministraotrAuthorityManagerLog() : administratorID(0), departmentID(0),
													subordinateDepartmentID(0),
													subordinateAdministratorID(0)
	{}
	~CLAdministraotrAuthorityManagerLog(){}

	char *serialize()
	{
		int len = 16;
		char *buffer = new char[16];
		memcpy(buffer, &administratorID, 4);
		memcpy(buffer + 4, &departmentID, 4);
		memcpy(buffer + 8, &subordinateDepartmentID, 4);
		memcpy(buffer + 12, &subordinateAdministratorID, 4);

		return buffer;
	}

	void deserialize(char *buffer)
	{
		memcpy(&administratorID, buffer, 4);
		memcpy(&departmentID, buffer + 4, 4);
		memcpy(&subordinateDepartmentID, buffer + 8, 4);
		memcpy(&subordinateAdministratorID, buffer + 12, 4);
	}

	int getLength()
	{
		return 16;
	}

	#ifdef SERVER
	string insertToSQL()
	{
		stringstream ss;
		ss << administratorID << ", " << departmentID + ", "
		   << subordinateAdministrator << ", " << subordinateDepartmentID << ");";
		string query = ss.str();
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
		subordinateDepartmentID = atoi(temp.c_str());
		temp = pSQL->m_store[offset + 3];
		subordinateAdministratorID = atoi(temp.c_str());
	}

	void registerIt(CLPraseManager *pManager)
	{
		pManager->registerHandle(this, 102, "CLAdministraotrAuthorityManagerLog");
		pManager->registerHandle(this, 103, "CLAdministraotrAuthorityManagerLog");
	}
	#endif

private:
	int administratorID;
	int departmentID;
	int subordinateDepartmentID;
	int subordinateAdministratorID;
};
#endif
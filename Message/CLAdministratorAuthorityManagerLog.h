#ifndef CLADMINISTRATORAUTHORITYMANAGERLOG_H
#define CLADMINISTRATORAUTHORITYMANAGERLOG_H

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

using namespace std;

class CLAdministratorAuthorityManagerLog : public CLMessage                       
{
public:
	explicit CLAdministratorAuthorityManagerLog() : administratorID(0), departmentID(0),
													subordinateDepartmentID(0),
													subordinateAdministratorID(0)
	{}
	~CLAdministratorAuthorityManagerLog(){}

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
		ss << administratorID << ", " << departmentID << ", "
		   << subordinateAdministratorID << ", " << subordinateDepartmentID << ");";
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
    void init(int id1, int id2, int id3, int id4)
    {
        administratorID = id1;
        departmentID = id2;
        subordinateDepartmentID = id4;
        subordinateAdministratorID = id3;
    }
    bool operator==(const CLAdministratorAuthorityManagerLog Log) const
    {
        if(administratorID != Log.administratorID)
            return false;
        if(departmentID != Log.departmentID)
            return false;
        if(subordinateAdministratorID != Log.subordinateAdministratorID)
            return false;
        if(subordinateDepartmentID != Log.subordinateDepartmentID)
            return false;

        return true;
    }

private:
	int administratorID;
	int departmentID;
	int subordinateDepartmentID;
	int subordinateAdministratorID;
};
#endif

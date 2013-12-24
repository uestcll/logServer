#ifndef CLSUBORDINATEDEPARTMENTACCOUNTLOG_H
#define CLSUBORDINATEDEPARTMENTACCOUNTLOG_H

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

class CLSubordinateDepartmentAccountLog : public CLMessage
{
public:
	CLSubordinateDepartmentAccountLog() : administratorID(0), departmentID(0), subordinateDepartmentID(0)
	{}
	~CLSubordinateDepartmentAccountLog()
	{}
	char *serialize()
	{
		int len = 12;
		char *buffer = new char[len];
		memcpy(buffer, &administratorID, 4);
		memcpy(buffer + 4, &departmentID, 4);
		memcpy(buffer + 8, &subordinateDepartmentID, 4);

		return buffer;
	}

	void deserialize(char *buffer)
	{
		memcpy(&administratorID, buffer, 4);
		memcpy(&departmentID, buffer + 4, 4);
		memcpy(&subordinateDepartmentID, buffer + 8, 4);
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
		ss << administratorID << ", " << departmentID << ", " << subordinateDepartmentID << ");";
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
		subordinateDepartmentID = atoi(temp.c_str());
	}


	void registerIt(CLPraseManager *pManager)
	{
		pManager->registerHandle(this, 108, "CLSubordinateDepartmentAccountLog");
		pManager->registerHandle(this, 109, "CLSubordinateDepartmentAccountLog");
	}
	#endif

	void init(int id1, int id2, int id3)
	{
		administratorID = id1;
		departmentID = id2;
		subordinateDepartmentID = id3;
	}
	bool operator==(const CLSubordinateDepartmentAccountLog &Log) const 
	{
		if(administratorID != Log.administratorID)
			return false;
		if(departmentID != Log.departmentID)
			return false;
		if(subordinateDepartmentID != Log.subordinateDepartmentID)
			return false;

		return true;
	}
	
private:
	int administratorID;
	int departmentID;
	int subordinateDepartmentID;
};
#endif

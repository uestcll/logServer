#ifndef CLSUBORDINATEACCOUNTLOG_H
#define CLSUBORDINATEACCOUNTLOG_H

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

class CLSubordinateAccountLog : public CLMessage
{
public:
	CLSubordinateAccountLog() : administratorID(0), departmentID(0), subordinateDepartmentID(0), userID(0)
	{}
	~CLSubordinateAccountLog()
	{}
	char *serialize()
	{
		int len = 16;
		char *buffer = new char[len];
		memcpy(buffer, &administratorID, 4);
		memcpy(buffer + 4, &departmentID, 4);
		memcpy(buffer + 8, &subordinateDepartmentID, 4);
		memcpy(buffer + 12, &userID, 4);

		return buffer;
	}

	void deserialize(char *buffer)
	{
		memcpy(&administratorID, buffer, 4);
		memcpy(&departmentID, buffer + 4, 4);
		memcpy(&subordinateDepartmentID, buffer + 8, 4);
		memcpy(&userID, buffer + 12, 4);
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
				<< ", " << userID << ");";
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
		userID = atoi(temp.c_str());
		//pSQL->closeSQL();
	}

	void registerIt(CLPraseManager *pManager)
	{
		pManager->registerHandle(this, 104, "CLSubordinateAccountLog");
		pManager->registerHandle(this, 105, "CLSubordinateAccountLog");
	}
	#endif

private:
	int administratorID;
	int departmentID;
	int subordinateDepartmentID;
	int userID;
};
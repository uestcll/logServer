#ifndef CLMODIFYPASSWORDLOG_H
#define CLMODIFYPASSWORDLOG_H

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

class CLModifyPasswordLog : public CLMessage
{
public:
	CLModifyPasswordLog() : administratorID(0), departmentID(0)
	{}
	~CLModifyPasswordLog()
	{}

	char* serialize()
	{
		char *buffer = new char[8];
		memcpy(buffer, &administratorID, 4);
		memcpy(buffer + 4, &departmentID, 4);
		return buffer;
	}

	void deserialize(char *buffer)
	{
		administratorID = *((int*)buffer);
		departmentID = *((int*)(buffer + 4));
	}

	int getLength()
	{
		return 8;
	}

	#ifdef SERVER
	string insertToSQL()
	{
		stringstream ss;
		string query;
		ss << administratorID << ", " << departmentID << ");";
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
		//pSQL->closeSQL();
	}
	void registerIt(CLPraseManager *pManager)
	{
		pManager->registerHandle(this, 118, "CLModifyPasswordLog");
	}
	#endif

public:
	int administratorID;
	int departmentID;
};

#endif
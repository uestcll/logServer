#ifndef CLMODIFYPASSWORDLOG_H
#define CLMODIFYPASSWORDLOG_H

#include "LibNetWork.h"
#include "CLMessage.h"
#include "CLPraseManager.h"
#include "CLSQL.h"

class CLModifyPasswordLog : public CLMessage
{
public:
	void init(int id)
	{
		CLPraseManager *manager = CLPraseManager::getInstance();
		manager->registerHandle(id, this);

	}

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

	string insertToSQL()
	{
		/*
		CLSQL *pSQL = CLSQL::getInstance();
		pSQL->connectSQL("localhost", "root", "go", "log");
		char query[1000];
		memset(query, 0, sizeof(query));
		sprintf(query, "insert into test1 values(%d, %d)", administratorID, departmentID);
		pSQL->querySQL(query);
		pSQL->closeSQL();
		*/
		string query;
		query = administratorID + ", " + departmentID + ");";
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

public:
	int administratorID;
	int departmentID;
};

#endif
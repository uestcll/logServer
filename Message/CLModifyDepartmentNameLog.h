#ifndef CLMODIFYDEPARTMENTNAMELOG_H
#define CLMODIFYDEPARTMENTNAMELOG_H

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

class CLModifyDepartmentNameLog : public CLMessage
{
public:
	CLModifyDepartmentNameLog() : administrarorID(0), departmentID(0), departmentIDOfNameModify(0), lengthOfNameBeforeModify(0), nameBeforeModify(NULL), lengthOfNameAfterModify(0), nameAfterModify(NULL)
	{}
	~CLModifyDepartmentNameLog()
	{
		if(NULL != nameBeforeModify)
		{
			delete[] nameBeforeModify;
		}
		if(NULL != nameAfterModify)
		{
			delete[] nameAfterModify;
		}
	}
	char *serialize()
	{
		int len = 20 + lengthOfNameBeforeModify + lengthOfNameAfterModify;
		char *buffer = new char[len];
		memcpy(buffer, &administrarorID, 4);
		memcpy(buffer + 4, &departmentID, 4);
		memcpy(buffer + 8, &departmentIDOfNameModify, 4);
		memcpy(buffer + 12, &lengthOfNameBeforeModify, 4);
		memcpy(buffer + 16, nameBeforeModify, lengthOfNameBeforeModify);
		memcpy(buffer + 16 + lengthOfNameBeforeModify, &lengthOfNameAfterModify, 4);
		memcpy(buffer + 20, nameAfterModify, lengthOfNameAfterModify);

		return buffer;
	}
	void deserialize(char *buffer)
	{
		memcpy(&administrarorID, buffer, 4);
		memcpy(&departmentID, buffer + 4, 4);
		memcpy(&departmentIDOfNameModify, buffer + 8, 4);
		memcpy(&lengthOfNameBeforeModify, buffer + 12, 4);
		nameBeforeModify = new char[lengthOfNameBeforeModify + 1];
		memcpy(nameBeforeModify, buffer + 16, lengthOfNameBeforeModify);
		nameBeforeModify[lengthOfNameBeforeModify] = '\0';
		memcpy(&lengthOfNameAfterModify, buffer + 16 + lengthOfNameBeforeModify, 4);
		nameAfterModify = new char[lengthOfNameAfterModify + 1];
		memcpy(nameAfterModify, buffer + 20 + lengthOfNameBeforeModify, lengthOfNameAfterModify);
		nameAfterModify[lengthOfNameAfterModify] = '\0';
	}
	int getLength()
	{
		return 20 + lengthOfNameAfterModify + lengthOfNameBeforeModify;
	}

	#ifdef SERVER
	string insertToSQL()
	{
		stringstream ss;
		string query;
		ss << administrarorID << ", " << departmentID + ", " << departmentIDOfNameModify
		   << ", " << lengthOfNameBeforeModify << ", " << "\"" << nameBeforeModify << "\"" << ", " << lengthOfNameAfterModify << << ", " << "\"" << nameAfterModify << "\"" << ");";
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
		departmentIDOfNameModify = atoi(temp.c_str());
		temp = pSQL->m_store[offset + 3];
		lengthOfNameBeforeModify = atoi(temp.c_str());
		temp = pSQL->m_store[offset + 4];
		nameBeforeModify = new char[lengthOfNameBeforeModify + 1];
		memcpy(nameBeforeModify, temp.c_str(), lengthOfNameBeforeModify);
		nameBeforeModify[lengthOfNameBeforeModify] = '\0';
		temp = pSQL->m_store[offset + 5];
		lengthOfNameAfterModify = atoi(temp.c_str());
		temp = pSQL->m_store[offset + 6];
		nameAfterModify = new char[lengthOfNameAfterModify + 1];
		memcpy(nameAfterModify, temp.c_str(), lengthOfNameAfterModify);
		nameAfterModify[lengthOfNameAfterModify] = '\0';
		//pSQL->closeSQL();
	}
	void registerIt(CLPraseManager *pManager)
	{
		pManager->registerHandle(this, 121, "CLModifyDepartmentNameLog");
	}
	#endif

private:
	int administrarorID;
	int departmentID;
	int departmentIDOfNameModify;
	int lengthOfNameBeforeModify;
	char *nameBeforeModify;
	int lengthOfNameAfterModify;
	char *nameAfterModify;
};

#endif
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
	CLModifyDepartmentNameLog() : administratorID(0), departmentID(0), departmentIDOfNameModify(0), lengthOfNameBeforeModify(0), nameBeforeModify(NULL), lengthOfNameAfterModify(0), nameAfterModify(NULL)
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
		memcpy(buffer, &administratorID, 4);
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
		memcpy(&administratorID, buffer, 4);
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
		ss << administratorID << ", " << departmentID << ", " << departmentIDOfNameModify
		   << ", " << lengthOfNameBeforeModify << ", " << "\"" << nameBeforeModify << "\"" << ", " << lengthOfNameAfterModify << ", " << "\"" << nameAfterModify << "\"" << ");";
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

	void init(int id1, int id2, int id3, int len1, char *name1, int len2, char *name2)
	{
		administratorID = id1;
		departmentID = id2;
		departmentIDOfNameModify = id3;
		lengthOfNameBeforeModify = len1;
		if(nameBeforeModify != NULL)
		{
			delete[] nameBeforeModify;
		}
		nameBeforeModify = new char[len1 + 1];
		memcpy(nameBeforeModify, name1, len1);
		nameBeforeModify[len1] = '\0';
		lengthOfNameAfterModify = len2;
		if(NULL != nameAfterModify)
		{
			delete[] nameAfterModify;
		}
		nameAfterModify = new char[len2 + 1];
		memcpy(nameAfterModify, name2, len2);
		nameAfterModify[len2] = '\0';
 	}
	bool operator==(const CLModifyDepartmentNameLog &Log) const
	{
		if(administratorID != Log.administratorID)
			return false;
		if(departmentID != Log.departmentID)
			return false;
		if(departmentIDOfNameModify != Log.departmentIDOfNameModify)
			return false;
		if(lengthOfNameBeforeModify != Log.lengthOfNameBeforeModify)
			return false;
		if(strcmp(nameBeforeModify, Log.nameBeforeModify) != 0)
			return false;
		if(lengthOfNameAfterModify != Log.lengthOfNameAfterModify)
			return false;
		if(strcmp(nameAfterModify, Log.nameAfterModify) != 0)
			return false;

		return true;
	}

private:
	int administratorID;
	int departmentID;
	int departmentIDOfNameModify;
	int lengthOfNameBeforeModify;
	char *nameBeforeModify;
	int lengthOfNameAfterModify;
	char *nameAfterModify;
};

#endif

#ifndef CLMODIFYNAMELOG_H
#define CLMODIFYNAMELOG_H

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

class CLModifyNameLog : public CLMessage
{
public:
	CLModifyNameLog() : administrarorID(0), departmentID(0), lengthOfNameBeforeModify(0),
	nameBeforeModify(NULL), lengthOfNameAfterModify(0), nameAfterModify(NULL)
	{}
	~CLModifyNameLog()
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
		memcpy(buffer + 8, &lengthOfNameBeforeModify, 4);
		memcpy(buffer + 12, nameBeforeModify, lengthOfNameBeforeModify);
		memcpy(buffer + 12 + lengthOfNameBeforeModify, &lengthOfNameAfterModify, 4);
		memcpy(buffer + 16 + lengthOfNameBeforeModify, nameAfterModify, lengthOfNameAfterModify);
		
		return buffer;
	}
	void deserialize(char * buffer)
	{
		memcpy(&administrarorID, buffer, 4);
		memcpy(&departmentID, buffer + 4, 4);
		memcpy(&lengthOfNameBeforeModify, buffer + 8, 4);
		nameBeforeModify = new char[lengthOfNameBeforeModify + 1];
		memcpy(nameBeforeModify, buffer + 12, lengthOfNameBeforeModify);
		nameBeforeModify[lengthOfNameBeforeModify] = '\0';
		memcpy(&lengthOfNameAfterModify, buffer + 12 + lengthOfNameBeforeModify, 4);
		nameAfterModify = new char[lengthOfNameAfterModify + 1];
		memcpy(nameAfterModify, buffer + 16 + lengthOfNameBeforeModify, lengthOfNameAfterModify);
	}
	int getLength()
	{
		return 20 + lengthOfNameBeforeModify + lengthOfNameAfterModify;
	}

	#ifdef SERVER
	string insertToSQL()
	{
		stringstream ss;
		string query;
		ss << administratorID << ", " << departmentID << ", " << lengthOfNameBeforeModify << ", " << "\"" << nameBeforeModify << "\"" << ", " << lengthOfNameAfterModify << ", " << "\"" << nameAfterModify << "\"" << ");";
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
		lengthOfNameBeforeModify = atoi(temp.c_str());
		temp = pSQL->m_store[offset + 3];
		nameBeforeModify = new char[lengthOfNameBeforeModify + 1];
		memcpy(nameBeforeModify, temp.c_str(), lengthOfNameBeforeModify);
		nameBeforeModify[lengthOfNameBeforeModify] = '\0';
		temp = pSQL->m_store[offset + 4];
		lengthOfNameAfterModify = atoi(temp.c_str());
		temp = pSQL->m_store[offset + 5];
		nameAfterModify = new char[lengthOfNameAfterModify + 1];
		memcpy(nameAfterModify, temp.c_str(), lengthOfNameAfterModify);
		nameAfterModify[lengthOfNameAfterModify] = '\0';
		//pSQL->closeSQL();
	}

	void registerIt(CLPraseManager *pManager)
	{
		pManager->registerHandle(this, 119, "CLModifyNameLog");
	}
	#endif

	void init(int id1, int id2, int len1, char *name1, int len2, char *name2)
	{
		administratorID = id1;
		departmentID = id2;
		lengthOfNameBeforeModify = len1;
		if(NULL != nameBeforeModify)
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
	bool operator==(const CLModifyNameLog &Log) const
	{
		if(administratorID != Log.administratorID)
			return false;
		if(departmentID != Log.departmentID)
			return false;
		if(lengthOfNameBeforeModify != Log.lengthOfNameBeforeModify)
			return false;
		if(strcmp(nameBeforeModify, name1) != 0)
			return false;
		if(lengthOfNameAfterModify != Log.lengthOfNameAfterModify)
			return false;
		if(strcmp(nameAfterModify, name2) != 0)
			return false;

		return true;
	}
private:
	int administrarorID;
	int departmentID;
	int lengthOfNameBeforeModify;   
	char *nameBeforeModify;
	int lengthOfNameAfterModify;
	char *nameAfterModify;
};
#endif
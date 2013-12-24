#ifndef CLMODIFYUSERNAMELOG_H
#define CLMODIFYUSERNAMELOG_H

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

class CLModifyUserNameLog : public CLMessage
{
public:
	CLModifyUserNameLog() : administratorID(0), departmentID(0), userID(0), departmentIDOfUser(0), lengthOfNameBeforeModify(0), nameBeforeModify(NULL), lengthOfNameAfterModify(0), nameAfterModify(NULL)
	{}
	~CLModifyUserNameLog()
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
		int len = 24 + lengthOfNameBeforeModify + lengthOfNameAfterModify;
		char *buffer = new char[len];
		memcpy(buffer, &administratorID, 4);
		memcpy(buffer + 4, &departmentID, 4);
		memcpy(buffer + 8, &userID, 4);
		memcpy(buffer + 12, &departmentIDOfUser, 4);
		memcpy(buffer + 16, &lengthOfNameBeforeModify, 4);
		memcpy(buffer + 20, nameBeforeModify, lengthOfNameBeforeModify);
		memcpy(buffer + 20 + lengthOfNameBeforeModify, &lengthOfNameAfterModify, 4);
		memcpy(buffer + 24 + lengthOfNameBeforeModify, nameAfterModify, lengthOfNameAfterModify);

		return buffer;
	}
	void deserialize(char *buffer)
	{
		memcpy(&administratorID, buffer, 4);
		memcpy(&departmentID, buffer + 4, 4);
		memcpy(&userID, buffer + 8, 4);
		memcpy(&departmentIDOfUser, buffer + 12, 4);
		memcpy(&lengthOfNameBeforeModify, buffer + 16, 4);
		nameBeforeModify = new char[lengthOfNameBeforeModify + 1];
		memcpy(nameBeforeModify, buffer + 20, lengthOfNameBeforeModify);
		nameBeforeModify[lengthOfNameBeforeModify] = '\0';
		memcpy(&lengthOfNameAfterModify, buffer + 20 + lengthOfNameBeforeModify, 4);
		nameAfterModify = new char[lengthOfNameAfterModify + 1];
		memcpy(nameAfterModify, buffer + 24 + lengthOfNameBeforeModify, lengthOfNameAfterModify);
	}
	int getLength()
	{
		return 24 + lengthOfNameBeforeModify + lengthOfNameAfterModify;
	}

	#ifdef SERVER
	string insertToSQL()
	{
		stringstream ss;
		string query;
		ss << administratorID << ", " << departmentID << ", " << userID << ", "
		   << departmentIDOfUser << ", " << lengthOfNameBeforeModify << ", " << "\"" << nameBeforeModify << "\"" << ", " << lengthOfNameAfterModify << ", " << "\""
		   << nameAfterModify << "\"" << ");";
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
		userID = atoi(temp.c_str());
		temp = pSQL->m_store[offset + 3];
		departmentIDOfUser = atoi(temp.c_str());
		temp = pSQL->m_store[offset + 4];
		lengthOfNameBeforeModify = atoi(temp.c_str());
		temp = pSQL->m_store[offset + 5];
		nameBeforeModify = new char[lengthOfNameBeforeModify + 1];
		memcpy(nameBeforeModify, temp.c_str(), lengthOfNameBeforeModify);
		nameBeforeModify[lengthOfNameBeforeModify] = '\0';
		temp = pSQL->m_store[offset + 6];
		lengthOfNameAfterModify = atoi(temp.c_str());
		temp = pSQL->m_store[offset + 7];
		nameAfterModify = new char[lengthOfNameAfterModify + 1];
		memcpy(nameAfterModify, temp.c_str(), lengthOfNameAfterModify);
		nameAfterModify[lengthOfNameAfterModify] = '\0';
		//pSQL->closeSQL();
	}
	
	void registerIt(CLPraseManager *pManager)
	{
		pManager->registerHandle(this, 122, "CLModifyUserNameLog");
	}
	#endif

	void init(int id1, int id2, int id3, int id4, int len1, char *name1, int len2, char *name2)
	{
		administratorID = id1;
		departmentID = id2;
		userID = id3;
		departmentIDOfUser = id4;
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
	bool operator==(const CLModifyUserNameLog &Log) const
	{
		if(administratorID != Log.administratorID)
			return false;
		if(departmentID != Log.departmentID)
			return false;
		if(userID != Log.userID)
			return false;
		if(departmentIDOfUser != Log.departmentIDOfUser)
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
	int userID;
	int departmentIDOfUser;
	int lengthOfNameBeforeModify;
	char *nameBeforeModify;
	int lengthOfNameAfterModify;
	char *nameAfterModify;
};

#endif

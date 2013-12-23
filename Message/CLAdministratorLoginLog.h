#ifndef CLADMINISTRATORLOGINLOG_H
#define CLADMINISTRATORLOGINLOG_H

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
class CLAdministratorLoginLog : public CLMessage
{
public:
	explicit CLAdministratorLoginLog() : administratorID(0), departmentID(0), IPType(0),
										 IPLength(0), loginIPAdress(NULL)
	{}
	~CLAdministratorLoginLog()
	{
		if(NULL != loginIPAdress)
		{
			delete loginIPAdress;
		}
	}
	char *serialize()
	{
		int len = 16 + IPLength;
		char *buffer = new char[len];
		memcpy(buffer, &administratorID, 4);
		memcpy(buffer + 4, &departmentID, 4);
		memcpy(buffer + 8, &IPType, 4);
		memcpy(buffer + 12, &IPLength, 4);
		memcpy(buffer + 16, &loginIPAdress, IPLength);

		return buffer;
	}

	int getLength()
	{
		return 20 + IPLength;
	}

	void deserialize(char *buffer)
	{
		memcpy(&administratorID, buffer, 4);
		memcpy(&departmentID, buffer + 4, 4);
		memcpy(&IPType, buffer + 8, 4);
		memcpy(&IPLength, buffer + 12, 4);
		loginIPAdress = new char[IPLength + 1];
		memcpy(loginIPAdress, buffer + 16, IPLength);
		loginIPAdress[IPLength] = '\0';
	}
	#ifdef SERVER
	string insertToSQL()
	{
		stringstream ss;
		string query;
		ss << administratorID << ", " << departmentID << ", "
		   << IPType << IPLength << ", " << "\"" << loginIPAdress << "\"" << ");";
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
		IPType = atoi(temp.c_str());
		temp = pSQL->m_store[offset + 3];
		IPLength = atoi(temp.c_str());
		temp = pSQL->m_store[offset + 4];
		loginIPAdress = new char[IPLength + 1];
		memcpy(loginIPAdress, temp.c_str(), IPLength);
		loginIPAdress[IPLength] = '\0';
		//pSQL->closeSQL();
	}
	void registerIt(CLPraseManager *pManager)
	{
		pManager->registerHandle(this, 110, "CLAdministratorLoginLog");
		pManager->registerHandle(this, 111, "CLAdministratorLoginLog");
	}
	#endif

	void init(int id1, int id2, int type, int len, char *address)
	{
		administratorID = id1;
		departmentID = id2;
		IPType = type;
		IPLength = len;
		if(NULL != loginIPAdress)
		{
			delete[] loginIPAdress;
		}
		loginIPAdress = new char[IPLength + 1];
		memcpy(loginIPAdress, address, len);
		loginIPAdress[len] = '\0';
	}
	bool operator==(const CLAdministratorLoginLog &Log) const
	{
		if(administratorID != Log.administratorID)
			return false;
		if(departmentID != Log.departmentID)
			return false;
		if(IPType != Log.IPType)
			return false;
		if(IPLength != Log.IPLength)
			return false;
		if(strcmp(loginIPAdress, Log.loginIPAdress) != 0)
			return false;

		return true;
	}
	
private:
	int administratorID;
	int departmentID;
	int IPType;
	int IPLength;
    char *loginIPAdress;
};
#endif

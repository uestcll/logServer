#ifndef CLUSERLOGINLOG_H
#define CLUSERLOGINLOG_H

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

class CLUserLoginLog : public CLMessage
{
public:
	CLUserLoginLog() : userID(0), departmentIDOfUser(0), IPType(0), IPLength(0), loginIPAddress(NULL)
	{}
	~CLUserLoginLog()
	{
		if(NULL != loginIPAddress)
		{
			delete[] loginIPAddress;
		}
	}
	char *serialize()
	{
		int len = 16 + IPLength;
		char *buffer = new char[len];
		memcpy(buffer, &userID, 4);
		memcpy(buffer + 4, &departmentIDOfUser, 4);
		memcpy(buffer + 8, &IPType, 4);
		memcpy(buffer + 12, &IPLength, 4);
		memcpy(buffer + 16, loginIPAddress, IPLength);

		return buffer;
	}

	void deserialize(char *buffer)
	{
		memcpy(&userID, buffer, 4);
		memcpy(&departmentIDOfUser, buffer + 4, 4);
		memcpy(&IPType, buffer + 8, 4);
		memcpy(&IPLength, buffer + 12, 4);
		loginIPAddress = new char[IPLength + 1];
		memcpy(loginIPAddress, buffer + 16, IPLength);
		loginIPAddress[IPLength] = '\0';
	}

	int getLength()
	{
		return 16 + IPLength;
	}
	#ifdef SERVER
	string insertToSQL()
	{
		stringstream ss;
		string query;
		ss << userID << ", " << departmentIDOfUser << ", " << IPType << ", "
		   << IPLength << ", " << "\"" << loginIPAddress << "\"" << ");";
		query = ss.str();
		return query;
	}
	void getResultFromSQL(int offset)
	{
		CLSQL *pSQL = CLSQL::getInstance();
		//pSQL->connectSQL("localhost", "root", "go", "log");
		//pSQL->fetchResult();
		string temp = pSQL->m_store[offset + 0];
		userID = atoi(temp.c_str());
		temp = pSQL->m_store[offset + 1];
		departmentIDOfUser = atoi(temp.c_str());
		temp = pSQL->m_store[offset + 2];
		IPType = atoi(temp.c_str());
		temp = pSQL->m_store[offset + 3];
		IPLength = atoi(temp.c_str());
		temp = pSQL->m_store[offset + 4];
		loginIPAddress = new char[IPLength + 1];
		memcpy(loginIPAddress, temp.c_str(), IPLength);
		loginIPAddress[IPLength] = '\0';
		//pSQL->closeSQL();
	}
	void registerIt(CLPraseManager *pManager)
	{
		pManager->registerHandle(this, 2, "CLUserLoginLog");
		pManager->registerHandle(this, 3, "CLUserLoginLog");
	}
	#endif

	void init(int id1, int id2, int type, int len, char *address)
	{
		userID = id1;
		departmentIDOfUser = id2;
		IPType = type;
		IPLength = len;
		if(NULL != loginIPAddress)
		{
			delete[] loginIPAddress;
		}
		loginIPAddress = new char[len + 1];
		memcpy(loginIPAddress, address, len);
		loginIPAddress[len] = '\0';
	}
	bool operator==(const CLUserLoginLog &Log) const 
	{
		if(userID != Log.userID)
			return false;
		if(departmentIDOfUser != Log.departmentIDOfUser)
			return false;
		if(IPType != Log.IPType)
			return false;
		if(IPLength != Log.IPLength)
			return false;
		if(strcmp(loginIPAddress, Log.loginIPAddress) != 0)
			return false;

		return true;
	}

private:
	int userID;
	int departmentIDOfUser;
    int IPType;
	int IPLength;
	char* loginIPAddress;
};

#endif

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
	CLUserLoginLog() : userID(0), departmentIDOfUser(0), IPType(0), IPlength(0), loginIPAdress(NULL)
	{}
	~CLUserLoginLog()
	{
		if(NULL != loginIPAdress)
		{
			delete[] loginIPAdress;
		}
	}
	char *serialize()
	{
		int len = 16 + IPlength;
		char *buffer = new char[len];
		memcpy(buffer, &userID, 4);
		memcpy(buffer + 4, &departmentIDOfUser, 4);
		memcpy(buffer + 8, &IPType, 4);
		memcpy(buffer + 12, &IPlength, 4);
		memcpy(buffer + 16, &loginIPAdress, IPlength);

		return buffer;
	}

	void deserialize(char *buffer)
	{
		memcpy(&userID, buffer, 4);
		memcpy(&departmentIDOfUser, buffer + 4, 4);
		memcpy(&IPType, buffer + 8, 4);
		memcpy(&IPlength, buffer + 12, 4);
		loginIPAdress = new char[IPlength + 1];
		memcpy(&loginIPAdress, buffer + 16, IPlength);
		loginIPAdress[IPlength] = '\0';
	}

	int getLength()
	{
		return 16 + IPlength;
	}
	#ifdef SERVER
	string insertToSQL()
	{
		stringstream ss;
		string query;
		ss << userID << ", " << departmentIDOfUser << ", " << IPType << ", "
		   << IPlength << ", " << "\"" << loginIPAdress << "\"" << ");";
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
		string temp = pSQL->m_store[offset + 1];
		departmentIDOfUser = atoi(temp.c_str());
		string temp = pSQL->m_store[offset + 2];
		IPType = atoi(temp.c_str());
		string temp = pSQL->m_store[offset + 3];
		IPlength = atoi(temp.str());
		string temp = pSQL->m_store[offset + 4];
		loginIPAdress = new char[IPlength + 1];
		memcpy(loginIPAdress, temp.c_str(), IPlength);
		loginIPAdress[IPlength] = '\0';
		//pSQL->closeSQL();
	}
	void registerIt(CLPraseManager *pManager)
	{
		pManager->registerHandle(this, 2, "CLUserLoginLog");
		pManager->registerHandle(this, 3, "CLUserLoginLog");
	}
	#endif

private:
	int userID;
	int departmentIDOfUser;
    int IPType;
	int IPlength;
	char* loginIPAdress;
};

#endif

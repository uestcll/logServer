#ifndef CLCHANGENODECAPACITYLOG_H
#define CLCHANGENODECAPACITYLOG_H

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

class CLChangeNodeCapacityLog : public CLMessage
{
public:
	explicit CLChangeNodeCapacityLog() : IPType(0), IPLength(0), IPAddress(NULL), lengthOfHostname(0), hostname(NULL), capacityBeforeModify(0), capacityAfterModify(0)
	{}
	~CLChangeNodeCapacityLog()
	{
		if(NULL != IPAddress)
		{
			delete[] IPAddress;
		}
		if(NULL != hostname)
		{
			delete[] hostname;
		}
	}
	char *serialize()
	{
		int len = 24 + IPLength + lengthOfHostname;
		char *buffer = new char[len];
		memcpy(buffer, &IPType, 4);
		memcpy(buffer + 4, &IPLength, 4);
		memcpy(buffer + 8, IPAddress, IPLength);
		memcpy(buffer + 8 + IPLength, &lengthOfHostname, 4);
		memcpy(buffer + 12 + IPLength, hostname, lengthOfHostname);
		memcpy(buffer + 12 + IPLength + lengthOfHostname, &capacityBeforeModify, 8);
		memcpy(buffer + 20 + IPLength + lengthOfHostname, &capacityAfterModify, 8);

		return buffer;
	}
	void deserialize(char *buffer)
	{
		memcpy(&IPType, buffer, 4);
		memcpy(&IPLength, buffer + 4, 4);
		IPAddress = new char[IPLength + 1];
		memcpy(IPAddress, buffer + 8, IPLength);
		IPAddress[IPLength] = '\0';
		memcpy(&lengthOfHostname, buffer + 8 + IPLength, 4);
		hostname = new char[lengthOfHostname + 1];
		memcpy(hostname, buffer + 12 + IPLength, lengthOfHostname);
		hostname[lengthOfHostname] = '\0';
		memcpy(&capacityBeforeModify, buffer + 12 + IPLength + lengthOfHostname, 8);
		memcpy(&capacityAfterModify, buffer + 20 + IPLength + lengthOfHostname, 8);
	}
	int getLength()
	{
		return 28 + IPLength + lengthOfHostname;
	}
	#ifdef SERVER
	string insertToSQL()
	{
		stringstream ss;
		string query;
		ss << IPType << ", " << IPLength << ", " << "\"" << IPAddress << "\"" << ", " <<lengthOfHostname << ", " << "\"" << hostname << "\"" << ", "
			<< capacityBeforeModify << ", " << capacityAfterModify << ");";
		query = ss.str();
		return query;
	}

	void getResultFromSQL(int offset)
	{
		CLSQL *pSQL = CLSQL::getInstance();
		//pSQL->connectSQL("localhost", "root", "go", "log");
		//pSQL->fetchResult();
		string temp = pSQL->m_store[offset + 0];
		IPType = atoi(temp.c_str());
		temp = pSQL->m_store[offset + 1];
		IPLength = atoi(temp.c_str());
		temp = pSQL->m_store[offset + 2];
		IPAddress = new char[IPLength + 1];
		memcpy(IPAddress, temp.c_str(), IPLength);
		IPAddress[IPLength] = '\0';
		temp = pSQL->m_store[offset + 3];
		lengthOfHostname = atoi(temp.c_str());
		temp = pSQL->m_store[offset + 4];
		hostname = new char[lengthOfHostname + 1];
		memcpy(hostname, temp.c_str(), lengthOfHostname);
		hostname[lengthOfHostname] = '\0';
		temp = pSQL->m_store[offset + 5];
		capacityBeforeModify = atoi(temp.c_str());
		temp = pSQL->m_store[offset + 6];
		capacityAfterModify = atoi(temp.c_str());
		//pSQL->closeSQL();
	}
	
	void registerIt(CLPraseManager *pManager)
	{
		pManager->registerHandle(this, 202, "CLChangeNodeCapacityLog");
		pManager->registerHandle(this, 203, "CLChangeNodeCapacityLog");
	}
	#endif

private:
	int IPType;
	int IPLength;
	char *IPAddress;
	int lengthOfHostname;
	char *hostname;
	long long capacityBeforeModify;
	long long capacityAfterModify;
};

#endif
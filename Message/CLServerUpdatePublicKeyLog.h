#ifndef CLSERVERUPDATEPUBLICKEYLOG_H
#define CLSERVERUPDATEPUBLICKEYLOG_H

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

class CLServerUpdatePublicKeyLog : public CLMessage
{
public:
	CLServerUpdatePublicKeyLog() : IPType(0), IPLength(0), IPAddress(NULL), lengthOfHostname(0), hostname(NULL)
	{}
	~CLServerUpdatePublicKeyLog()
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
	}
	int getLength()
	{
		return 12 + IPLength + lengthOfHostname;
	}
	#ifdef SERVER
	string insertToSQL()
	{
		stringstream ss;
		string query;
		ss << IPType << ", " << IPLength << ", " << "\"" << IPAddress << "\"" << ", " << lengthOfHostname << ", " << "\"" << hostname << "\"" << ");";
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
		//pSQL->closeSQL();
	}
	void registerIt(CLPraseManager *pManager)
	{
		pManager->registerHandle(this, 201, "CLServerUpdatePublicKeyLog");
	}
	#endif

	void init(int type, int len1, char *address, int len2, char *name)
	{
		IPType = type;
		IPLength = len1;
		if(NULL != IPAddress)
		{
			delete[] IPAddress;
		}
		IPAddress = new char[len1 + 1];
		memcpy(IPAddress, address, len1);
		IPAddress[len1] = '\0';
		lengthOfHostname = len2;
		if(NULL != hostname)
		{
			delete[] hostname;
		}
		hostname = new char[len2 + 1];
		memcpy(hostname, name, len2);
		hostname[len2] = '\0';
	}
	bool operator==(const CLServerUpdatePublicKeyLog &Log) const
	{
		if(IPType != Log.IPType)
			return false;
		if(IPLength != Log.IPLength)
			return false;
		if(strcmp(IPAddress, Log.IPAddress) != 0)
			return false;
		if(lengthOfHostname != Log.lengthOfHostname)
			return false;
		if(strcmp(hostname, Log.hostname) != 0)
			return false;

		return true;
	}

private:
	int IPType;
	int IPLength;
	char *IPAdress;
	int lengthOfHostname;
    char *hostname;
};

#endif
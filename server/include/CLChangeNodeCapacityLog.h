#ifndef CLCHANGENODECAPACITYLOG_H
#define CLCHANGENODECAPACITYLOG_H

#include <cstdio>
#include <cstdlib>
#include <cstring>

class CLChangeNodeCapacityLog
{
public:
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
	void insertToSQL()
	{
		CLSQL *pSQL = CLSQL::getInstance();
		pSQL->connectSQL("localhost", "root", "go", "log");
		char query[1000];
		memset(query, 0, sizeof(query));
		sprintf(query, "insert into test values(%d, %s, %s, %lld, %lld);", 
				IPType, IPAddress, hostname, 
				capacityBeforeModify, capacityAfterModify);
		pSQL->querySQL(query);
		pSQL->closeSQL();
	}

	void getResultFromSQL()
	{
		CLSQL *pSQL = CLSQL::getInstance();
		pSQL->connectSQL("localhost", "root", "go", "log");
		pSQL->fetchResult();
		string temp = pSQL->m_store[0];
		IPType = atoi(temp.c_str());
		temp = pSQL->m_store[1];
		IPLength = temp.size();
		IPAddress = new char[IPLength + 1];
		memcpy(IPAddress, temp.c_str(), IPLength);
		IPAddress[IPLength] = '\0';
		temp = pSQL->m_store[2];
		lengthOfHostname = temp.size();
		hostname = new char[lengthOfHostname + 1];
		memcpy(hostname, temp.c_str(), lengthOfHostname);
		hostname[lengthOfHostname] = '\0';
		temp = pSQL->m_store[3];
		capacityBeforeModify = atoi(temp.c_str());
		temp = pSQL->m_store[4];
		capacityAfterModify = atoi(temp.c_str());
		pSQL->closeSQL();
	}
	int getLength()
	{
		return 28 + IPLength + lengthOfHostname;
	}
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
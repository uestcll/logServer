#ifndef CLSERVERSTATUSLOG_H
#define CLSERVERSTATUSLOG_H

#include <cstdio>
#include <cstdlib>
#include <cstring>

class CLServerStatusLog
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
		memcpy(buffer + 12 + IPLength + lengthOfHostname, &cpu, 4);
		memcpy(buffer + 16 + IPLength + lengthOfHostname, &network, 4);
		memcpy(buffer + 20 + IPLength + lengthOfHostname, &memory, 4);

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
		memcpy(&cpu, buffer + 12 + IPLength + lengthOfHostname, 4);
		memcpy(&network, buffer + 16 + IPLength + lengthOfHostname, 4);
		memcpy(&memory, buffer + 20 + IPLength + lengthOfHostname, 4);
	}
	void insertToSQL()
	{
		CLSQL *pSQL = CLSQL::getInstance();
		pSQL->connectSQL("localhost", "root", "go", "log");
		char query[1000];
		memset(query, 0, sizeof(query));
		sprintf(query, "insert into test values(%d, %s, %s, %d, %d, %d);", 
			IPType, IPAddress, hostname, cpu, network, memory);
		pSQL->querySQL(query);
		pSQL->closeSQL();
	}
	int getLength()
	{
		return 24 + IPLength + lengthOfHostname;
	}
private:
	int IPType;
	int IPLength;
	char* IPAddress;
	int lengthOfHostname;
	char* hostname;
	int cpu;
	int network;
	int memory;
};

#endif
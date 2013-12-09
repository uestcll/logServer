#ifndef CLREBOOTLOG_H
#define CLREBOOTLOG_H

#include <cstdio>
#include <cstdlib>
#include <cstring>

class rebootLog : public CLMessage
{
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
	string insertToSQL()
	{
		/*
		CLSQL *pSQL = CLSQL::getInstance();
		pSQL->connectSQL("localhost", "root", "go", "log");
		char query[1000];
		memset(query, 0, sizeof(query));
		sprintf(query, "insert into test values(%d, %s, %s);", 
			IPType, IPAddress, hostname);
		pSQL->querySQL(query);
		pSQL->closeSQL();
		*/
		string query;
		query = IPType + ", " + IPAddress + ", " + hostname + ");";
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
		IPLength = temp.size();
		IPAddress = new char[IPLength + 1];
		memcpy(IPAddress, temp.c_str(), IPLength);
		IPAddress[IPLength] = '\0';
		temp = pSQL->m_store[offset + 2];
		lengthOfHostname = temp.size();
		hostname = new char[lengthOfHostname + 1];
		memcpy(hostname, temp.c_str(), lengthOfHostname);
		hostname[lengthOfHostname] = '\0';
		//pSQL->closeSQL();
	}
	int getLength()
	{
		return 12 + IPLength + lengthOfHostname;
	}
	#ifdef SERVER
	void register(CLPraseManager *pManager)
	{
		pManager->registerHandle(this, 207, "rebootLog");
	}
	#endif
private:
	int IPType;
	int IPLength;
	char *IPAddress;
	int lengthOfHostname;
	char *hostname;
};
#endif


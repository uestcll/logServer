#ifndef CLSERVERUPDATEPUBLICKEYLOG_H
#define CLSERVERUPDATEPUBLICKEYLOG_H

#include "LibNetWork.h"
#include "CLMessage.h"
#include "CLPraseManager.h"
#include "CLSQL.h"

class CLServerUpdatePublicKeyLog : public CLMessage
{
public:
	char* serialize()
	{
		int len = 4 + 16 + 4 + lengthOfHostname;
		char *buffer = new char[len];
		memcpy(buffer, &IPType, 4);
		memcpy(buffer + 4, IPAdress, 16);
		memcpy(buffer + 20, &lengthOfHostname, 4);
		memcpy(buffer + 24, hostname, lengthOfHostname);

		return buffer;
	}

	void deserialize(char *buffer)
	{
		IPType = *((int*)buffer);
		memcpy(IPAdress, buffer + 4, 16);
		lengthOfHostname = *((int*)(buffer + 20));
		hostname = new char[lengthOfHostname];
		memcpy(hostname, buffer + 24, lengthOfHostname);
	}

	int getLength()
	{
		return 24 + lengthOfHostname;
	}

	string insertToSQL()
	{
		/*
		CLSQL *pSQL = CLSQL::getInstance();
		pSQL->connectSQL("localhost", "root", "go", "log");
		char query[1000];
		memset(query, 0, sizeof(query));
		sprintf(query, "insert into test values(%d, %s, %d, %s);", IPType, IPAdress, lengthOfHostname, hostname);
		pSQL->querySQL(query);
		pSQL->closeSQL();
		*/
		stirng query;
		query = IPType + ", " + IPAdress + ", " + lengthOfHostname + ", " + hostname + ");";
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
	}

	#ifdef SERVER
	void register(CLPraseManager *pManager)
	{
		pManager->registerHandle(this, 201, "CLServerUpdatePublicKeyLog");
	}
	#endif

private:
	int IPType;
	char IPAdress[16];
	int lengthOfHostname;
    char *hostname;
};

#endif
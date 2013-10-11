#ifndef CLSERVERUPDATEPUBLICKEYLOG_H
#define CLSERVERUPDATEPUBLICKEYLOG_H

#include "LibNetWork.h"
#include "CLMessage.h"
#include "CLPraseManager.h"
#include "CLSQL.h"

class CLServerUpdatePublicKeyLog : public CLMessage
{
public:
	explicit CLServerUpdatePublicKeyLog();
	~CLServerUpdatePublicKeyLog();

	void init(int id)
	{
		 CLPraseManager *manager = CLPraseManager::getInstance();
        manager->registerHandle(id, this);
	}

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

	virtual void insertToSQL()
	{
		CLSQL *pSQL = CLSQL::getInstance();
    pSQL->connectSQL("localhost", "root", "go", "log");
        char query[1000];
        memset(query, 0, sizeof(query));
        sprintf(query, "insert into test values(%d, %s, %d, %s);", IPType, IPAdress, lengthOfHostname, hostname);
        pSQL->querySQL(query);
        pSQL->closeSQL();
	}

private:
	int IPType;
　　char IPAdress[16];
　　int lengthOfHostname;
　　char *hostname;
};

#endif
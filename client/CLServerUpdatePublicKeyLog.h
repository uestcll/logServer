#ifndef CLSERVERUPDATEPUBLICKEYLOG_H
#define CLSERVERUPDATEPUBLICKEYLOG_H

#include <cstring>
#include <iostream>
using namespace std;

class CLServerUpdatePublicKeyLog
{
public:
	explicit CLServerUpdatePublicKeyLog();
	~CLServerUpdatePublicKeyLog();

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

private:
	int IPType;
　　char IPAdress[16];
　　int lengthOfHostname;
　　char *hostname;
};

#endif
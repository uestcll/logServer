#ifndef SLADDRESS_H
#define SLADDRESS_H

#include "headfile.h"

struct SLAddress
{
	int IPType;
	char IPAddress[16];
	int port;
	char type[4];
    bool isServer;

	SLAddress() : IPType(IPV4), isServer(false)
	{
        memset(IPAddress, 0, sizeof(IPAddress));
        memset(type, 0, sizeof(type));
    }

};
#endif

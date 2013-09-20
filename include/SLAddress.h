#ifndef SLADDRESS_H
#define SLADDRESS_H

#include "headfile.h"

struct SLAddress
{
	int IPType;
	char IPAddress[16];
	int port;
	char type[4];

	SLAddress() : IPType(IPV4)
	{}

};
#endif

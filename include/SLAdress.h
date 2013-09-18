#idndef SLADDRESS_H
#define SLADDRESS_H

#include "headfile.h"

struct SLAddress
{
	int IPType;
	char IPAdress[16];
	int port;
	char type[4];

	CLAddress() : IPType(IPV4), IPaddress("127.0.0.1"), type("TCP")
	{}

};
#endif
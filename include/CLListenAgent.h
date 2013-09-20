#ifndef CLLISTENAGENT_H
#define CLLISTENAGENT_H

#include "CLAgent.h"
#include "headfile.h"
#include "SLAddress.h"

class CLListenAgent : public CLAgent
{
public:
	explicit CLListenAgent(SLAddress IPAddress);
	~CLListenAgent();
	int recevData();
    int sendData();

private:
	struct sockaddr_in m_address;
};

#endif

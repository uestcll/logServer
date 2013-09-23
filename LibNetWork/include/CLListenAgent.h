#ifndef CLLISTENAGENT_H
#define CLLISTENAGENT_H

#include "CLAgent.h"
#include "headfile.h"
#include "SLAddress.h"

class CLListenAgent : public CLAgent
{
public:
	explicit CLListenAgent(const int fd = -1);
	~CLListenAgent();
	int recevData();
    int sendData();

};

#endif

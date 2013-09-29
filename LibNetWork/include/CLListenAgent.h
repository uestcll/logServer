#ifndef CLLISTENAGENT_H
#define CLLISTENAGENT_H

#include "CLAgent.h"
#include "headfile.h"
#include "SLAddress.h"

template<typename T>
class CLListenAgent : public CLAgent
{
public:
	explicit CLListenAgent(const int fd = -1);
	explicit CLListenAgent(const SLAddress address);
	~CLListenAgent();
	int recevData();
    int sendData();

};

#endif

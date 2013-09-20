#ifndef CLRELAYAGENT_H
#define CLRELAYAGENT_H

#include "SLAddress.h"
#include "CLBuffer.h"
#include "CLAgent.h"

class CLRelayAgent : public CLAgent
{
public:
	explicit CLRelayAgent(const SLAddress IPAddress);
	~CLRelayAgent();

	int recevData();
	int sendData();

private:
	CLBuffer m_buffer;
};

#endif

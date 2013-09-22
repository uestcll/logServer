#ifndef CLRELAYAGENT_H
#define CLRELAYAGENT_H

#include "SLAddress.h"
#include "CLBuffer.h"
#include "CLAgent.h"
#include "CLProcessRequest.h"

class CLBuffer;

class CLRelayAgent : public CLAgent
{
public:
	explicit CLRelayAgent(const int id, const SLAddress IPAddress);
	~CLRelayAgent();

	int recevData();
	int sendData();
    void setState(bool state);
    void setProcess(CLProcessRequest *process);

private:
	CLBuffer *m_buffer;
    bool m_state;
    CLProcessRequest *m_process;
};

#endif

#ifndef CLCOMMUNICATION_H
#define CLCOMMUNICATION_H

#include "SLAddress.h"
#include "CLBuffer.h"
#include "CLAgent.h"
#include "CLProcessRequest.h"

class CLBuffer;
class CLProcessRequest;

class CLCommunication : public CLAgent
{
public:
	explicit CLCommunication(const int fd = -1);
	~CLCommunication();

	int recevData();
	int sendData();
    void setState(bool state);
    void setProcess(CLProcessRequest *process);
    //void getRequest(SLRequest *request);
    void writeToServer(struct iovec hello);

private:
	CLBuffer *m_buffer;
    bool m_state;
    CLProcessRequest *m_process;
};

#endif

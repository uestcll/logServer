#include "../include/CLRelayAgent.h"
#include "../include/CLSocket.h"
#include "../include/CLBuffer.h"
#include "../include/headfile.h"
#include "../include/SLResponse.h"

CLRelayAgent::CLRelayAgent(const int fd, CLProcessRequest *process) : CLAgent(fd), m_state(true), m_process(process)
{
    m_buffer = new CLBuffer();
    m_buffer->setRelayAgent(this);
}

CLRelayAgent::~CLRelayAgent()
{
    if(NULL != m_buffer)
        delete m_buffer;
}

int CLRelayAgent::recevData()
{
    if(!m_state)
        return FAILED;

	int n = m_buffer->readBuffer(m_socket);
    if(FINISHED == n)
    {
        m_process->work();
        struct iovec result = m_process->getResult();
        SLResponse response;
        response.io = result;
        response.finished = true;
        m_buffer->addToBuffer(response);
    }

    return n;

}

int CLRelayAgent::sendData()
{
    if(!m_state)
        return FAILED;

	return m_buffer->writeBuffer(m_socket);
}

void CLRelayAgent::setState(bool state)
{
    m_state = state;
}

void CLRelayAgent::setProcess(CLProcessRequest *process)
{
    m_process = process;
}

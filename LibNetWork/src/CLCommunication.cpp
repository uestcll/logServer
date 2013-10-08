#include "../include/CLCommunication.h"
#include "../include/CLSocket.h"
#include "../include/CLBuffer.h"
#include "../include/headfile.h"
#include "../include/SLResponse.h"

CLCommunication::CLCommunication(const int fd) : CLAgent(fd), m_state(true), m_process(NULL)
{
    m_buffer = new CLBuffer();
    m_buffer->setCommunication(this);
}

CLCommunication::~CLCommunication()
{
    if(NULL != m_buffer)
        delete m_buffer;
    if(NULL != m_process)
        delete m_process;
}

int CLCommunication::recevData()
{
    if(!m_state)
        return FAILED;

	int n = m_buffer->readBuffer(m_socket);
    if(FINISHED == n)
    {
        SLRequest *request = new SLRequest;
        while(true)
        {
            m_buffer->getRequest(request);
            if(NULL == request)
                break;
            m_process->work(request);
            delete[] request->readbuffer;
            delete request;
            struct iovec result = m_process->getResult();
            SLResponse response;
            response.io = result;
            response.finished = true;
            if(NULL != result.iov_base)
                m_buffer->addToBuffer(response);
        }
    }

    return n;

}

int CLCommunication::sendData()
{
    if(!m_state)
        return FAILED;

	return m_buffer->writeBuffer(m_socket);
}

void CLCommunication::setState(bool state)
{
    m_state = state;
}

void CLCommunication::setProcess(CLProcessRequest *process)
{
    m_process = process;
    m_process->setCommunication(this);
}

/*void CLCommunication::getRequest(SLRequest *request)
{
    m_buffer->getRequest(request);
}*/

void CLCommunication::writeToServer(struct iovec hello)
{
    SLResponse response;
    response.io = hello;
    response.finished = true;
    m_buffer->addToBuffer(response);
}

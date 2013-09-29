#include "../include/CLListenAgent.h"
#include "../include/CLSocket.h"
#include "../include/CLCommunicationAgent.h"
#include "../include/CLAgentManager.h"
#include "../include/CLEpoll.h"
#include "../include/CLEpollEvent.h"
#include "../include/CLProcessRequest.h"

CLListenAgent::CLListenAgent(const int fd) : CLAgent(fd)
{
}

CLListenAgent::CLListenAgent(const SLAddress address) : CLAgent(address)
{
}

CLListenAgent::~CLListenAgent()
{

}

int CLListenAgent::recevData()
{
	int tempfd = m_socket->acceptSocket();
	T *pT = new T();
    CLAgent *pAgent = new CLCommunicationAgent(tempfd);
    pAgent->setProcess((CLProcessRequest*)pT);
    CLEpollEvent myevent;
    myevent.setParameter(pAgent, tempfd, EPOLL_CTL_ADD, EPOLLIN);
    CLEpoll *pEpoll = CLEpoll::getInstance();
    pEpoll->workWithEpoll(&myevent);

    return tempfd;

}

int CLListenAgent::sendData()
{
    return SUCCESSFUL;
}

#include "../include/CLListenAgent.h"
#include "../include/CLSocket.h"
#include "../include/CLRelayAgent.h"
#include "../include/CLAgentManager.h"
#include "../include/CLEpoll.h"
#include "../include/CLEpollEvent.h"

CLListenAgent::CLListenAgent(const int fd) : CLAgent(fd)
{
}

CLListenAgent::~CLListenAgent()
{

}

int CLListenAgent::recevData()
{
	int tempfd = m_socket->acceptSocket();
    CLAgentManager *pManager = CLAgentManager::getInstance();
    CLAgent *pAgent = pManager->createAgent<CLRelayAgent>(tempfd);
    CLEpollEvent myevent;
    myevent.setParameter(pAgent, tempfd, EPOLL_CTL_ADD, EPOLLIN);
    CLEpoll *pEpoll = CLEpoll::getInstance();
    pEpoll->addToEpoll(&myevent);

    return tempfd;
}

int CLListenAgent::sendData()
{
    return SUCCESSFUL;
}

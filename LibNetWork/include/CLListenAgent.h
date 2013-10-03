#ifndef CLLISTENAGENT_H
#define CLLISTENAGENT_H

#include "CLAgent.h"
#include "headfile.h"
#include "SLAddress.h"
#include "CLCommunication.h"
#include "CLEpollEvent.h"
#include "CLEpoll.h"

template<typename T>
class CLListenAgent : public CLAgent
{
public:
	explicit CLListenAgent(const int fd = -1) : CLAgent(fd)
{}

	explicit CLListenAgent(const SLAddress address) : CLAgent(address)
{}
	~CLListenAgent()
{}
	int recevData()
{
    int tempfd = m_socket->acceptSocket();
	T *pT = new T();
    CLCommunication *pAgent = new CLCommunication(tempfd);
    pAgent->setProcess((CLProcessRequest*)pT);
    CLEpollEvent myevent;
    myevent.setParameter((CLAgent*)pAgent, tempfd, EPOLL_CTL_ADD, EPOLLIN);
    CLEpoll *pEpoll = CLEpoll::getInstance();
    pEpoll->workWithEpoll(&myevent);

    return tempfd;
}
    int sendData()
{
    return SUCCESSFUL;
}

};

#endif

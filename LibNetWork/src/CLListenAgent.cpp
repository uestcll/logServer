#include "../include/CLListenAgent.h"
#include "../include/CLSocket.h"
#include "../include/CLCommunication.h"
#include "../include/CLAgentManager.h"
#include "../include/CLEpoll.h"
#include "../include/CLEpollEvent.h"
#include "../include/CLProcessRequest.h"

template<typename T>
CLListenAgent<T>::CLListenAgent(const int fd) : CLAgent(fd)
{
}

template<typename T>
CLListenAgent<T>::CLListenAgent(const SLAddress address) : CLAgent(address)
{
}

template<typename T>
CLListenAgent<T>::~CLListenAgent()
{

}

template<typename T>
int CLListenAgent<T>::recevData()
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

template<typename T>
int CLListenAgent<T>::sendData()
{
    return SUCCESSFUL;
}

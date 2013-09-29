/*
 * =====================================================================================
 *
 *       Filename:  startup.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  09/21/13 15:12:51
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:   (), 
 *        Company:  NDSL
 *
 * =====================================================================================
 */
#include "headfile.h"

int main(int argc, char *argv[])
{
    if(2 != argc)
    {
        cerr << "parameter error, please input port" << endl;
        exit(-1);
    }

    SLAddress address;
    address.isServer = true;
    memcpy(address.type, "tcp");
    address.port = atoi(argv[1]);
    CLListenAgent listenAgent(address);

    CLEpollEvent myevent;
    myevent.setParameter(&listenAgent, listenAgent.getFd(), EPOLL_CTL_ADD, EPOLLIN);
    CLEpoll *pEpoll = CLEpoll::getInstance();
    pEpoll->addToEpoll(&myevent);

    pEpoll->run();
    return 0;
}

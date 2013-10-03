#include "../include/CLEchoServer.h"

int main(int argc, char *argv[])
{
    if(2 != argc)
    {
        cerr << "argv error, the parameter : port " << endl;
        exit(0);
    }

    SLAddress address;
    address.port = atoi(argv[1]);
    address.isServer = true;
    CLListenAgent<CLEchoServer> myAgent;
    myAgent.initAgent(address);

    CLEpollEvent myevent;
    myevent.setParameter(&myAgent, myAgent.getFd(), EPOLL_CTL_ADD, EPOLLIN);

    CLEpoll *pEpoll = CLEpoll::getInstance();
    pEpoll->workWithEpoll(&myevent);
    pEpoll->runEpoll();

    return 0;
}

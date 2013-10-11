#include "../include/CLLoggerProcess.h"
#include "../include/CLUserAccessDiskLog.h"
#include "../include/CLModifyPasswordLog.h"
#include "../include/CLQueryByLog.h"

int main(int argc, char *argv[])
{
    if(2 != argc)
    {
        cerr << "argv error, the parameter : port " << endl;
        exit(0);
    }

    CLUserAccessDiskLog access;
    access.init(1);
    CLModifyPasswordLog password;
    password.init(2);
    CLQueryByLog query;
    query.init(3);
    CLEpoll *pEpoll = CLEpoll::getInstance();
    SLAddress address;
    address.port = atoi(argv[1]);
    address.isServer = true;
    CLListenAgent<CLLoggerProcess> myAgent;
    myAgent.initAgent(address, true);

    CLEpollEvent myevent;
    myevent.setParameter(&myAgent, myAgent.getFd(), EPOLL_CTL_ADD, EPOLLIN);

    pEpoll->workWithEpoll(&myevent);
    pEpoll->runEpoll();

    return 0;
}

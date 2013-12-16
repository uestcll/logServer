#include "../include/CLLoggerProcess.h"
#include "../include/CLSQL.h"
#include "../include/CLPraseManager.h"
#include "LibNetWork.h"

void init();
int main(int argc, char *argv[])
{
    /*
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
    */

    if(5 != argc)
    {
        cerr << "argv error, the parameter : port, mysql username, password, databasename " << endl;
        exit(0);
    }
    CLSQL *pSQL = CLSQL::getInstance();
    pSQL->setParameter(argv[2], argv[3], argv[4]);
    init();
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

void init()
{
    CLPraseManager *pManager = CLPraseManager::getInstance();
    CLAbnormalAndErrnoLog  *pAbnormalAndErrnoLog = new CLAbnormalAndErrnoLog;
    pAbnormalAndErrnoLog->register(pManager);
}
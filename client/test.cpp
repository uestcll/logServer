/*
 * =====================================================================================
 *
 *       Filename:  startup.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/07/2013 09:03:17 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lemon (zyl), lemon_wonder@163.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include "CLClientProcess.h"

int main(int argc, char *argv[])
{
    if(4 != argc)
    {
        cerr << "parameter error, the true format is : IP, port, the number of connection" << endl;
        exit(0);
    }

    CLEpoll *pEpoll = CLEpoll::getInstance();
    SLAddress address;
    memcpy(address.IPAddress, argv[1], strlen(argv[1]));
    address.port = atoi(argv[2]);
    address.isServer = false;

    int connectnumber = atoi(argv[3]);
    for(int i = 0; i < connectnumber; ++i)
    {
        CLCommunication *pAgent = new CLCommunication();
        pAgent->initAgent(address, false);
        CLClientProcess *p = new CLClientProcess();
        pAgent->setProcess(p);
        CLEpollEvent myevent;
        myevent.setParameter((CLAgent*)pAgent, pAgent->getFd(), EPOLL_CTL_ADD, EPOLLIN);
        pEpoll->workWithEpoll(&myevent);
        p->init();
    }

    pEpoll->runEpoll();
    return 0;
}

#include "../include/CLEchoClient.h"

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
        CLEpollEvent myevent;
        myevent.setParameter((CLAgent*)pAgent, pAgent->getFd(), EPOLL_CTL_ADD, EPOLLIN);
        pEpoll->workWithEpoll(&myevent);
        struct iovec io;
        SLMessageHead head;
        head.length = 5;
        head.cmd = head.reserved = 0;
        io.iov_base = new char[5 + sizeof(SLMessageHead)];
        memcpy(io.iov_base, &head, sizeof(SLMessageHead));
        memcpy((char*)io.iov_base + sizeof(SLMessageHead), "hello", 5);
        io.iov_len = 5 + sizeof(SLMessageHead);
        pAgent->writeToServer(io);
    }

    pEpoll->runEpoll();

    return 0;
}

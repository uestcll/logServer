#ifndef CLSOCKET_H
#define CLSOCKET_H

#include "headfile.h"

struct SLAddress;

class CLSocket
{
    public:
        explicit CLSocket(const SLAddress address);
        ~CLSocket();
        int getFd();
        int readSocket(char *buffer, const int len);
        int writeSocket(const struct iovec *iov, int cnt);
        int setNonBlock();
        int connectSocket();
        int listenSocket();
        int bindSocket();
        int acceptSocket();
        //int closeSocket();

    private:
        CLSocket(CLSocket&);
        CLSocket& operator=(CLSocket&);

    private:
        int m_socketfd;
        struct sockaddr_in m_address;
        const int Qlen;
};

#endif

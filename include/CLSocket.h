#ifndef CLSOCKET_H
#define CLSOCKET_H

class CLSocket
{
    public:
        explicit CLSocket(const char *IPAdress, const int port);
        ~CLSocket();
        int getFd();
        int readSocket(char *buffer, int len);
        int writeSocket(char *buffer, int len);
        int setNonBlock();
        int connectSocket();
        int listenSocket();
        int bindSocket();
        int acceptSocket();

    private:
        CLSocket& CLSocket(CLSocket&);
        CLSocket& operator=(CLSocket&);

    private:
        int m_socketfd;
        struct sockaddr_in m_address;
        const int Qlen;
};

#endif

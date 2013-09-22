/*
 * =====================================================================================
 *
 *       Filename:  CLSocket.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013/9/12 21:50:54
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lemon (lemon), lemon_wonder@163.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include "../include/CLSocket.h"
#include "../include/SLAddress.h"

CLSocket::CLSocket(const SLAddress address) : Qlen(3000)
{
    m_socketfd = socket(PF_INET, SOCK_STREAM, 0);

    if(m_socketfd < 0)
    {
        perror("socket create error\n");
    }

    bzero(&m_address, sizeof(m_address));
    m_address.sin_family = AF_INET;
    m_address.sin_port = htons(address.port);
    if(!address.isServer)
    {
        inet_pton(AF_INET, address.IPAddress, &m_address.sin_addr);
    }
    else
    {
        m_address.sin_addr.s_addr = htonl(INADDR_ANY);
    }
}

CLSocket::~CLSocket()
{
    if(close(m_socketfd) < 0)
    {
        perror("close error");
    }
}

int CLSocket::getFd()
{
    return m_socketfd;
}

int CLSocket::readSocket(char *buffer, const int len)
{
    int n = read(m_socketfd, buffer, len);
    if(n < 0)
    {
        perror("read error");
        return FAILED;
    }
    return n;
}

int CLSocket::writeSocket(const struct iovec *iov, int len)
{
    int n = writev(m_socketfd, iov, len);
    if(n < 0)
    {
        perror("write error");
        return FAILED;
    }
    return n;
}

int CLSocket::setNonBlock()
{
    int flag = fcntl(m_socketfd, F_GETFL);
    flag |= O_NONBLOCK;
    if(fcntl(m_socketfd, F_SETFL, flag) < 0)
    {
        perror("F_SETFL error");
        return FAILED;
    }

    return SUCCESSFUL;
}

int CLSocket::connectSocket()
{
    socklen_t len = sizeof(m_address);
    int n = connect(m_socketfd, (struct sockaddr*)&m_address, len);

    if(n < 0)
    {
        perror("connect error");
        return FAILED;
    }

    return SUCCESSFUL;
}

int CLSocket::listenSocket()
{
    int n = listen(m_socketfd, Qlen);
    if(n < 0)
    {
        perror("listen error");
        return FAILED;
    }
    return SUCCESSFUL;
}

int CLSocket::bindSocket()
{
    socklen_t len = sizeof(m_address);
    int n = bind(m_socketfd, (struct sockaddr*)&m_address, len);
    if(n < 0)
    {
        perror("bin socket error");
        return FAILED;
    }
    return SUCCESSFUL;
}

int CLSocket::acceptSocket()
{
    socklen_t len;
    struct sockaddr_in temppeer;
    len = sizeof(temppeer);
    int n = accept(m_socketfd, (struct sockaddr*)&temppeer, &len);
    if(n < 0)
    {
        perror("accept error");
        return FAILED;
    }

    return SUCCESSFUL;
}

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
#include "../include/headfile.h"

CLSocket::CLSocket(const char *IPAdress, const int port) : Qlen(3000)
{
    m_socketfd = socket(PF_INET, SOCK_STREAM, 0);

    if(m_socketfd < 0)
    {
        perror("socket create error\n");
    }

    bzero(m_adress, sizeof(m_adress));
    m_adress.sin_family = AF_INET;
    m_adress.sin_port = htons(port);
    inetpton(AF_INET, IPAdress, (void*)m_adress);
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

int CLSocket::readSocket(char *buffer, int len)
{
    int n = read(m_socketfd, buffer, len);
    if(n < 0)
    {
        perror("read error");
    }
    return n;
}

int CLSocket::writeSocket(char *buffer, int len)
{
    int n = write(m_socketfd, buffer, len);
    if(n < 0)
    {
        perror("write error");
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
        return -1;
    }

    return 0;
}

int CLSocket::connectSocket()
{
    socklen_t len = sizeof(m_address);
    int n = connect(m_socketfd, (struct sockaddr*)&m_sin, len);

    if(n < 0)
    {
        perror("connect error");
    }

    return n;
}

int CLSocket::listenSocket()
{
    int n = listen(m_socketfd, Qlen);
    if(n < 0)
    {
        perror("listen error");
    }
    return n;
}

int CLSocket::bindSocket()
{
    socklen_t len = sizeof(m_address);
    int n = bind(m_socketfd, (struct sockaddr*)&m_address, len);
    if(n < 0)
    {
        perror("bin socket error");
    }
    return n;
}

int CLSocket::acceptSocket()
{
    socklen_t len;
    int n = accept(m_socketfd, (struct sockaddr*)&m_address, &len);
    if(n < 0)
    {
        perror("accept error");
    }

    return n;
}

/*
 * =====================================================================================
 *
 *       Filename:  CLAgent.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013/9/13 10:50:02
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lemon (lemon), lemon_wonder@163.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include "../include/CLSocket.h"
#include "../include/CLAgent.h"
#include "../include/headfile.h"
#include "../include/SLAddress.h"

CLAgent::CLAgent(const int fd)
{
    m_socket = new CLSocket(fd);
}

void CLAgent::initAgent(const SLAddress address, const bool block)
{
    m_socket->initSocket(address, block);
}

CLAgent::~CLAgent()
{
    if(NULL != m_socket)
    {
        delete m_socket;
    }
}

int CLAgent::recevData()
{
    return SUCCESSFUL;
}

int CLAgent::sendData()
{
    return SUCCESSFUL;
}

int CLAgent::getId()
{
    return m_id;
}

int CLAgent::getFd()
{
    return m_socket->getFd();
}

void CLAgent::setId(const int id)
{
    m_id = id;
}


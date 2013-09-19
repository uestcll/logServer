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
#include "../include/CLBuffer.h"
#include "../include/SLAddress.h"

CLAgent::CLAgent(const SLAddress address)
{
    m_socket = new CLSocket(address);
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

int CLAgent::getID()
{
    return m_ID;
}

int CLAgent::getFd()
{
    return m_socket->getFd();
}

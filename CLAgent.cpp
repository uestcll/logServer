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

CLAgent::CLAgent(const int ID, const char *IPAddress, const int port) : m_id(ID), m_state(BEFORECONNECTTED)
{
    m_socket = new CLSocket(IPAdress, port);
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

int CLAgent::getCurrentState()
{
    return m_state;
}

int CLAgent::getID()
{
    return m_ID;
}

int CLAgent::getFd()
{
    return m_socket->getFd();
}

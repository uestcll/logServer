/*
 * =====================================================================================
 *
 *       Filename:  CLEpoll.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013/9/13 12:05:07
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lemon (lemon), lemon_wonder@163.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include "../include/headfile.h"
#include "../include/CLEpoll.h"
#include "../include/CLEpollEvent.h"

CLEpoll::m_epoll = NULL;

static CLEpoll* CLEpoll::getInstance()
{
    if(NULL == m_epoll)
    {
        m_epoll = new CLEpoll();
    }

    return m_epoll;
}

int CLEpoll::addToEpoll(const CLEpollEvent *event)
{

}

int CLEpoll::modifyEpollEvent(const CLEpollEvent *event)
{

}

int CLEpoll::deleteFromEpoll(const CLEpollEvent *event)
{

}

void CLEpoll::runEpoll(const int waittime)
{

}

CLEpoll::CLEpoll()
{

}

CLEpoll::~CLEpoll()
{

}

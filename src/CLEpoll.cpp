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
	struct epoll_event ev;
    memset(&ev, 0, sizeof( struct epoll_event));
    ev.events = event->events;
    ev.data.ptr = event;
    if( epoll_ctl( mEpollFd, event->op, event->fd, &ev) < 0)
    {
        return -1;
    }
    return 0; 
}

int CLEpoll::modifyEpollEvent(const CLEpollEvent *event)
{
	struct epoll_event ev;
    memset(&ev, 0, sizeof( struct epoll_event));
    ev.events = event->events;
    ev.data.ptr = event;
    if( epoll_ctl( mEpollFd, event->op, event->fd, &ev) < 0)
    {
        return -1;
    }
    return 0; 
}

int CLEpoll::deleteFromEpoll(const CLEpollEvent *event)
{
    if( epoll_ctl( mEpollFd, event->op, event->fd, NULL) < 0)
    {
        return -1;
    }
    return 0; 
}

void CLEpoll::runEpoll(const int waittime)
{
    int ndfs = epoll_wait(m_epfd, events, 3000);
}

CLEpoll::CLEpoll()
{
	m_epfd = epoll_create(3000);
}

CLEpoll::~CLEpoll()
{

}

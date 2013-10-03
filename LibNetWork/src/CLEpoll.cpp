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
#include "../include/CLAgent.h"

CLEpoll* CLEpoll::m_epoll = NULL;

CLEpoll* CLEpoll::getInstance()
{
    if(NULL == m_epoll)
    {
        m_epoll = new CLEpoll();
    }

    return m_epoll;
}

int CLEpoll::workWithEpoll(CLEpollEvent *event)
{
    struct epoll_event ev;
    memset(&ev, 0, sizeof( struct epoll_event));
    ev.events = event->events;
    ev.data.ptr = event->pAgent;
    if( epoll_ctl( m_epfd, event->op, event->fd, &ev) < 0)
    {
        return FAILED;
    }
    return SUCCESSFUL; 
}

/*int CLEpoll::addToEpoll(CLEpollEvent *event)
{
	struct epoll_event ev;
    memset(&ev, 0, sizeof( struct epoll_event));
    ev.events = event->events;
    ev.data.ptr = event;
    if( epoll_ctl( m_epfd, event->op, event->fd, &ev) < 0)
    {
        return -1;
    }
    return 0; 
}

int CLEpoll::modifyEpollEvent(CLEpollEvent *event)
{
	struct epoll_event ev;
    memset(&ev, 0, sizeof( struct epoll_event));
    ev.events = event->events;
    ev.data.ptr = event;
    if( epoll_ctl(m_epfd, event->op, event->fd, &ev) < 0)
    {
        return -1;
    }
    return 0; 
}

int CLEpoll::deleteFromEpoll(CLEpollEvent *event)
{
    if( epoll_ctl(m_epfd, event->op, event->fd, NULL) < 0)
    {
        return -1;
    }
    return 0; 
}*/

void CLEpoll::runEpoll(const int waittime)
{
    struct epoll_event events[MAXN];
    while(true)
    {
        int ndfs = epoll_wait(m_epfd, events, MAXN, waittime);
        for(int i = 0; i < ndfs; ++i)
        {
            CLAgent *pAgent = (CLAgent*)events[i].data.ptr;

            if(events[i].events & EPOLLHUP || events[i].events & EPOLLERR)
            {
                perror("EPOLLHUP or EPOLLERR happened");
            }
            else if(events[i].events & EPOLLOUT)
            {
                pAgent->sendData();
            }
            else if(events[i].events & EPOLLIN)
            {
                pAgent->recevData();
            }
            else
            {
                perror("unknown thing happened");
            }
        }
    }
}

CLEpoll::CLEpoll()
{
	m_epfd = epoll_create(MAXN);
}

CLEpoll::~CLEpoll()
{
    close(m_epfd);
}

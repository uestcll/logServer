/*
 * =====================================================================================
 *
 *       Filename:  CLEpoll.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013/9/13 10:51:21
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lemon (lemon), lemon_wonder@163.com
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef CLEPOLL_H
#define CLEPOLL_H

class CLEpollEvent;
class CLEpoll
{
    public:
        static CLEpoll* getInstance();
        int addToEpoll(CLEpollEvent *event);
        int modifyEpollEvent(CLEpollEvent *event);
        int deleteFromEpoll(CLEpollEvent *event);
        void runEpoll(const int waittime = -1);

    private:
        explicit CLEpoll();
        ~CLEpoll();

    private:
        static CLEpoll *m_epoll;
        int m_epfd;
};

#endif

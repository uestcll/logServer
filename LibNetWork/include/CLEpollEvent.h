/*
 * =====================================================================================
 *
 *       Filename:  CLEpollEvent.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013/9/17 23:35:57
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lemon (lemon), lemon_wonder@163.com
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef CLEPOLLEVENT_H
#define CLEPOLLEVENT_H

class CLAgent;

struct CLEpollEvent
{
    public:
        explicit CLEpollEvent();
        ~CLEpollEvent();
        void setParameter(CLAgent *pAgent, int fd, int op, int events);

    public:        
        CLAgent *pAgent;
        int fd;
        int op;
        int events;
};

#endif

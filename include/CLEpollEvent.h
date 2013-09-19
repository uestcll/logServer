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

class CLEpollEvent
{
    public:
        explicit CLEpollEvent();
        ~CLEpoll();

    private:
    	CLAgent *m_pAgent;
    	int m_fd;
    	int m_op;
    	int events;
};

#endif

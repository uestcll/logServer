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

#ifndef SLEPOLLEVENT_H
#define SLEPOLLEVENT_H

struct SLEpollEvent
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

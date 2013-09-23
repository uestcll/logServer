/*
 * =====================================================================================
 *
 *       Filename:  CLEpollEvent.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  09/22/13 21:26:56
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:   (), 
 *        Company:  NDSL
 *
 * =====================================================================================
 */
#include "../include/CLEpollEvent.h"

CLEpollEvent::CLEpollEvent()
{

}

CLEpollEvent::~CLEpollEvent()
{
}

void CLEpollEvent::setParameter(CLAgent *pAgent, int fd, int op, int events)
{
    this->pAgent = pAgent;
    this->fd = fd;
    this->op = op;
    this->events = events;
}

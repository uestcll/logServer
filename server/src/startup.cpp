/*
 * =====================================================================================
 *
 *       Filename:  startup.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  09/21/13 15:12:51
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:   (), 
 *        Company:  NDSL
 *
 * =====================================================================================
 */
#include <iostream>
 #include "../include/CLLogProcessor.h"

 using namespace std;

 int main(int argc, char *argv[])
 {
 	CLAgentManager *p_manager = CLAgentManager::getInstance();
 	p_manager->setProcessor(new CLLogProcessor());
    CLListenAgent listenAgent;
    CLEpollEvent myevent;
    myevent.setParameter(&listenAgent, listenAgent.getFd(), EPOLL_CTL_ADD, EPOLLIN);

    CLEpoll *pEpoll = CLEpoll::getInstance();
    pEpoll->run();

    return 0;  
 }

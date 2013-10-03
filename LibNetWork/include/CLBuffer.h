/*
 * =====================================================================================
 *
 *       Filename:  CLBuffer.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013/9/15 19:34:57
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lemon (lemon), lemon_wonder@163.com
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef CLBUFFER_H
#define CLBUFFER_H

#include "SLResponse.h"
#include "CLSocket.h"
#include "headfile.h"
#include "SLRequest.h"
#include "CLCommunication.h"

class CLCommunication;

class CLBuffer
{
    public:
        explicit CLBuffer();
        ~CLBuffer();
        int addToBuffer(SLResponse response);
        int readBuffer(CLSocket *mysocket);
        int writeBuffer(CLSocket *mysocket);
        void processError();
        void setCommunication(CLCommunication *pAgent);
        void getRequest(SLRequest* &request);
               
    private:
        CLBuffer(CLBuffer&);
        CLBuffer& operator=(CLBuffer&);

    private:
        list<SLResponse> m_list;
        queue<SLRequest> m_queue;
        void *m_lastchange;
        int m_readlength;
        SLRequest m_request;
        CLCommunication *m_pAgent;
        int m_epollstate;
};

#endif

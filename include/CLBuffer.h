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

#include "SLReponse.h"
#include <list>
 #include "CLSocket.h"
 
 class CLAgent;

class CLBuffer
{
    public:
        explicit CLBuffer();
        ~CLBuffer();
        int addToBuffer(SLReponse response);
        int readBuffer(CLSocket *mysocket, SLRequest request);
        int writeBuffer(CLSokcet *mysocket);
        void processError();
        void setAgent(CLAgent *pAgent);
               
    private:
        CLBuffer(CLBuffer&);
        CLBuffer& operator=(CLBuffer&);

    private:
        list<SLReponse> m_list;
        char *m_lastchange;
        int m_readlength;
        SLRequest m_request;
        CLAgent *m_pAgent;
};

#endif

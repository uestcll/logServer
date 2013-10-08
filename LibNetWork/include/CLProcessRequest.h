/*
 * =====================================================================================
 *
 *       Filename:  CLProcessRequest.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  09/22/13 22:31:33
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:   (), 
 *        Company:  NDSL
 *
 * =====================================================================================
 */
#ifndef CLPROCESSREQUEST_H
#define CLPROCESSREQUEST_H

#include "../include/headfile.h"
#include "../include/SLRequest.h"
#include "../include/CLCommunication.h"

class CLCommunication;
class CLProcessRequest
{
    public:
        explicit CLProcessRequest();
        virtual ~CLProcessRequest();
        //void setRequest(SLRequest request);
        virtual void work(SLRequest *request);
        virtual struct iovec getResult();
        void setCommunication(CLCommunication *communication);

    protected:
        SLRequest m_request;
        CLCommunication *m_communication;
};

#endif

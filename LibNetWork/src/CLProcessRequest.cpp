/*
 * =====================================================================================
 *
 *       Filename:  CLProcessRequest.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  09/22/13 22:30:17
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:   (), 
 *        Company:  NDSL
 *
 * =====================================================================================
 */
#include "../include/CLProcessRequest.h"

CLProcessRequest::CLProcessRequest()
{
}

CLProcessRequest::~CLProcessRequest()
{
}

void CLProcessRequest::setRequest(SLRequest request)
{
    m_request = request;
}

void CLProcessRequest::work()
{
}

struct iovec CLProcessRequest::getResult()
{
}

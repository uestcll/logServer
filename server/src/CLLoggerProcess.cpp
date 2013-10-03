/*
 * =====================================================================================
 *
 *       Filename:  CLLoggerProcess.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  09/29/2013 04:22:08 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lemon (zyl), lemon_wonder@163.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include "../include/CLLoggerProcess.h"
#include "../include/CLPraseManager.h"

CLLoggerProcess::CLLoggerProcess(CLPraseManager *manager) : m_manager(manager)
{
}

CLLoggerProcess::~CLLoggerProcess()
{
}

void CLLoggerProcess::work(SLRequest *request)
{
    m_iov.iov_base = NULL;
    m_iov.iov_len = 0;
    m_manager->process(request.readbuffer);
}

struct iovec CLLoggerProcess::getResult()
{
    return m_iov;
}

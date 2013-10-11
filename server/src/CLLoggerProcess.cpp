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

CLLoggerProcess::CLLoggerProcess()
{
    m_manager = CLPraseManager::getInstance();
}

CLLoggerProcess::~CLLoggerProcess()
{
}

void CLLoggerProcess::work(SLRequest *request)
{
    m_manager->process(request->readbuffer);
    getResult();
}

struct iovec CLLoggerProcess::getResult()
{
	string str;
    if(!m_store.empty())
    {
    	for(int i = 0; i < m_store.size(); ++i)
    	{
    		str += m_store[i];
    	}
    	int len = str.size();
    	char *buffer = new char[len + 1];
    	memcpy(buffer, str.c_str(), len);
    	buffer[len] = '\0';
    	m_iov.iov_base = buffer;
    	m_iov.len = len;

    	return m_iov;
    }

    m_iov.iov_base = NULL;
    m_iov.iov_len = 0;

    return m_iov;
}

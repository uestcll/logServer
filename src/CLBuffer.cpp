/*
 * =====================================================================================
 *
 *       Filename:  CLBuffer.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013/9/15 19:44:56
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lemon (lemon), lemon_wonder@163.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include "../include/CLBuffer.h"
#include "../include/CLSocket.h"

CLBuffer::CLBuffer() : m_readlength(0), m_lastchange(NULL)
{
}

CLBuffer::~CLBuffer()
{
	list<SLResponse>::iterator it = m_list.begin();
	while(it != m_list.end())
	{
		if((*it).finished)
		{
			delete [] (char*)(*it).io.iov_base;
			(*it).io.iov_base = NULL;
		}

		++it;
	}
	m_list.clear();
	if(NULL == m_lastchange)
	{
		delete [](char*)m_lastchange;
		m_lastchange = NULL;
	}
}

int CLBuffer::addToBuffer(SLResponse response)
{
	m_list.push_back(response);

	return SUCCESSFUL;
}

int CLBuffer::readBuffer(CLSocket *mysocket, SLRequest request)
{
	int len = sizeof(SLMessageHead);

	if(m_readlength < len && !m_request.finished)
	{
		int n = mysocket->readSocket((char*)&m_request.head + m_readlength, len - m_readlength);
	}
	else if(m_readlength == len && !m_request.finished)
	{
		m_request.finished = true;
		m_readlength = 0;
		m_request.len = m_request.head.length;
		if(0 != m_request.len)
		{
			m_request.readbuffer = new char[m_request.len];
		}
	}
	else
	{
		int n = mysocket->readSocket(m_request.readbuffer + m_readlength, m_request.len - m_readlength);
	}

	if(n < 0)
	{
		if(errno != EWOULDBLOCK && errno != EINTR)
		{
			processError();

			return FAILED;
		}
		else
		{
			return SUCCESSFUL;
		}
	}
	else
	{
		m_readlength += n;
		return SUCCESSFUL;
	}
}

int CLBuffer::writeBuffer(CLSocket *mysocket)
{
	int len = m_list.length();
	struct iovec *output;
	output = new struct iovec[len]; 
	for(int i = 0; i < len; ++i)
	{
		SLReponse tempReponse;
		tempReponse = m_list[i];
		output[i] = tempReponse.io;
	}

	int n = mysocket->writeSocket(output, len);
	if(n < 0)
	{
		if(errno != EWOULDBLOCK && errno != EINTR)
		{
			processError();
			return FAILED;
		}
	}

	int ret = n;
	list<SLReponse>::iterator aIt, pIt;
	aIt = m_list.begin();
	while(m_list.end() != aIt)
	{
		pIt = aIt++;
		if(n > (*pIt).io.iov_len)
		{
			n -= (*pIt).io.iov_len;
			if((*pIt).finished)
			{
				delete [] (char*)(*it).io.iov_base;
			    (*pIt).io.iov_base = NULL;
			}
			else
			{
				if(NULL != m_lastchange)
				{
					delete [] (char*)m_lastchange;
			        m_lastchange = NULL;
				}
			}
		    m_list.erase(pIt);
		}
		else
		{
			(*pIt).finished = false;
			m_lastchange = (*pIt).io.iov_base;
			(*pIt).io.iov_base = (void*)((char*)(*pIt).io.iov_base + n);
			(*pIt).io.iov_len -= n;
		}
	}

	delete[] output;
    return ret;
}

void CLBuffer::processError()
{
	delete m_pAgent;
}

void CLBuffer::setAgent(CLAgent *pAgent)
{
	m_pAgent = pAgent;
}


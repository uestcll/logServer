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
#include "../include/CLEpoll.h"
#include "../include/CLEpollEvent.h"
#include "../include/headfile.h"

CLBuffer::CLBuffer() : m_readlength(0), m_lastchange(NULL),m_pAgent(NULL), m_epollstate(EPOLLIN)
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

    if(EPOLLIN == m_epollstate)
    {
        CLEpollEvent myevent;
        myevent.setParameter(m_pAgent, m_pAgent->getFd(), EPOLL_CTL_MOD, EPOLLIN | EPOLLOUT);
        m_epollstate = EPOLLIN | EPOLLOUT;
        CLEpoll *epoll = CLEpoll::getInstance();
        epoll->workWithEpoll(&myevent);
        m_epollstate = EPOLLIN | EPOLLOUT;
    }

	return SUCCESSFUL;
}

int CLBuffer::readBuffer(CLSocket *mysocket)
{
	int len = sizeof(SLMessageHead);
    int n = 0;

	if(m_readlength < len && !m_request.finished)
	{
		n = mysocket->readSocket((char*)&m_request.head + m_readlength, len - m_readlength);
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
		n = mysocket->readSocket(m_request.readbuffer + m_readlength, m_request.len - m_readlength);
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
        if(m_request.finished && m_readlength == m_request.len)
        {
            m_readlength = 0;
        	m_queue.push(m_request);
            m_request.finished = false;
            m_request.len = 0;
            return FINISHED;
        }
		return SUCCESSFUL;
	}
}

int CLBuffer::writeBuffer(CLSocket *mysocket)
{
	int len = m_list.size();
    int cnt = 0;
	struct iovec *output;
	output = new struct iovec[len]; 
	list<SLResponse>::iterator aIt, pIt;
	for(aIt = m_list.begin(); aIt != m_list.end(); ++aIt)
	{
		SLResponse tempReponse;
		tempReponse = *aIt;
		output[cnt++] = tempReponse.io;
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
	aIt = m_list.begin();
	while(m_list.end() != aIt)
	{
		pIt = aIt++;
		if(n >= (*pIt).io.iov_len)
		{
			n -= (*pIt).io.iov_len;
			if((*pIt).finished)
			{
				delete [] (char*)(*pIt).io.iov_base;
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
            break;
		}
	}

    if(0 == m_list.size())
    {
        CLEpollEvent myevent;
        myevent.setParameter(m_pAgent, m_pAgent->getFd(), EPOLL_CTL_MOD, EPOLLIN);
        m_epollstate = EPOLLIN;
        CLEpoll *epoll = CLEpoll::getInstance();
        epoll->workWithEpoll(&myevent);
    }

	delete[] output;
    return ret;
}

void CLBuffer::processError()
{
	if(NULL == m_pAgent)
    {
        perror("m_pAgent is null");
        return;
    }

    m_pAgent->setState(false);
}

void CLBuffer::setCommunication(CLCommunication *pAgent)
{
	m_pAgent = pAgent;
}

void CLBuffer::getRequest(SLRequest* &request)
{
    if(!m_queue.empty())
    {
    	*request = m_queue.front();
    	m_queue.pop();
    }
    else
    {
    	request = NULL;
    }
}

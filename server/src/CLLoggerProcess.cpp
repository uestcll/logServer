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
#include "../include/CLSQL.h"

CLLoggerProcess::CLLoggerProcess()
{
    m_manager = CLPraseManager::getInstance();
}

CLLoggerProcess::~CLLoggerProcess()
{
}

void CLLoggerProcess::work(SLRequest *request)
{
    SLPraseResult result = m_manager->process(request->readbuffer);
    if(0 == result.type)
    {
        CLLogHead *pHead = result.pHead;
        string name = m_manager->getName(pHead->logType);
        string query;
        query = pHead->insertToSQL(name);
        query += pMessage->insertToSQL();
        CLSQL *pSQL = CLSQL::getInstance();
        pSQL->connectSQL("localhost", "root", "go", "log");
        pSQL->querySQL(query.c_str());
        pSQL->closeSQL();
    }
}

struct iovec CLLoggerProcess::getResult()
{
	/*
    string str;
    CLSQL *pSQL = CLSQL::getInstance();
    vector<string> store = pSQL->getResult();
    if(!store.empty())
    {
    	for(int i = 0; i < store.size(); ++i)
    	{
    		str += store[i];
    	}
    	int len = str.size();
        SLMessageHead head;
        head.length = len;
        char *buffer = new char[len + sizeof(SLMessageHead)];
        memcpy(buffer, &head, sizeof(SLMessageHead));
    	memcpy(buffer + sizeof(SLMessageHead), str.c_str(), len);
    	m_iov.iov_base = buffer;
    	m_iov.iov_len = len;

        pSQL->clearResult();
    	return m_iov;
    }

    m_iov.iov_base = NULL;
    m_iov.iov_len = 0;

    return m_iov;
    */
}

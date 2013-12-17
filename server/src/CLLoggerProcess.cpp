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
#include "../../Message/CLLogHead.h"
#include "../../Message/CLQueryLogHead.h"
#include "../../Message/CLQueryByLog.h"
#include "../../Message/CLQueryByTime.h"
#include "../../Message/CLQueryByIP.h"
#include "../../Message/CLMessage.h"
#include "../../Message/CLResponseLogHead.h"
#include <sstream>

CLLoggerProcess::CLLoggerProcess()
{
    m_manager = CLPraseManager::getInstance();
}

CLLoggerProcess::~CLLoggerProcess()
{
}

void CLLoggerProcess::work(SLRequest *request)
{
    SLPraseResult result = m_manager->praseProtocol(request->readbuffer);
    if(-1 == result.type)
    {
        return;
    }
    else if(0 == result.type)
    {
        handleInsert(result);
    }
    else 
    {
        handleQuery(result);
    }
}

void CLLoggerProcess::handleInsert(SLPraseResult result)
{
    CLLogHead *pHead = (CLLogHead*)result.pHead;
    CLMessage *pMessage = result.pMessage;
    string name = m_manager->getName(pHead->logType);
    string query;
    query = pHead->insertToSQL(name);
    query += pMessage->insertToSQL();
    CLSQL *pSQL = CLSQL::getInstance();
    pSQL->connectSQL();
    pSQL->querySQL(query.c_str());
    pSQL->closeSQL();
    delete pHead;
}

void CLLoggerProcess::handleQuery(SLPraseResult result)
{
    CLQueryLogHead *pHead = (CLQueryLogHead*)result.pHead;
    int logtype = pHead->logType;
    string name = m_manager->getName(logtype);
    if(500 == logtype)
    {
        handleQueryByLog(result, name);
    }
    else if(502 == logtype)
    {
        handleQueryByTime(result, name);
    }
    else
    {
        //handleQueryByIP(result, name);
    }

    delete pHead;
}

void CLLoggerProcess::handleQueryByLog(SLPraseResult result, string name)
{
    CLResponseLogHead responseHead;
    responseHead.logType = 501;
    responseHead.echoID = ((CLQueryLogHead*)result.pHead)->echoID;
    responseHead.numberOfResponse = ((CLQueryByLog*)(result.pMessage))->numberOfResponse;
    //responseHead.lengthOfLoad = responseHead.numberOfResponse *
    struct iovec temp;
    temp.iov_base  = responseHead.serialize();
    temp.iov_len = responseHead.getLength();
    m_iov.push_back(temp);
    CLQueryByLog *pMessage = (CLQueryByLog*)result.pMessage;
    int targetid = pMessage->typeOfLog;
    string targetname = m_manager->getName(targetid);
    string query;
    CLSQL *pSQL = CLSQL::getInstance();
    pSQL->connectSQL();
    for(int i = 0; i < pMessage->numberOfResponse; ++i)
    {
        stringstream ss;
        ss << "select * from " << targetname << " limit " << "1"
            << " offset " << pMessage->offsetOfResponse + i << ";";
        query = ss.str();
        if(pSQL->querySQL(query.c_str()))
        {
            break;
        }
        pSQL->getResult();
        CLMessage *tempMessage = m_manager->getMessage(targetid);
        CLLogHead head;
        int n = head.getResultFromSQL();
        temp.iov_base = head.serialize();
        temp.iov_len = head.getLength();
        m_iov.push_back(temp);
        tempMessage->getResultFromSQL(n);
        temp.iov_base = tempMessage->serialize();
        temp.iov_len = tempMessage->getLength();
        m_iov.push_back(temp);
    }
}

void CLLoggerProcess::handleQueryByTime(SLPraseResult result, string name)
{
    CLResponseLogHead responseHead;
    responseHead.logType = 503;
    responseHead.echoID = ((CLQueryLogHead*)result.pHead)->echoID;
    responseHead.numberOfResponse = ((CLQueryByTime*)result.pMessage)->numberOfResponse;
    struct iovec temp;
    temp.iov_base  = responseHead.serialize();
    temp.iov_len = responseHead.getLength();
    m_iov.push_back(temp);
    CLQueryByTime *pMessage = (CLQueryByTime*)result.pMessage;
    int targetid = pMessage->typeOfLog;
    string targetname = m_manager->getName(targetid);
    string query;
    CLSQL *pSQL = CLSQL::getInstance();
    pSQL->connectSQL();
    for(int i = 0; i < pMessage->numberOfResponse; ++i)
    {
        stringstream ss;
        ss << "select * from " << targetname << " limit " << "1"
           << " offset " << pMessage->offsetOfResponse << i << ";";
        query = ss.str();
        if(pSQL->querySQL(query.c_str()))
        {
            break;
        }
        pSQL->getResult();
        CLMessage *tempMessage = m_manager->getMessage(targetid);
        CLLogHead head;
        int n = head.getResultFromSQL();
        if(((head.eventOccurTimeSec > pMessage->startTimeSec)
           || (head.eventOccurTimeSec == pMessage->startTimeSec 
           &&head.eventOccurTimeUsec >= pMessage->startTimeUsec))
           &&((head.eventOccurTimeSec < pMessage->endTimeSec)
           || (head.eventOccurTimeSec == pMessage->endTimeSec 
           &&head.eventOccurTimeUsec <= pMessage->endTimeUsec)))
        {
            temp.iov_base = head.serialize();
            temp.iov_len = head.getLength();
            m_iov.push_back(temp);
            tempMessage->getResultFromSQL(n);
            temp.iov_base = tempMessage->serialize();
            temp.iov_len = tempMessage->getLength();
            m_iov.push_back(temp);
        }
        else
        {
            --i;
        }
    }
}

/*
void CLLoggerProcess::handleQueryByIP(SLPraseResult result, string name)
{
    CLResponseLogHead responseHead;
    responseHead.logType = 505;
    responseHead.echoID = (CLQueryLogHead*)result.pHead->echo;
    responseHead.numberOfResponse = (CLQueryByIP*)result.pMessage->numberOfResponse;
    struct iovec temp;
    temp.iov_base  = responseHead.serialize();
    temp.iov_len = responseHead.getLength();
    m_iov.push_back(temp);
    CLQueryByIP *pMessage = (CLQueryByIP*)result.pMessage;
    int targetid = pMessage->typeOfLog;
    string targetname = m_manager->getName(targetid);
    string query;
    CLSQL *pSQL = CLSQL::getInstance();
    pSQL->connectSQL();
    for(int i = 0; i < pMessage->numberOfResponse; ++i)
    {
        query = "selet * from " + targetname + " limit " + "1"
            + " offset " + pMessage->offsetOfResponse + i + ";";
        if(pSQL->querySQL(query.c_str()))
        {
            break;
        }
        pSQL->getResult();
        CLMessage *tempMessage = m_manager->getMessage(targetid);
        CLLogHead head;
        int n = head.getResultFromSQL();
        if((head.)
        {
            temp.iov_base = head.deserialize();
            temp.iov_len = head.getLength();
            m_iov.push_back(temp);
            tempMessage.getResultFromSQL(n);
            temp.iov_base = tempMessage.deserialize();
            temp.iov_len = tempMessage.getLength();
            m_iov.push_back(temp);
        }
        else
        {
            --i;
        }
    }
}
*/

vector<struct iovec> CLLoggerProcess::getResult()
{
    if(0 != m_iov.size())
    {
        int len = 0;
        vector<struct iovec>::iterator it = m_iov.begin();
        while(it != m_iov.end())
        {
            len += (*it).iov_len;
            it++;
        }
        char *buffer = new char[len];
        int cnt = 0;
        it = m_iov.begin();
        while(it != m_iov.end())
        {
            int temp = (*it).iov_len;
            memcpy(buffer + cnt, (*it).iov_base, temp);
            delete[] (char*)(*it).iov_base;
            cnt += temp;
            it++;
        }
        m_iov.clear();
        struct iovec buf;
        buf.iov_base = buffer;
        buf.iov_len = len;
        m_iov.push_back(buf);
    }
    return m_iov; 
}

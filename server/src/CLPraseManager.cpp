#include "../include/CLPraseManager.h"
#include "../include/CLSQL.h"
#include <cstring>
#include "../include/CLLogHead.h"
#include "../include/CLPraseManager.h"

CLPraseManager* CLPraseManager::m_manager = NULL;

CLPraseManager* CLPraseManager::getInstance()
{
    if(NULL == m_manager)
    {
        m_manager = new CLPraseManager();
    }

    return m_manager;
}
CLPraseManager::CLPraseManager()
{
}

CLPraseManager::~CLPraseManager()
{}

void CLPraseManager::registerHandle(CLMessage *pContent, int id, string name)
{
	m_map[id] = pContent;
    m_namemap[id] = name;
}

SLPraseResult CLPraseManager::praseProtocol(char *buffer)
{
	/*
    CLLogHead head;
    head.deserialize(buffer);

	CLMessage *pPrase = m_map[head.logType];
	pPrase->deserialize(buffer + head.getLength());
	pPrase->insertToSQL();
    */
    int type = *((int*)buffer);
    if(type <500)
    {
        CLLogHead *pHead = new CLLogHead;
        pHead->deserialize(buffer);
        CLMessage *pMessage = m_map[pHead->logType];
        pMessage->deserialize(buffer + head->getLength());
        SLPraseResult result;
        result.pHead = pHead;
        result.pMessage = pMessage;
        result.type = 0;

        return result;
    }

}

string CLPraseManager::getName(int id)
{
    return m_namemap[id];
}

#include "../include/CLPraseManager.h"
#include "../include/CLSQL.h"
#include <cstring>
#include "CLLogHead.h"

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
    initSQL();
}

CLPraseManager::~CLPraseManager()
{}

void CLPraseManager::registerHandle(int id, CLMessage *pContent)
{
	m_map[id] = pContent;
}

void CLPraseManager::process(char *buffer)
{
	CLLogHead head;
    head.deserialize(buffer);

	CLMessage *pPrase = m_map[head.logType];
	pPrase->deserialize(buffer + head.getLength());
	pPrase->insertToSQL();

	delete[] buffer;
}

void CLPraseManager::initSQL()
{
    CLSQL *pSQL = CLSQL::getInstance();
    pSQL->connectSQL("localhost", "root", "uestc8020", "log");
}

/*
 * =====================================================================================
 *
 *       Filename:  CLAgentManager.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013/9/17 23:13:02
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lemon (lemon), lemon_wonder@163.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include "../include/headfile.h"
#include "../include/CLAgentManager.h"
#include "../include/CLAgent.h"

CLAgentManager* CLAgentManager::m_manager = NULL;

CLAgentManager* CLAgentManager::getInstance()
{
    if(NULL == m_manager)
    {
        m_manager = new CLAgentManager();
    }

    return m_manager;
}

int CLAgentManager::insertAgent(int id, CLAgent *pAgent)
{
	pair<map<int, CLAgent*>::iterator, bool> ret;
	ret = m_map.insert(pair<int, CLAgent*>(id, pAgent));
	if(!ret.second)
	{
		perror("insert error");
		return FAILED;
	}

	return SUCCESSFUL;
}

int CLAgentManager::deleteAgent(int id)
{
	if(0 == m_map.erase(id))
	{
		perror("erase error");
		return FAILED;
	}

	return SUCCESSFUL;
}

int CLAgentManager::findAgent(int id, CLAgent **pAgent)
{
	map<int, CLAgent*>::iterator it;
	it = m_map.find(id);
	if(m_map.end() == it)
	{
		pAgent = NULL;
		return FAILED;
	}

	*pAgent = it->second;

	return SUCCESSFUL;
}

CLAgentManager::CLAgentManager()
{

}

CLAgentManager::~CLAgentManager()
{

}

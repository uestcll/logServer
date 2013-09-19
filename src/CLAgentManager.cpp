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

CLAgentManager::m_manager = NULL;

CLAgentManager* CLAgentManager::getInstance()
{
    if(NULL == m_manager)
    {
        m_manager = new CLAgentManager();
    }

    return m_manager;
}

int CLAgentManger::insertAgent(int id, CLAgent *pAgent)
{
	pair<map<int, CLAgent*>::iterator, bool> ret;
	ret = m_map.insert(pair<int, CLAgent*>(id, pAgent));
	if(!ret.second)
	{
		perror("insert error");
		return -1;
	}

	return 0;
}

int CLAgent::deleteAgent(int id)
{
	if(0 == m_map.erase(id))
	{
		perror("erase error");
		return -1;
	}

	return 0;
}

int CLAgentManager::findAgent(int id, CLAgent **pAgent)
{
	map<int, CLAgent*>::iterator it;
	it = find(ID);
	if(m_map.end() == it)
	{
		pAgent = NULL;
		return -1;
	}

	*pAgent = it->second;

	return 0;
}

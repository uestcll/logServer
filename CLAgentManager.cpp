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

CLAgent* CLAgentManager::createAgent(int type, int id)
{

}

int CLAgentManger::deleteAgent(int id)
{

}

int CLAgentManager::findAgent(int id)
{

}

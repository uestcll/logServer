/*
 * =====================================================================================
 *
 *       Filename:  CLAgentManager.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013/9/15 21:48:55
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lemon (lemon), lemon_wonder@163.com
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef CLAGENTMANAGER_H
#define CLAGENTMANAGER_H

#include <map>
class CLAgent;

class CLAgentManager
{
    public:
        static CLAgentManager* getInstance();
        template<typename Type> Type* createAgent(int id)
        {
            Type *agent = new Type(id);

            insertAgent(id, (CLAgent*)agent);
        }

        int insertAgent(int id, CLAgent *pAgent);
        int deleteAgent(int id);
        int findAgent(int id, CLAgent **pAgent);

    private:
        explicit CLAgentManager();
        ~CLAgentManager();
       
    private:
        CLAgentManager(const CLAgentManager&);
        CLAgentManager& operator=(const CLAgentManager&);

    private:
        static CLAgentManager *m_manager;
        map<int, CLAgent*> m_map;
};

#endif

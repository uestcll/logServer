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
#include <list>
#include "SLAddress.h"
#include "CLProcessRequest.h"

class CLAgent;

class CLAgentManager
{
    public:
        static CLAgentManager* getInstance();
        template<typename Type> Type* createAgent(const int fd = -1)
        {
            Type *agent = new Type(fd, m_process);
            m_list.push_back(agent);
        }

        int insertAgent(int id, CLAgent *pAgent);
        int deleteAgent(int id);
        int findAgent(int id, CLAgent **pAgent);
        void setProcessor(CLProcessRequest *process);

    private:
        explicit CLAgentManager();
        ~CLAgentManager();
       
    private:
        CLAgentManager(const CLAgentManager&);
        CLAgentManager& operator=(const CLAgentManager&);

    private:
        static CLAgentManager *m_manager;
        map<int, CLAgent*> m_map;
        list<CLAgent*> m_list;
        CLProcessRequest *m_process;
};

#endif

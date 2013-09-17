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

class CLAgentManager
{
    public:
        static CLAgentManager *getInstance();
        int createAgent(int type, int id);
        int deleteAgent(int id);
        int findAgent(int id);

    private:
        explicit CLAgentManager();
        ~CLAgentManager();
       
    private:
        CLBufferManager(const CLBufferManager&);
        CLBufferManager& operator=(const CLBufferManager&);

};

#endif

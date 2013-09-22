/*
 * =====================================================================================
 *
 *       Filename:  CLAgent.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013/9/13 10:46:12
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lemon (lemon), lemon_wonder@163.com
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef CLAGENT_H
#define CLAGENT_H

class CLSocket;
struct SLAddress;

class CLAgent
{
    public:
        explicit CLAgent(const int id, const SLAddress address);
        virtual ~CLAgent();
        virtual int recevData();
        virtual int sendData();
        int getID();
        int getFd();

    protected:
        CLSocket *m_socket;
        int m_id;
};

#endif

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
        explicit CLAgent(const int fd = -1);
        virtual ~CLAgent();
        void initAgent(const SLAddress address, const bool block);
        virtual int recevData();
        virtual int sendData();
        int getId();
        int getFd();
        void setId(const int id);

    protected:
        CLSocket *m_socket;
        int m_id;
};

#endif

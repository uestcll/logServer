/*
 * =====================================================================================
 *
 *       Filename:  CLClientProcess.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/07/2013 08:58:05 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lemon (zyl), lemon_wonder@163.com
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef CLCLIENTPROCESS_H
#define CLCLIENTPROCESS_H

#include "LibNetWork.h"
#include "CLLogHead.h"
#include "CLUserAccessDiskLog.h"
#include "CLModifyPasswordLog.h"
#include "CLQueryByLog.h"

class CLClientProcess : public CLProcessRequest
{
    public:
        virtual void work(SLRequest *request)
        {
            char len = request->len;
            char *buffer = new char[len + 1];
            memcpy(buffer, request->readbuffer, len);
            buffer[len] = '\0';
            cout << buffer << endl;
        }

        void init()
        {
            initUserAccessDiskLog();
            initModifyPasswordLog();
            initQueryLog();

        }

        void initUserAccessDiskLog()
        {
            CLLogHead head;
            CLUserAccessDiskLog userlog;
            head.logType = 1;
            head.lengthOfLoad = userlog.getLength();
            head.lengthOfRemark = 2;
            head.remark = new char[2];
            memcpy(head.remark, "M", 2);
            head.eventOccurTimeSec = head.eventOccurTimeUsec = 1;

            userlog.userID = userlog.departmentIDOfUser = userlog.diskID = userlog.position = userlog.range = 1;

            SLMessageHead myhead;
            int len = head.getLength() + userlog.getLength();
            myhead.length = len;
            len += sizeof(SLMessageHead);
            char *buffer = new char[len];
            memcpy(buffer, &myhead, sizeof(SLMessageHead));
            memcpy(buffer + sizeof(SLMessageHead), head.serialize(), head.getLength());
            memcpy(buffer + head.getLength() + sizeof(SLMessageHead), userlog.serialize(), userlog.getLength());
            struct iovec hello;
            hello.iov_base = buffer;
            hello.iov_len = len;
            m_communication->writeToServer(hello);
        }

        void initModifyPasswordLog()
        {
            CLLogHead head;
            CLModifyPasswordLog userlog;
            head.logType = 2;
            head.lengthOfLoad = userlog.getLength();
            head.lengthOfRemark = 2;
            head.remark = new char[2];
            memcpy(head.remark, "N", 2);
            head.eventOccurTimeSec = head.eventOccurTimeUsec = 1;

            userlog.administratorID = userlog.departmentID = 3;

            SLMessageHead myhead;
            int len = head.getLength() + userlog.getLength();
            myhead.length = len;
            len += sizeof(SLMessageHead);
            char *buffer = new char[len];
            memcpy(buffer, &myhead, sizeof(SLMessageHead));
            memcpy(buffer + sizeof(SLMessageHead), head.serialize(), head.getLength());
            memcpy(buffer + head.getLength() + sizeof(SLMessageHead), userlog.serialize(), userlog.getLength());
            struct iovec hello;
            hello.iov_base = buffer;
            hello.iov_len = len;
            m_communication->writeToServer(hello);
        }

        void initQueryLog()
        {
            CLLogHead head;
            CLQueryByLog query;
            head.logType = 3;
            head.lengthOfLoad = query.getLength();
            head.lengthOfRemark = 2;
            head.remark = new char[2];
            memcpy(head.remark, "Q", 2);
            head.eventOccurTimeSec = head.eventOccurTimeUsec = 1;

            query.typeOfLog = 2;
            query.numberOfResponse = 2;
            query.offsetOfResponse = 0;

            SLMessageHead myhead;
            int len = head.getLength() + query.getLength();
            myhead.length = len;
            len += sizeof(SLMessageHead);
            char *buffer = new char[len];
            memcpy(buffer, &myhead, sizeof(SLMessageHead));
            memcpy(buffer + sizeof(SLMessageHead), head.serialize(), head.getLength());
            memcpy(buffer + head.getLength() + sizeof(SLMessageHead), query.serialize(), query.getLength());
            struct iovec hello;
            hello.iov_base = buffer;
            hello.iov_len = len;
            m_communication->writeToServer(hello);
        }

        virtual vector<struct iovec> getResult()
        {

        }
};

#endif

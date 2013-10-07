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

class CLClientProcess : public CLProcessRequest
{
    public:
        virtual void work(SLRequest *request)
        {

        }

        char* init()
        {
            CLLogHead head;
            CLUserAccessDiskLog userlog;
            head.logType = 1;
            head.lengthOfLoad = userlog.getLength();
            head.lengthOfRemark = 2;
            head.remark = new char[2];
            memcpy(head.remark, "M", 2);
            head.eventOccurTimeSec = head.eventOccurTimeUsec;

            userlog.userID = userlog.departmentIDOfUser = userlog.diskID = userlog.position = userlog.range = 1;

            int len = head.getLength() + userlog.getLength();
            char *buffer = new char[len];
            memcpy(buffer, head.serialize(), head.getLength());
            memcpy(buffer + head.getLength(), userlog.serialize(), userlog.getLength());

        }

        virtual struct iovec getResult()
        {

        }
};

#endif

/*
 * =====================================================================================
 *
 *       Filename:  startup.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/06/2013 01:17:00 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lemon (zyl), lemon_wonder@163.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include "../include/CLLoggerProcess.h"
#include "../include/CLUserAccessDiskLog.h"
#include "../include/CLLogHead.h"

int main(int argc, char *argv[])
{
    CLLogHead head;
    CLUserAccessDiskLog *pLog = new CLUserAccessDiskLog();
    pLog->init(1);
    head.logType = 1;
    head.lengthOfLoad = 28;
    head.lengthOfRemark = 6;
    head.remark = new char[6];
    memcpy(head.remark, "hello", 6);
    head.eventOccurTimeSec = 2;
    head.eventOccurTimeUsec = 2;

    CLUserAccessDiskLog logger;
    logger.userID = 12;
    logger.departmentIDOfUser = 2;
    logger.diskID = 13;
    logger.position = 14;
    logger.range = 15;

    int len = head.getLength() + logger.getLength();
    char *buffer = new char[head.getLength() + logger.getLength()];
    char *temp = head.serialize();
    memcpy(buffer, temp, head.getLength());
    delete temp;
    temp = logger.serialize();
    memcpy((void*)(buffer + head.getLength()), temp, logger.getLength());
    delete temp;
    SLRequest request;
    request.head.length = len;
    request.readbuffer = buffer;
    request.len = len;

    CLLoggerProcess process;
    process.work(&request);

    return 0;
}

#ifndef CLRESPONSELOGHEAD_H
#define CLRESPONSELOGHEAD_H

#include "CLHead.h"

class CLResponseLogHead : public CLHead
{
public:
	explicit CLResponseLogHead()
    {
    }
	~CLResponseLogHead(){}

    char* serialize()
    {
    	int len = 16;
    	char *buffer = new char[len];
    	memcpy(buffer, &logType, 4);
    	memcpy(buffer + 4, &lengthOfLoad, 4);
    	memcpy(buffer + 8, &echoID, 4);
    	memcpy(buffer + 12, &numberOfResponse, 4);

    	return buffer;
    }

    void deserialize(char *buffer)
    {
    	memcpy(&logType, buffer, 4);
    	memcpy(&lengthOfLoad, buffer + 4, 4);
    	memcpy(&echoID, buffer + 8, 4);
    	memcpy(&numberOfResponse, buffer + 12, 4);
    }

    int getLength()
    {
        return 16;
    }

    void init(int type, int len, int echo, int num)
    {
        logType = type;
        lengthOfLoad = len;
        echoID = echo;
        numberOfResponse = num;
    }
    bool operator==(const CLResponseLogHead &Log) const
    {
        if(logType != Log.logType)
            return false;
        if(lengthOfLoad != Log.lengthOfLoad)
            return false;
        if(echoID != Log.echoID)
            return false;
        if(numberOfResponse != Log.numberOfResponse)
            return false;

        return true;
    }

public:
	int logType;
	int lengthOfLoad;
	int echoID;
	int numberOfResponse;
};

#endif

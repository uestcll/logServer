#ifndef CLRESPONSELOGHEAD_H
#define CLRESPONSELOGHEAD_H

#include <cstring>
#include <iostream>
using namespace std;

class CLResponseLogHead
{
public:
	explicit CLResponseLogHead();
	~CLResponseLogHead();

    char* serialize()
    {
    	int len = 12;
    	char *buffer = new char[len];
    	memcpy(buffer, &logType, 4);
    	memcpy(buffer + 4, &lengthOfLoad, 4);
    	memcpy(buffer + 8, &echoID, 4);
    	memcpy(buffer + 12, &numberOfRecord, 4);

    	return buffer;
    }

    void deserialize(char *buffer)
    {
    	memcpy(&logType, buffer, 4);
    	memcpy(&lengthOfLoad, buffer + 4, 4);
    	memcpy(&echoID, buffer + 8, 4);
    	memcpy(&numberOfRecord, buffer + 12, 4);
    }

    int getLength()
    {
        return 16;
    }

private:
	int logType;
	int lengthOfLoad;
	int echoID;
	int numberOfRecord;
};

#endif
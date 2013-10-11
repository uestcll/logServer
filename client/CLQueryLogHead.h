#ifndef CLQUERYLOGHEAD_H
#define CLQUERYLOGHEAD_H

#include <cstring>
#include <iostream>
using namespace std;

class CLQueryLogHead
{
public:
	explicit CLQueryLogHead(arguments);
	~CLQueryLogHead();

    char *serialize()
    {
    	int len = 12;
    	char *buffer = new char[len];
    	memcpy(buffer, &logType, 4);
    	memcpy(buffer + 4, &lengthOfLoad, 4);
    	memcpy(buffer + 8, &echoID, 4);

    	return buffer;
    }

    void deserialize(char *buffer)
    {
    	memcpy(&logType, buffer, 4);
    	memcpy(&lengthOfLoad, buffer + 4, 4);
    	memcpy(&echoID, buffer + 8, 4);
    }

    int getLength()
    {
    	return 12;
    }

private:
	int logType;
	int lengthOfLoad;
	int echoID;  
	
};

#endif
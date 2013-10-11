#ifndef CLOTHERTYPELOG_H
#define CLOTHERTYPELOG_H

#include <cstring>
#include <iostream>
using namespace std;

class CLOtherTypeLog
{
public:
	explicit CLOtherTypeLog();
	~CLOtherTypeLog();

    char* serialize()
    {
    	int len = lengthOfExplain + 4;
    	char *buffer = new char[len];
    	memcpy(buffer, &lengthOfExplain, 4);
    	memcpy(buffer + 4, explain, lengthOfExplain);

    	return buffer;
    }

    void deserialize(char *buffer)
    {
    	memcpy(&lengthOfExplain, buffer, 4);
    	explain = new char[lengthOfExplain];
    	memcpy(explain, buffer + 4, lengthOfExplain);
    }

    int getLength()
    {
        return 4 + lengthOfExplain;
    }   

private:
	int lengthOfExplain;
　　char *explain;

};

#endif
#ifndef CLQUERYLOGHEAD_H
#define CLQUERYLOGHEAD_H
#include "CLHead.h"

class CLQueryLogHead : public CLHead
{
public:
	explicit CLQueryLogHead(){}
	~CLQueryLogHead(){}

	/*
    void init(int id)
    {
        CLPraseManager *manager = CLPraseManager::getInstance();
        manager->registerHandle(id, this);

    }
    */

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
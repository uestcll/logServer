#ifndef CLQUERYBYLOG_H
#define CLQUERYBYLOG_H

#include "CLMessage.h"
#include "CLPraseManager.h"

class CLQueryByLog : public CLMessage
{
public:
    /*
    void init(int id)
    {
        CLPraseManager *manager = CLPraseManager::getInstance();
        manager->registerHandle(id, this);
    }
    */
	char* serialize()
	{
		char *buffer = new char[12];
		memcpy(buffer, &typeOfLog, 4);
		memcpy(buffer + 4, &numberOfResponse, 4);
		memcpy(buffer + 8, &offsetOfResponse, 4);

		return buffer;
	}

	void deserialize(char *buffer)
	{
		memcpy(&typeOfLog, buffer, 4);
		memcpy(&numberOfResponse, buffer + 4, 4);
		memcpy(&offsetOfResponse, buffer + 8, 4);
	}

	#ifdef SERVER
	void register(CLPraseManager *pManager)
	{
		pManager->registerHandle(this, 500, "CLQueryByLog");
	}
	#endif

public:
	int typeOfLog;
	int numberOfResponse;
	int offsetOfResponse; 
};

#endif

#ifndef CLQUERYBYTIME_H
#define CLQUERYBYTIME_H

#include "CLMessage.h"
#include "../server/include/CLPraseManager.h"
#include <cstring>

class CLQueryByTime : public CLMessage
{
public:
	char *serialize()
	{
		int len = getLength();
		char *buffer = new char[len];
		memcpy(buffer, &typeOfLog, 4);
		memcpy(buffer + 4, &startTimeSec, 8);
		memcpy(buffer + 12, &startTimeUsec, 8);
		memcpy(buffer + 20, &endTimeSec, 8);
		memcpy(buffer + 28, &endTimeUsec, 8);
		memcpy(buffer + 36, &numberOfResponse, 4);
		memcpy(buffer + 40, &offsetOfResponse, 4);

		return buffer;
	}

	void deserialize(char *buffer)
	{
		memcpy(&typeOfLog, buffer, 4);
		memcpy(&startTimeSec, buffer + 4, 8);
		memcpy(&startTimeUsec, buffer + 12, 8);
		memcpy(&endTimeSec, buffer + 20, 8);
		memcpy(&endTimeUsec, buffer + 28, 8);
		memcpy(&numberOfResponse, buffer + 36, 4);
		memcpy(&offsetOfResponse, buffer + 40, 4);
	}
	int getLength()
	{
		return 44;
	}

	#ifdef SERVER
	void registerIt(CLPraseManager *pManager)
	{
		pManager->registerHandle(this, 502, "CLQueryByTime");
	}
	#endif

public:
	int typeOfLog;
	long long startTimeSec;
	long long startTimeUsec;
	long long endTimeSec;
	long long endTimeUsec;
	int numberOfResponse;
	int offsetOfResponse;

};

#endif

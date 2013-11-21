#ifndef CLLOGHEAD_H
#define CLLOGHEAD_H

#include <cstring>
#include <cstdio>
#include <cstdlib>

class CLLogHead
{
public:
	explicit CLLogHead()
	{
	}
	~CLLogHead()
	{
	}
	char* serialize()
	{
		int len = 12 + lengthOfRemark + 16;
		char *buffer = new char[len];
		memcpy(buffer, &logType, 4);
		memcpy(buffer + 4, &lengthOfLoad, 4);
		memcpy(buffer + 8, &lengthOfRemark, 4);
		memcpy(buffer + 12, remark, lengthOfRemark);
		memcpy(buffer + 12 + lengthOfRemark, &eventOccurTimeSec, 8);
		memcpy(buffer + 20 + lengthOfRemark, &eventOccurTimeUsec, 8);
		return buffer;
	}

	void deserialize(char *buffer)
	{
		int len = 4;
		logType = *((int*)buffer);
		buffer += len;
		lengthOfLoad = *((int*)buffer);
		buffer += len;
		lengthOfRemark = *((int*)buffer);
		buffer += len;
		len = lengthOfRemark;
		remark = new char[len];
		memcpy(remark, buffer, len);
		buffer += len;
		len = 8;
		memcpy(&eventOccurTimeSec, buffer, len);
		buffer += len;
		memcpy(&eventOccurTimeUsec, buffer, len);
	}

	int getLength()
	{
		return 12 + lengthOfRemark + 16;
	}
public:
	int logType;
	int lengthOfLoad;
	int lengthOfRemark;
	char *remark;
	long long eventOccurTimeSec;
	long long eventOccurTimeUsec;
};

#endif
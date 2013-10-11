#ifndef CLQUERYBYLOG_H
#define CLQUERYBYLOG_H

#include <cstring>
#include <iostream>
using namespace std;

class CLQueryByLog
{
public:
	explicit CLQueryByLog();
	~CLQueryByLog();
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

private:
	int typeOfLog;
	int numberOfResponse;
	int offsetOfResponse; 
};

#endif
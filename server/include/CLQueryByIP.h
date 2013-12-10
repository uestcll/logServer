#ifndef CLQUERYBYIP_H
#define CLQUERYBYIP_H

#include "CLMessage.h"
#include <cstring>

class CLQueryByIP : public CLMessage
{
public:
	char *serialize()
	{
		int len = getLength();
		char *buffer = new char[len];
		memcpy(buffer, &typeOfLog, 4);
		memcpy(buffer + 4, &IPType, 4);
		memcpy(buffer + 8, &IPLength, 4);
		memcpy(buffer + 12, IPAdress, IPLength);
		memcpy(buffer + 12 + IPLength, &numberOfResponse, 4);
		memcpy(buffer + 16 + IPLength, &offsetOfResponse, 4);

		return buffer;
	}

	void deserialize(char *buffer)
	{
		memcpy(&typeOfLog, buffer, 4);
		memcpy(&IPType, buffer + 4, 4);
		memcpy(&IPLength, buffer + 8, 4);
		IPAdress = new char[IPLength + 1];
		memcpy(IPAdress, buffer + 12, IPLength);
		IPAdress[IPLength] = '\0';
		memcpy(&numberOfResponse, buffer + 12 + IPLength, 4);
		memcpy(&offsetOfResponse, buffer + 16 + IPLength, 4);
	}

	int getLength()
	{
		return 20 + IPLength;
	}
	#ifdef SERVER
	void register(CLPraseManager *pManager)
	{
		pManager->registerHandle(this, 504, "CLQueryByIP");
	}
	#endif
	
private:
	int typeOfLog;
	int IPType;
	int IPLength;
	char *IPAdress;
	int numberOfResponse;
	int offsetOfResponse;

};

#endif
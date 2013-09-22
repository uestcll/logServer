#ifndef SLREQUEST_H
#define SLREQUEST_H

#include "SLMessageHead.h"

struct SLRequest
{
	SLMessageHead head;
	char *readbuffer;
	int len;
	bool finished;

	SLRequest() : readbuffer(NULL),
	len(0), finished(false)
	{}
};
#endif
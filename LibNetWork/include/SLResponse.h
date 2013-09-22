#ifndef SLREPONSE_H
#define SLREPONSE_H

#include "headfile.h"

struct SLResponse
{
	struct iovec io;
	bool finished;
};

#endif

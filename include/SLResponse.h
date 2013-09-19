#ifndef SLREPONSE_H
#define SLREPONSE_H

#include "headfile.h"

struct SLReponse
{
	struct iovec io;
	bool mark;
};

#endif
#ifndef CLPRASEMESSAGEHEAD_H
#define CLPRASEMESSAGEHEAD_H

#include "SLMessageHead.h"

class CLPraseMessageHead
{
public:
	explicit CLPraseMessageHead();
	~CLPraseMessageHead();
	SLMessageHead getResut(char* &buffer);
};

#endif
#ifndef CLECHOCLIENT_H
#define CLECHOCLIENT_H

#include "LibNetWork.h"

class CLEchoClient : public CLProcessRequest
{
public:
	explicit CLEchoClient();
	~CLEchoClient();
	virtual void work(SLRequest *request);
	virtual struct iovec getResult();

private:
	struct iovec m_iovec;
};

#endif

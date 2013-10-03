#ifndef CLECHOSERVER_H
#define CLECHOSERVER_H

#include "LibNetWork.h"

class CLEchoServer : public CLProcessRequest
{
public:
	explicit CLEchoServer();
	~CLEchoServer();
	virtual void work(SLRequest *request);
	virtual struct iovec getResult();

private:
	struct iovec m_iovec;
};

#endif

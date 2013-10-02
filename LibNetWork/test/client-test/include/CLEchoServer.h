#ifndef CLECHOSERVER_H
#define CLECHOSERVER_H

class CLEchoServer : public CLProcessRequset
{
public:
	explicit CLEchoServer();
	~CLEchoServer();
	virtual void work(SLRequest *request);
	virtual struct iovec getResult();

private:
	struct iovec *m_iovec;
};

#endif
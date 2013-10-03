#include "../include/CLEchoServer.h"

CLEchoServer::CLEchoServer()
{}

CLEchoServer::~CLEchoServer()
{}

void CLEchoServer::work(SLRequest *request)
{
	int len = request->len;
	m_iovec.iov_base = new char[len];
	memset(m_iovec.iov_base, 0, len);
	m_iovec.iov_len = len;
	memcpy(m_iovec.iov_base, request->readbuffer, len);
}

struct iovec CLEchoServer::getResult()
{
	return m_iovec;
}


#include "../include/CLEchoServer.h"

CLEchoServer::CLEchoServer()
{}

CLEchoServer::~CLEchoServer()
{}

void CLEchoServer::work(SLRequest *request)
{
	int len = request->len;
	m_iovec.io_bases = new char[len];
	memset(m_iovec.io_bases, 0, len);
	m_iovec.io_len = len;
	memcpy(m_iovec.io_bases, request->readbuffer, len);
}

struct iovec CLEchoServer::getResult()
{
	return m_iovec;
}


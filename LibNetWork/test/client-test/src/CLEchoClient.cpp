#include "../include/CLEchoClient.h"

CLEchoClient::CLEchoClient()
{}

CLEchoClient::~CLEchoClient()
{}

void CLEchoClient::work(SLRequest *request)
{
	int len = request->len;
	m_iovec.iov_base = new char[len];
	memset(m_iovec.iov_base, 0, len);
	m_iovec.iov_len = len;
	memcpy(m_iovec.iov_base, request->readbuffer, len);
}

struct iovec CLEchoClient::getResult()
{
	return m_iovec;
}


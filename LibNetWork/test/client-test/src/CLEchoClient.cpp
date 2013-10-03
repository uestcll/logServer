#include "../include/CLEchoClient.h"

CLEchoClient::CLEchoClient()
{}

CLEchoClient::~CLEchoClient()
{}

void CLEchoClient::work(SLRequest *request)
{
    SLMessageHead head;
    head.length = request->len;
    head.cmd = 0;
    head.reserved = 0;
	int len = request->len + sizeof(SLMessageHead);
	m_iovec.iov_base = new char[len];
	memset(m_iovec.iov_base, 0, len);
	m_iovec.iov_len = len;
	memcpy(m_iovec.iov_base, &head, sizeof(SLMessageHead));
    memcpy((char*)m_iovec.iov_base + sizeof(SLMessageHead), request->readbuffer, request->len);
}

struct iovec CLEchoClient::getResult()
{
	return m_iovec;
}


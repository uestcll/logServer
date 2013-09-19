#include "../include/CLListenAgent.h"

CLListenAgent::CLListenAgent(SLAddress IPAddress) : CLAgent(IPAddress)
{
}

int CLListenAgent::recevData()
{
	int tempfd = m_socket->acceptSocket();

	return tempfd;
}
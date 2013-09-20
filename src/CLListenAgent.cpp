#include "../include/CLListenAgent.h"
#include "../include/CLSocket.h"

CLListenAgent::CLListenAgent(SLAddress IPAddress) : CLAgent(IPAddress)
{
}

CLListenAgent::~CLListenAgent()
{

}

int CLListenAgent::recevData()
{
	int tempfd = m_socket->acceptSocket();

	return tempfd;
}

int CLListenAgent::sendData()
{
    return SUCCESSFUL;
}

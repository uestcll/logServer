#include "../include/CLListenAgent.h"
#include "../include/CLSocket.h"

CLListenAgent::CLListenAgent(int id, SLAddress IPAddress) : CLAgent(id, IPAddress)
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

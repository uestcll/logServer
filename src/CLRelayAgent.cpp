#include "../include/CLRelayAgent.h"
#include "../include/CLSocket.h"
#include "../include/CLBuffer.h"

CLRelayAgent::CLRelayAgent(const SLAddress IPAddress) : CLAgent(IPAddress)
{}

CLRelayAgent::~CLRelayAgent()
{
}

int CLRelayAgent::recevData()
{
	return m_buffer.readBuffer(m_socket);
}

int CLRelayAgent::sendData()
{
	return m_buffer.writeBuffer(m_socket);
}

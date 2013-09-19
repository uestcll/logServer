#include "../include/CLRelayAgent.h"

CLRelayAgent::CLRelayAgent(const SLAddress IPAddress) : CLAgent(IPAddress)
{}

int CLRelayAgent::recevData()
{
	return m_buffer->read(m_socket);
}

int CLRelayAgent::sendData()
{
	return m_buffer->write(m_socket);
}
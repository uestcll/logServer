#ifndef CLRELAYAGENT_H
#define CLRELAYAGENT_H

class CLRelayAgent
{
public:
	explicit CLRelayAgent(const SLAddress IPAddress);
	~CLRelayAgent();

	int recevData();
	int sendData();

private:
	CLBuffer m_buffer;
};

#endif
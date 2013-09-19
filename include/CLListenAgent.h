#ifndef CLLISTENAGENT_H
#define CLLISTENAGENT_H

class CLListenAgent : public CLAgent
{
public:
	explicit CLListenAgent(SLAddress IPAdress);
	~CLListenAgent();
	int recevData();

private:
	struct sockaddr_in m_address;
};

#endif
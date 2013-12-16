#ifndef CLPRASEMANAGER_H
#define CLPRASEMANAGER_H

#include "../../Message/CLHead.h"
#include "../../Message/CLMessage.h"
#include <iostream>
#include <map>
#include <string>
using namespace std;

struct SLPraseResult
{
	CLHead *pHead;
	CLMessage *pMessage;
	int type;

	SLPraseResult() : pHead(NULL), pMessage(NULL), type(-1)
	{}
};

class CLPraseManager
{
public:
    static CLPraseManager* getInstance();
	void registerHandle(CLMessage *pContent, int id, string name);
	SLPraseResult praseProtocol(char *buffer);
	string getName(int id);
	CLMessage* getMessage(int id);

private:
    explicit CLPraseManager();
	~CLPraseManager();


private:
	map<int, CLMessage*> m_map;
	map<int, string> m_namemap;
    static CLPraseManager *m_manager;
};

#endif

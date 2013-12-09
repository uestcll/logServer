#ifndef CLPRASEMANAGER_H
#define CLPRASEMANAGER_H

#include "CLMessage.h"
#include <iostream>
#include <map>
#include <string>
using namespace std;

class CLPraseManager
{
public:
    static CLPraseManager* getInstance();
	void registerHandle(CLMessage *pContent, int id, string name);
	void process(char *buffer);

private:
    explicit CLPraseManager();
	~CLPraseManager();


private:
	map<int, CLMessage*> m_map;
	map<int, string> m_namemap;
    static CLPraseManager *m_manager;
};

#endif

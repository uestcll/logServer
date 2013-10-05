#ifndef CLPRASEMANAGER_H
#define CLPRASEMANAGER_H

#include "CLMessage.h"
#include <iostream>
#include <map>
using namespace std;

class CLPraseManager
{
public:
    static CLPraseManager* getInstance();
	void registerHandle(int id, CLMessage *pContent);
	void process(char *buffer);
    void initSQL();

private:
    explicit CLPraseManager();
	~CLPraseManager();


private:
	map<int, CLMessage*> m_map;
    static CLPraseManager *m_manager;
};

#endif

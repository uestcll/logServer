#ifndef CLOTHERTYPELOG_H
#define CLOTHERTYPELOG_H

#include "LibNetWork.h"
#include "CLMessage.h"
#include "CLPraseManager.h"
#include "CLSQL.h"

class CLOtherTypeLog : public CLMessage
{
public:
	explicit CLOtherTypeLog();
	~CLOtherTypeLog();

	void init(int id)
    {
        CLPraseManager *manager = CLPraseManager::getInstance();
        manager->registerHandle(id, this);

    }

    char* serialize()
    {
    	int len = lengthOfExplain + 4;
    	char *buffer = new char[len];
    	memcpy(buffer, &lengthOfExplain, 4);
    	memcpy(buffer + 4, explain, lengthOfExplain);

    	return buffer;
    }

    void deserialize(char *buffer)
    {
    	memcpy(&lengthOfExplain, buffer, 4);
    	explain = new char[lengthOfExplain];
    	memcpy(explain, buffer + 4, lengthOfExplain);
    }

    int getLength()
    {
        return 4 + lengthOfExplain;
    }
    virtual void insertToSQL()
    {
        CLSQL *pSQL = CLSQL::getInstance();
    pSQL->connectSQL("localhost", "root", "go", "log");
        char query[1000];
        memset(query, 0, sizeof(query));
        sprintf(query, "insert into test values(%d, %s);", lengthOfExplain, explain);
        pSQL->querySQL(query);
        pSQL->closeSQL();
    }

private:
	int lengthOfExplain;
　　char *explain;

};

#endif
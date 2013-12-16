#ifndef CLABNORMALANDERRNOLOG_H
#define CLABNORMALANDERRNOLOG_H

#include "CLSQL.h"
#include "CLMessage.h"
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>
#include <sstream>
using namespace std;

class CLAbnormalAndErrnoLog : public CLMessage
{
public:
    CLAbnormalAndErrnoLog() : lengthOfExplain(0), explain(NULL)
    {
    }
    ~CLAbnormalAndErrnoLog()
    {
        if(NULL != explain)
            delete[] explain;
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
	string insertToSQL()
	{
		/*
		CLSQL *pSQL = CLSQL::getInstance();
		pSQL->connectSQL("localhost", "root", "go", "log");
		char query[1000];
		memset(query, 0, sizeof(query));
		sprintf(query, "insert into test values(%d, %s);", lengthOfExplain, explain);
		pSQL->querySQL(query);
		pSQL->closeSQL();
		*/
		string query;
        stringstream ss;
		ss << lengthOfExplain << ", " << "\"" << explain << "\"" << ");";
        query = ss.str();
		return query;
	}
	void getResultFromSQL(int offset)
	{
		CLSQL *pSQL = CLSQL::getInstance();
		string temp = pSQL->m_store[offset + 0];
		lengthOfExplain = atoi(temp.c_str());
		explain = new char[lengthOfExplain + 1];
		temp = pSQL->m_store[offset + 1];
		memcpy(explain, temp.c_str(), lengthOfExplain);
		explain[lengthOfExplain] = '\0';
		//pSQL->closeSQL();
	}

	#ifdef SERVER
	void register(CLPraseManager *pManager)
	{
		pManager->registerHandle(this, 300, "CLAbnormalAndErrnoLog");
	}
	#endif

    void init(int len, char *ch)
    {
        lengthOfExplain = len;
        if(NULL != explain)
        {
            delete[] explain;
        }
        explain = new char[lengthOfExplain + 1];
        memcpy(explain, ch, lengthOfExplain);
        explain[lengthOfExplain] = '\0';
    }
    bool operator==(const CLAbnormalAndErrnoLog &logger) const
    {
        if(lengthOfExplain != logger.lengthOfExplain)
            return false;
        if(strcmp(explain, logger.explain) != 0)
            return false;

        return true;
    }

private:
	int lengthOfExplain;
	char *explain;

};

#endif

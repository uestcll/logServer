#ifndef CLOTHERTYPELOG_H
#define CLOTHERTYPELOG_H

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <iostream>
#include <sstream>
#include "CLMessage.h"
#ifdef SERVER
#include "../server/include/CLSQL.h"
#include "../server/include/CLPraseManager.h"
#endif

class CLOtherTypeLog : public CLMessage
{
public:
	CLOtherTypeLog() : lengthOfExplain(0), explain(NULL)
	{}
	~CLOtherTypeLog()
	{
		if(NULL != explain)
		{
			delete[] explain;
		}
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
	#ifdef SERVER
	string insertToSQL()
	{
		stringstream ss;
		string query;
		ss << lengthOfExplain << ", " << "\"" << explain << "\"" << ");";
		query = ss.str();
		return query;
	}
	void getResultFromSQL(int offset)
	{
		CLSQL *pSQL = CLSQL::getInstance();
		string temp = pSQL->m_store[offset + 0];
		lengthOfExplain = atoi(temp.c_str());
		temp = pSQL->m_store[offset + 1];
		explain = new char[lengthOfExplain + 1];
		memcpy(explain, temp.c_str(), lengthOfExplain);
		explain[lengthOfExplain] = '\0';
	}

	void registerIt(CLPraseManager *pManager)
	{
		pManager->registerHandle(this, 400, "CLOtherTypeLog");
	}
	#endif

	void init(int len, char *str)
	{
		lengthOfExplain = len;
		if(NULL != explain)
		{
			delete[] explain;
		}
		explain =  new char[len + 1];
		memcpy(explain, str, len);
		explain[len] = '\0';
	}
	bool operator==(const CLOtherTypeLog &Log) const
	{
		if(lengthOfExplain != Log.lengthOfExplain)
			return false;
		if(strcmp(explain, Log.explain) != 0)
			return false;

		return true;
	}
	
private:
	int lengthOfExplain;
	char *explain;

};

#endif

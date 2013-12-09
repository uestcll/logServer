#ifndef CLABNORMALANDERRNOLOG_H
#define CLABNORMALANDERRNOLOG_H

#include <cstdlib>
#include <cstdio>
#include <cstring>

class CLAbnormalAndErrnoLog : public CLMessage
{
public:
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
		query = lengthOfExplain + ", " + explain + ");";
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

private:
	int lengthOfExplain;
	char *explain;

};

#endif
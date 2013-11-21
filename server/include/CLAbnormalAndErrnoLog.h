#ifndef CLABNORMALANDERRNOLOG_H
#define CLABNORMALANDERRNOLOG_H

#include <cstdlib>
#include <cstdio>
#include <cstring>

class CLAbnormalAndErrnoLog
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
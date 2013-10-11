#ifndef CLQUERYBYLOG_H
#define CLQUERYBYLOG_H

#include "CLMessage.h"

class CLQueryByLog : public CLMessage
{
public:
	explicit CLQueryByLog();
	~CLQueryByLog();
	char* serialize()
	{
		char *buffer = new char[12];
		memcpy(buffer, &typeOfLog, 4);
		memcpy(buffer + 4, &numberOfResponse, 4);
		memcpy(buffer + 8, &offsetOfResponse, 4);

		return buffer;
	}

	void deserialize(char *buffer)
	{
		memcpy(&typeOfLog, buffer, 4);
		memcpy(&numberOfResponse, buffer + 4, 4);
		memcpy(&offsetOfResponse, buffer + 8, 4);
	}

	virtual void insertToSQL()
	{
		CLSQL *pSQL = CLSQL::getInstance();
    pSQL->connectSQL("localhost", "root", "go", "log");
        char query[1000];
        memset(query, 0, sizeof(query));
        sprintf(query, "select * from test limited 2 offset 0;");
        pSQL->querySQL(query);
        pSQL->closeSQL();
	}

private:
	int typeOfLog;
	int numberOfResponse;
	int offsetOfResponse; 
};

#endif
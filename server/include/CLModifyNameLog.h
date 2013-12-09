#ifndef CLMODIFYNAMELOG_H
#define CLMODIFYNAMELOG_H

#include <cstdio>
#include <cstdlib>
#include <cstring>

class CLModifyNameLog : public CLMessage
{
public:
	char *serialize()
	{
		int len = 20 + lengthOfNameBeforeModify + lengthOfNameAfterModify;
		char *buffer = new char[len];
		memcpy(buffer, &administrarorID, 4);
		memcpy(buffer + 4, &departmentID, 4);
		memcpy(buffer + 8, &lengthOfNameBeforeModify, 4);
		memcpy(buffer + 12, nameBeforeModify, lengthOfNameBeforeModify);
		memcpy(buffer + 12 + lengthOfNameBeforeModify, &lengthOfNameAfterModify, 4);
		memcpy(buffer + 16 + lengthOfNameBeforeModify, nameAfterModify, lengthOfNameAfterModify);
		
		return buffer;
	}
	void deserialize(char * buffer)
	{
		memcpy(&administrarorID, buffer, 4);
		memcpy(&departmentID, buffer + 4, 4);
		memcpy(&lengthOfNameBeforeModify, buffer + 8, 4);
		nameBeforeModify = new char[lengthOfNameBeforeModify + 1];
		memcpy(nameBeforeModify, buffer + 12, lengthOfNameBeforeModify);
		nameBeforeModify[lengthOfNameBeforeModify] = '\0';
		memcpy(&lengthOfNameAfterModify, buffer + 12 + lengthOfNameBeforeModify, 4);
		nameAfterModify = new char[lengthOfNameAfterModify + 1];
		memcpy(nameAfterModify, buffer + 16 + lengthOfNameBeforeModify, lengthOfNameAfterModify);
	}

	string insertToSQL()
	{
		/*
		CLSQL *pSQL = CLSQL::getInstance();
		pSQL->connectSQL("localhost", "root", "go", "log");
		char query[1000];
		memset(query, 0, sizeof(query));
		sprintf(query, "insert into test values(%d, %d, %s, %s);", 
			administratorID, departmentID, nameBeforeModify,
			nameAfterModify);
		pSQL->querySQL(query);
		pSQL->closeSQL();
		*/
		string query;
		query = administratorID + ", " + departmentID + ", " + nameBeforeModify
				+ ", " + nameAfterModify + ");";
		return query;
	}
	void getResultFromSQL(int offset)
	{
		CLSQL *pSQL = CLSQL::getInstance();
		//pSQL->connectSQL("localhost", "root", "go", "log");
		//pSQL->fetchResult();
		string temp = pSQL->m_store[offset + 0];
		administrarorID = atoi(temp.c_str());
		temp = pSQL->m_store[offset + 1];
		departmentID = atoi(temp.c_str());
		temp = pSQL->m_store[offset + 2];
		departmentIDOfNameModify = atoi(temp.c_str());
		temp = pSQL->m_store[offset + 3];
		lengthOfNameBeforeModify = temp.size();
		nameBeforeModify = new char[lengthOfNameBeforeModify + 1];
		memcpy(nameBeforeModify, temp.c_str(), lengthOfNameBeforeModify);
		nameBeforeModify[lengthOfNameBeforeModify] = '\0';
		temp = pSQL->m_store[offset + 4];
		lengthOfNameAfterModify = temp.size();
		nameAfterModify = new char[lengthOfNameAfterModify + 1];
		memcpy(nameAfterModify, temp.c_str(), lengthOfNameAfterModify);
		nameAfterModify[lengthOfNameAfterModify] = '\0';
		//pSQL->closeSQL();
	}
	int getLength()
	{
		return 16 + lengthOfNameBeforeModify + lengthOfNameAfterModify;
	}
private:
	int administrarorID;
	int departmentID;
	int lengthOfNameBeforeModify;   
	char *nameBeforeModify;
	int lengthOfNameAfterModify;
	char *nameAfterModify;
};
#endif
#ifndef CLADMINISTRATORLOGINLOG_H
#define CLADMINISTRATORLOGINLOG_H

#include <cstdio>
#include <cstdlib>
#include <cstring>

class CLAdministratorLoginLog : public CLMessage
{
public:
	char *serialize()
	{
		int len = 16 + IPLength;
		char *buffer = new char[len];
		memcpy(buffer, &administratorID, 4);
		memcpy(buffer + 4, &departmentID, 4);
		memcpy(buffer + 8, &IPType, 4);
		memcpy(buffer + 12, &IPLength, 4);
		memcpy(buffer + 16, &loginIPAdress, IPLength);

		return buffer;
	}
	void deserialize(char *buffer)
	{
		memcpy(&administratorID, buffer, 4);
		memcpy(&departmentID, buffer + 4, 4);
		memcpy(&IPType, buffer + 8, 4);
		memcpy(&IPLength, buffer + 12, 4);
		loginIPAdress = new char[IPLength + 1];
		memcpy(loginIPAdress, buffer + 16, IPLength);
		loginIPAdress[IPLength] = '\0';
	}
	string insertToSQL()
	{
		/*
		CLSQL *pSQL = CLSQL::getInstance();
		pSQL->connectSQL("localhost", "root", "go", "log");
		char query[1000];
		memset(query, 0, sizeof(query));
		sprintf(query, "insert into test values(%d, %d, %d, %s);", 
			administratorID, departmentID, IPType, loginIPAdress);
		pSQL->querySQL(query);
		pSQL->closeSQL();
		*/
		string query;
		query = administratorID + ", " + departmentID + ", "
			    + IPType + ", " + loginIPAdress + ");";
		return query;
	}

	void getResultFromSQL(int offset)
	{
		CLSQL *pSQL = CLSQL::getInstance();
		//pSQL->connectSQL("localhost", "root", "go", "log");
		//pSQL->fetchResult();
		string temp = pSQL->m_store[offset + 0];
		administratorID = atoi(temp.c_str());
		temp = pSQL->m_store[offset + 1];
		departmentID = atoi(temp.c_str());
		temp = pSQL->m_store[offset + 2];
		IPType = atoi(temp.c_str());
		temp = pSQL->m_store[offset + 3];
		IPLength = temp.size();
		loginIPAdress = new char[IPLength + 1];
		memcpy(loginIPAdress, temp.c_str(), IPLength);
		loginIPAdress[IPLength] = '\0';
		//pSQL->closeSQL();
	}

	#ifdef SERVER
	void register(CLPraseManager *pManager)
	{
		pManager->registerHandle(this, 110, "CLAdministratorLoginLog");
		pManager->registerHandle(this, 111, "CLAdministratorLoginLog");
	}
	#endif

private:
	int administratorID;
	int departmentID;
	int IPType;
	int IPLength;
    char *loginIPAdress;
};
#endif
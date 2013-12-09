#ifndef CLSUBORDINATEADMINSTRATORLOG_H
#define CLSUBORDINATEADMINSTRATORLOG_H

#include <cstdio>
#include <cstdlib>
#include <cstring>

class CLSubordinateAdministratorLog : public CLMessage
{
public:
	char* serialize()
	{
		char *buffer = new char[16];
		memcpy(buffer, &administratorID, 4);
		memcpy(buffer + 4, &departmentID, 4);
		memcpy(buffer + 8, &subordinateAdministrator, 4);
		memcpy(buffer + 12, &subordinateDepartmentID, 4);

		return buffer;
	}

	void deserialize(char *buffer)
	{
		memcpy(&administratorID, buffer, 4);
		memcpy(&departmentID, buffer + 4, 4);
		memcpy(&subordinateAdministrator, buffer + 8, 4);
		memcpy(&subordinateDepartmentID, buffer + 12, 4);
	}

	int getLength()
	{
		return 16;
	}
	string insertToSQL()
	{
		/*
		CLSQL *pSQL = CLSQL::getInstance();
		pSQL->connectSQL("localhost", "root", "go", "log");
		char query[1000];
		memset(query, 0, sizeof(query));
		sprintf(query, "insert into test values(%d, %d, %d, %d);", 
			    administratorID, departmentID, subordinateAdministrator,
				subordinateDepartmentID);
		pSQL->querySQL(query);
		pSQL->closeSQL();
		*/
		string query;
		query = administratorID + ", " + departmentID + ", " + subordinateAdministrator
				+ ", " + subordinateDepartmentID + ");";
		return query;
	}
	void getResultFromSQL(int offset)
	{
		CLSQL *pSQL = CLSQL::getInstance();
		//pSQL->connectSQL("localhost", "root", "go", "log");
		//pSQL->fetchResult();
		string temp = pSQL->m_store[offset + 0];
		administratorID = atoi(temp.c_str());
		string temp = pSQL->m_store[offset + 1];
		departmentID = atoi(temp.c_str());
		string temp = pSQL->m_store[offset + 2];
		subordinateDepartmentID = atoi(temp.c_str());
		string temp = pSQL->m_store[offset + 3];
		subordinateDepartmentID = atoi(temp.c_str());
		//pSQL->closeSQL();
	}

	#ifdef SERVER
	void register(CLPraseManager *pManager)
	{
		pManager->registerHandle(this, 100, "CLSubordinateAdministratorLog");
		pManager->registerHandle(this, 101, "CLSubordinateAdministratorLog");
	}
	#endif
	
private:
	int administratorID;
	int departmentID;
	int subordinateAdministrator;
    int subordinateDepartmentID;
};

#endif
#ifndef CLADMINISTRATORAUTHORITYMANAGERLOG_H
#define CLADMINISTRATORAUTHORITYMANAGERLOG_H

#include <cstdio>
#include <cstdlib>
#include <cstring>

class CLAdministraotrAuthorityManagerLog : public CLMessage
{
public:
	char *serialize()
	{
		int len = 16;
		char *buffer = new char[16];
		memcpy(buffer, &administratorID, 4);
		memcpy(buffer + 4, &departmentID, 4);
		memcpy(buffer + 8, &subordinateDepartmentID, 4);
		memcpy(buffer + 12, &subordinateAdministratorID, 4);

		return buffer;
	}

	void deserialize(char *buffer)
	{
		memcpy(&administratorID, buffer, 4);
		memcpy(&departmentID, buffer + 4, 4);
		memcpy(&subordinateDepartmentID, buffer + 8, 4);
		memcpy(&subordinateAdministratorID, buffer + 12, 4);
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
		string query = administratorID + ", " + departmentID + ", "
					   + subordinateAdministrator + ", " + subordinateDepartmentID + ");";
		return query; 
	}
	int getLength()
	{
		return 16;
	}

	void getResultFromSQL(int offset)
	{
		CLSQL *pSQL = CLSQL::getInstance();
		string temp = pSQL->m_store[offset + 0];
		administratorID = atoi(temp.c_str());
		temp = pSQL->m_store[offset + 1];
		departmentID = atoi(temp.c_str());
		temp = pSQL->m_store[offset + 2];
		subordinateDepartmentID = atoi(temp.c_str());
		temp = pSQL->m_store[offset + 3];
		subordinateAdministratorID = atoi(temp.c_str());
		//pSQL->closeSQL();
	}

private:
	int administratorID;
	int departmentID;
	int subordinateDepartmentID;
	int subordinateAdministratorID;
};
#endif
#include "../include/CLPraseUserAccessDiskLog.h"
#include "../include/CLSQL.h"

CLPraseUserAccessDiskLog::CLPraseUserAccessDiskLog()
{}

CLPraseUserAccessDiskLog::~CLPraseUserAccessDiskLog()
{}

void CLPraseUserAccessDiskLog::praseLog(char *buffer)
{
	int len  = 4;
	m_disklog.userID = *((int*)buffer);
	buffer += len;
	m_disklog.departmentIDOfUser = *((int*)buffer);
	buffer += len;
	m_disklog.diskID = *((int*)buffer);
	len = 8;
	memcpy(&m_disklog.position, buffer, len);
	buffer += len;
	memcpy(&m_disklog.range, buffer, len);
}

void CLPraseUserAccessDiskLog::insertToSQL()
{
    string query;
    INSERT INTO children(fname, age) VALUES('ann', 3)"); 
    query = "insert into userAccessDiskLog valuse (" + 
   m_disklog.userID + "," + m_disklog.departmentIDOfUser +"," + m_disklog.diskID  +"," + m_disklog.position  +"," + m_disklog.range + ");";
     CLSQL *pSQL = CLSQL::getInstance();
     pSQL->querySQL(query.c_str());
}

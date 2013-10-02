#include "../include/CLPraseUserAccessDiskLog.h"

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
	
}
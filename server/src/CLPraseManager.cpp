#include "../include/CLPraseManager.h"

CLPraseManager::CLPraseManager()
{}

CLPraseManager::~CLPraseManager()
{}

void CLPraseManager::register(int id, CLPraseContent *pContent)
{
	m_map[id] = pContent;
}

int CLPraseManager::praseHead(char *buffer, SLLogHead &head)
{
	int len = 4;
	int totallen = 0;
	SLLogHead head;
	head.logType = *((int*)buffer);
	buffer += len;
	head.lengthOfLoad = *((int*)buffer);
	buffer += len;
	head.lengthOfRemark = *((int*)buffer);
	buffer += len;
	len = head.lengthOfRemark;
	head.remark = new char[len];
	memcpy(head.remark, buffer, len);
	buffer += len;
	len = 8;
	memcpy(head.eventOccurTimeSec, buffer, len);
	buffer += len;
	memcpy(head.eventOccurTimeUsec, buffer, len);

	totallen = 4 + 4 + 4 + head.lengthOfRemark + 8 + 8;
	return totallen;
}

void CLPraseManager::praseContent(int id, char *buffer)
{
	CLPraseContent *pPrase = m_map[id];
	pPrase->praseLog(buffer);
}

void CLPraseManager::process(char *buffer)
{
	SLLogHead head;
	int len = praseHead(buffer, head);

	CLPraseContent *pPrase = m_map[head.logType];
	pPrase->praseLog(buffer + len);
	pPrase->insertToSQL();

	delete[] buffer;
}

#include "../include/CLLogProcessor.h"

CLLogProcessor::CLLogProcessor()
{}

CLLogProcessor::~CLLogProcessor()
{
}

void CLLogProcessor::work()
{
	if(0 == m_request.head.cmd)
	{
		//SQL插入语句
	}
	else if(1 == m_request)
	{
		//SQL查询语句
	}
}

struct iovec CLLogProcessor::getResult()
{
}
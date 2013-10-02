#ifndef CLPRASEMANAGER_H
#define CLPRASEMANAGER_H

struct SLLogHead
{
	uint32_t logType;                       
　　uint32_t lengthOfLoad;                  
　　uint32_t lengthOfRemark;               
　　uint32_t *remark;       
　　uint64_t eventOccurTimeSec;     
　　uint64_t eventOccurTimeUsec;
};

class CLPraseManager
{
public:
	explicit CLPraseManager();
	~CLPraseManager();
	void register(int id, CLPraseContent *pContent);
	int praseHead(char* buffer, SLLogHead &head);
	void praseContent(int id, char *buffer);
	void process(char *buffer);

private:
	map<int, CLPraseContent*> m_map;
};

#endif
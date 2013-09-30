#ifndef SLMESSAGEHEAD_H
#define SLMESSAGEHEAD_H

struct SLLogHead
{
	uint32_t logType;                       
　　uint32_t lengthOfLoad;                  
　　uint32_t lengthOfRemark;               
　　uint32_t *remark;       
　　uint64_t eventOccurTimeSec;     
　　uint64_t eventOccurTimeUsec;
};

#endif
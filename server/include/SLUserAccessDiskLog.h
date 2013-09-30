#ifndef SLUSERACCESSDISKLOG_H
#define SLUSERACCESSDISKLOG_H

struct SLUserAccessDiskLog
{	uint32_t userID;
　　uint32_t departmentIDOfUser;
　　uint32_t diskID;
　　uint64_t position; 
　　uint64_t range;             
};

#endif
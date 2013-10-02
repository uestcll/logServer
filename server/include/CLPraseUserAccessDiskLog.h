#ifndef CLPRASEUSERACCESSDISKLOG_H
#define CLPRASEUSERACCESSDISKLOG_H

struct SLUserAccessDiskLog
{	uint32_t userID;
　　uint32_t departmentIDOfUser;
　　uint32_t diskID;
　　uint64_t position; 
　　uint64_t range;             
};

class CLPraseUserAccessDiskLog : public CLPraseContent
{
public:
	explicit CLPraseUserAccessDiskLog();
	~CLPraseUserAccessDiskLog();
	virtual void praseLog(char *buffer);
	virtual void insertToSQL();

private:
	SLUserAccessDiskLog m_disklog;
};

#endif
#ifndef CLHEAD_H
#define CLHEAD_H

class CLHead
{
public:
	explicit CLHead()
	{}
	virtual ~CLHead()
	{}
	virtual char* serialize(){}
	virtual void deserialize(char *buffer){}
	virtual int getLength(){}
};

#endif
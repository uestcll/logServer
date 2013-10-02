#ifndef CLPRASECONTENT_H
#define CLPRASECONTENT_H

class CLPraseContent
{
public:
	explicit CLPraseContent();
	virtual ~CLPraseContent();
	virutal void praseLog(char *buffer);
	virutal void insertToSQL();
};

#endif
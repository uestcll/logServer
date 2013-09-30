#ifndef CLPRASECONTENT_H
#define CLPRASECONTENT_H

<typename T>
class CLPraseContent
{
public:
	explicit CLPraseContent();
	~CLPraseContent();
	T getResult(char *buffer);
};

#endif
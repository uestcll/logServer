#ifndef CLLOGPROCESSOR_H
#define CLLOGPROCESSOR_H

class CLLogProcessor : public CLProcessRequest
{
	public:
		explicit CLProcessor();
		~CLProcessor();
		void work();
		struct iovec getResult();


};

#endif
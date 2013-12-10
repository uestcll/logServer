#ifndef CLLOGGERPROCESS_H
#define CLLOGGERPROCESS_H

#include "LibNetWork.h"

class CLPraseManager;

class CLLoggerProcess : public CLProcessRequest
{
    public:
        explicit CLLoggerProcess();
        ~CLLoggerProcess();
        virtual void work(SLRequest *request);
        virtual struct iovec getResult();

    private:
        void handleInsert(SLPraseResult result);

    private:
    	CLPraseManager *m_manager;
        struct iovec m_iov;
};

#endif

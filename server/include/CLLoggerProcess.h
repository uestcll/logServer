#ifndef CLLOGGERPROCESS_H
#define CLLOGGERPROCESS_H

class CLPraseManager;

class CLLoggerProcess : public CLProcessRequest
{
    public:
        explicit CLLoggerProcess(CLPraseManager *manager);
        ~CLLoggerProcess();
        virtual void work(SLRequest *request);
        virtual struct iovec getResult();

    private:
    	CLPraseManager *m_manager;
        struct iovec m_iov;
};

#endif

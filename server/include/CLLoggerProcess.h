#ifndef CLLOGGERPROCESS_H
#define CLLOGGERPROCESS_H

class CLLoggerProcess : public CLProcessRequest
{
    public:
        explicit CLLoggerProcess();
        ~CLLoggerProcess();
        virtual void work(SLRequest *request);
        virtual struct iovec getResult();
};

#endif

#ifndef CLLOGGERPROCESS_H
#define CLLOGGERPROCESS_H

#include <string>
#include <vector>

class CLPraseManager;

class CLLoggerProcess : public CLProcessRequest
{
    public:
        explicit CLLoggerProcess();
        ~CLLoggerProcess();
        virtual void work(SLRequest *request);
        virtual vector<struct iovec> getResult();
        void setParameter(string hostname, string name, string password, string databasename);

    private:
        void handleInsert(SLPraseResult result);
        void handleQuery(SLPraseResult result);
        void handleQueryByLog(SLPraseResult result, string name);
        void handleQueryByTime(SLPraseResult result, string name);
        void handleQueryByIP(SLPraseResult result, string name);

    private:
    	CLPraseManager *m_manager;
        vecotr<struct iovec> m_iov;
};

#endif

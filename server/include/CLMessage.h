#ifndef CLMESSAGE_H
#define CLMESSAGE_H

#include <string>

class CLMessage
{
    public:
        explicit CLMessage(){}
        virtual ~CLMessage(){}
        virtual char* serialize(){}
        virtual void deserialize(char *buffer){}
        virtual string insertToSQL(){}
        virtual void getResultFromSQL(int offset){}
};

#endif

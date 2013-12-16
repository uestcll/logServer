#ifndef CLMESSAGE_H
#define CLMESSAGE_H

#include <string>
#include <iostream>
using namespace std;

class CLMessage
{
    public:
        explicit CLMessage(){}
        virtual ~CLMessage(){}
        virtual char* serialize(){}
        virtual void deserialize(char *buffer){}
        virtual int getLength(){}
        virtual string insertToSQL(){}
        virtual void getResultFromSQL(int offset){}
};

#endif

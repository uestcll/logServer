#ifndef CLMESSAGE_H
#define CLMESSAGE_H

class CLMessage
{
    public:
        explicit CLMessage(){}
        virtual ~CLMessage(){}
        virtual char* serialize(){}
        virtual void deserialize(char *buffer){}
        virtual void insertToSQL(){}
};

#endif

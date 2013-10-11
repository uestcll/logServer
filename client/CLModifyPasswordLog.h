#ifndef CLMODIFYPASSWORDLOG_H
#define CLMODIFYPASSWORDLOG_H
#include <cstring>
#include <iostream>
using namespace std;

class CLModifyPasswordLog
{
    public:
        char* serialize()
        {
            char *buffer = new char[8];
            memcpy(buffer, &administratorID, 4);
            memcpy(buffer + 4, &departmentID, 4);
            return buffer;
        }

        void deserialize(char *buffer)
        {
            administratorID = *((int*)buffer);
            departmentID = *((int*)(buffer + 4));
        }

        int getLength()
        {
            return 8;
        }

    public:
        int administratorID;
        int departmentID;
};

#endif

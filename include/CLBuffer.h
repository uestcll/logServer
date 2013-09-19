/*
 * =====================================================================================
 *
 *       Filename:  CLBuffer.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013/9/15 19:34:57
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lemon (lemon), lemon_wonder@163.com
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef CLBUFFER_H
#define CLBUFFER_H

class CLBuffer
{
    public:
        int addToBuffer();
        int readBuffer();
        int writeBuffer();

    private:
        explicit CLBuffer();
        ~CLBuffer();

    private:
        CLBuffer(CLBuffer&);
        CLBuffer& operator=(CLBuffer&);

    private:
        list<iovec> m_list;
};

#endif

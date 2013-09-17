/*
 * =====================================================================================
 *
 *       Filename:  CLBufferManager.h
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

#ifndef CLBUFFERMANAGER_H
#define CLBUFFERMANAGER_H

class CLBufferManager
{
    public:
        CLBufferManager *getInstance();
        int addToBuffer();
        int readBuffer();
        int writeBuffer();

    private:
        explicit CLBufferManager();
        ~CLBufferManager();

    private:
        CLBufferManager(CLBufferManager&);
        CLBufferManager& operator=(CLBufferManager&);

    private:
        static CLBufferManager *m_bufferManager;
};

#endif

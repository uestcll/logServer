/*
 * =====================================================================================
 *
 *       Filename:  CLBuffer.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013/9/15 19:44:56
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lemon (lemon), lemon_wonder@163.com
 *   Organization:  
 *
 * =====================================================================================
 */

CLBuffer::m_buffer = NULL;

CLBuffer* CLBuffer::getInstance()
{
    if(NULL == m_bufferManager)
    {
         m_bufferManager = new CLBuffer;
    }

    return m_bufferManager;
}

int CLBuffer::addToBuffer()
{

}

int CLBuffer::readBuffer()
{

}

int CLBuffer::writeBuffer()
{

}



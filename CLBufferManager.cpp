/*
 * =====================================================================================
 *
 *       Filename:  CLBufferManager.cpp
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

CLBufferManager::m_bufferManager = NULL;

CLBufferManager* CLBufferManager::getInstance()
{
    if(NULL == m_bufferManager)
    {
         m_bufferManager = new CLBufferManager;
    }

    return m_bufferManager;
}

int CLBufferManager::addToBuffer()
{

}

int CLBufferManager::readBuffer()
{

}

int CLBufferManager::writeBuffer()
{

}



/*
 * =====================================================================================
 *
 *       Filename:  msghead.h
 *
 *    Description: 
 *
 *        Version:  1.0
 *        Created:  2013/9/15 18:59:01
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lemon (lemon), lemon_wonder@163.com
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef SLMESSAGEHEAD_H
#define SLMESSAGEHEAD_H

struct CLMessageHead
{
    uint32_t headLength;
    uint32_t cmd;
    uint32_t reserved;
};

#endif

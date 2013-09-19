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

struct SLMessageHead

{
    uint32_t length;
    uint32_t cmd;
    uint32_t reserved;

    CLMessageHead() :
    length(0),
    cmd(0),
    reserved(0)
    {}
};

#endif

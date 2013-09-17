/*
 * =====================================================================================
 *
 *       Filename:  headfile.h
 *
 *    Description:  ]
 *
 *        Version:  1.0
 *        Created:  2013/9/12 23:19:15
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lemon (lemon), lemon_wonder@163.com
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef HEADFILE_H
#define HEADFILE_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
using namespace std;

const int SUCCESSFUL = 0;
const int FAILED = -1;
const int BEFORECONNECTTED = -1;
const int AFTERCONNECTTED = 0;

#endif

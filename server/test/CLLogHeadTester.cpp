/*
 * =====================================================================================
 *
 *       Filename:  CLLogHead.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  12/11/13 17:11:13
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:   (), 
 *        Company:  NDSL UESTC
 *
 * =====================================================================================
 */
#include <gtest/gtest.h>
#include "../include/CLLogHead.h"

TEST(CLLogHead, serializeAnddeserialize)
{
    CLLogHead myHead;
    char *buffer = myHead.serialize();
    EXPECT_EQ(-1, *((int*)buffer));
    delete buffer; 
}

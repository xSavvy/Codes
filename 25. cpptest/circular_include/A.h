/*
 * @Author: Liu Weilong
 * @Date: 2021-01-24 17:27:28
 * @LastEditors: Liu Weilong 
 * @LastEditTime: 2021-01-24 17:28:29
 * @FilePath: /3rd-test-learning/25. cpptest/circular_include/A.h
 * @Description: 
 */
#include "B.h"

class A
{
    public:
    B* bp;

    int content;
};
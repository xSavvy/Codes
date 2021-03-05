/*
 * @Author: Liu Weilong
 * @Date: 2021-01-24 17:27:28
 * @LastEditors: Liu Weilong 
 * @LastEditTime: 2021-03-05 10:26:25
 * @FilePath: /3rd-test-learning/25. cpptest/circular_include/A.h
 * @Description: 
 * 
 * 
 * 
 * 
 * 
 */
#include <iostream>

using namespace std;

class B;

class A
{
    public:
    // B bp; 无法通过编译
    B* bp;//可以通过编译 

    void getB(B& b)
    {
        // cout<< b.content<<endl;
        if(bp!=nullptr)
        {
            // delete bp;
            // bp = new B(b);
            bp = &b;
            bp->content;
        }else{
            // bp = new B(b);
            bp = &b;
        }
    }

    int content;
};

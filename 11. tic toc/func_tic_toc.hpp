/*
 * @Author: Liu Weilong
 * @Date: 2020-09-23 16:19:04
 * @LastEditors: Liu Weilong 
 * @LastEditTime: 2020-09-23 16:37:12
 * @FilePath: /3rd-test-learning/11. tic toc/func_tic_toc.hpp
 * @Description: 函数当中进行使用的计时器
 */

#include <chrono>
#include <iostream>
#include <string>
class FuncTic
{
    public:
    using __tp = std::chrono::_V2::system_clock::time_point;
    enum OutputForm
    {
        
    };
    explicit FuncTic(const std::string funcName):funcName_(funcName){
        start = std::chrono::high_resolution_clock::now();
    }

    __tp check(){return std::chrono::high_resolution_clock::now();}
    
    
    ~FuncTic()
    {
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> diff = end - start;

    }

    
    __tp start;
    const std::string funcName_;      
};
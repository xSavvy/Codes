/*
 * @Author: Liu Weilong
 * @Date: 2020-09-23 16:19:04
 * @LastEditors: Liu Weilong 
 * @LastEditTime: 2020-09-24 09:49:21
 * @FilePath: /3rd-test-learning/11. tic toc/tic_toc.hpp
 * @Description: 函数当中进行使用的计时器
 */


#include <chrono>
#include <iostream>
#include <string>
#include <utility>

#define nanos(diff) std::chrono::duration_cast<std::chrono::nanoseconds>(diff)
#define micros(diff) std::chrono::duration_cast<std::chrono::microseconds>(diff)
#define millis(diff) std::chrono::duration_cast<std::chrono::milliseconds>(diff)


class Tic
{
    public:
    using __tp = std::chrono::_V2::system_clock::time_point;
    using __tpp = std::pair<__tp,int64_t>;


    explicit Tic(const std::string funcName):funcName_(funcName){
        start = std::chrono::high_resolution_clock::now();
    }

    __tp check(){return std::chrono::high_resolution_clock::now();}

    auto checkprint_nano()
    {
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> diff_1 = end - start;
        std::cout<<"=============== until now "<<funcName_<<" have used ============="
        <<std::endl<<" "<<
        nanos(diff_1).count()<<" nanoseconds"<<std::endl;
        return nanos(diff_1).count();
    }

    auto checkprint_micro(){
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> diff_1 = end - start;
        std::cout<<"=============== until now "<<funcName_<<" have used ============="
        <<std::endl<<" "<<
        micros(diff_1).count()<<" microseconds"<<std::endl;
        return micros(diff_1).count();
    }

    auto checkprint_milli()
    {
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> diff_1 = end - start;
        std::cout<<"=============== until now "<<funcName_<<" have used ============="
        <<std::endl<<" "<<
        millis(diff_1).count()<<" milliseconds"<<std::endl;
        return millis(diff_1).count();
    }

    
    
    ~Tic()
    {
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> diff = end - start;
        std::cout<<"=============== "<<funcName_<<" totally used ============="
        <<std::endl<<" "<<
        nanos(diff).count()<<" nanoseconds "<<" == "<<micros(diff).count()<<" macroseconds "<<
        " == "<<millis(diff).count()<<" milliseconds "<<std::endl;
    }

    
    __tp start;
    const std::string funcName_;      
};
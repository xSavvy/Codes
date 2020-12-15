/*
 * @Author: Liu Weilong
 * @Date: 2020-12-15 13:53:38
 * @LastEditors: Liu Weilong 
 * @LastEditTime: 2020-12-15 13:57:00
 * @FilePath: /3rd-test-learning/11. utils/tictoc/tic_toc.cpp
 * @Description: 
 */
#include "tic_toc.hpp"
TicToc::TicToc(const std::string funcName):funcName_(funcName){
        start = std::chrono::high_resolution_clock::now();
    }

void TicToc::Tic()
    {
        start = std::chrono::high_resolution_clock::now();
    }

int64_t TicToc::Toc()
{
    int64_t duration = checkprint_milli();
    if(average_want)
    {
        average_sum+=duration;
        count++;
    }
    return duration;
}

int64_t TicToc::checkprint_nano()
{
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff_1 = end - start;
    std::cout<<"=============== until now "<<funcName_<<" have used ============="
    <<std::endl<<" "<<
    nanos(diff_1).count()<<" nanoseconds"<<std::endl;
    return nanos(diff_1).count();
}
int64_t TicToc::checkprint_micro(){
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff_1 = end - start;
    std::cout<<"=============== until now "<<funcName_<<" have used ============="
    <<std::endl<<" "<<
    micros(diff_1).count()<<" microseconds"<<std::endl;
    return micros(diff_1).count();
}
int64_t TicToc::checkprint_milli()
{
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff_1 = end - start;
    std::cout<<"=============== until now "<<funcName_<<" have used ============="
    <<std::endl<<" "<<
    millis(diff_1).count()<<" milliseconds"<<std::endl;
    return millis(diff_1).count();
}
TicToc::~TicToc()
{
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;
    std::cout<<"=============== "<<funcName_<<" totally used ============="
    <<std::endl<<" "<<
    nanos(diff).count()<<" nanoseconds "<<" == "<<micros(diff).count()<<" macroseconds "<<
    " == "<<millis(diff).count()<<" milliseconds "<<std::endl;
}
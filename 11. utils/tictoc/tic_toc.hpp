/*
 * @Author: Liu Weilong
 * @Date: 2020-09-23 16:19:04
 * @LastEditors: Liu Weilong 
 * @LastEditTime: 2020-12-15 13:57:14
 * @FilePath: /3rd-test-learning/11. utils/tictoc/tic_toc.hpp
 * @Description: 函数当中进行使用的计时器
 */


#include <chrono>
#include <iostream>
#include <string>
#include <utility>

#define nanos(diff) std::chrono::duration_cast<std::chrono::nanoseconds>(diff)
#define micros(diff) std::chrono::duration_cast<std::chrono::microseconds>(diff)
#define millis(diff) std::chrono::duration_cast<std::chrono::milliseconds>(diff)


class TicToc
{
    public:
    using __tp = std::chrono::_V2::system_clock::time_point;
    using __tpp = std::pair<__tp,int64_t>;


    explicit TicToc(const std::string funcName);

    void Tic();

    int64_t Toc();

    int64_t checkprint_nano();

    int64_t checkprint_micro();

    int64_t checkprint_milli();  
    ~TicToc();
    __tp start;
    bool average_want = false;
    int64_t average_sum = 0;
    unsigned int count = 0;
    const std::string funcName_;      
};
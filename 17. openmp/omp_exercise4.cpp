/*
 * @Author: Liu Weilong
 * @Date: 2020-10-22 17:09:50
 * @LastEditors: Liu Weilong 
 * @LastEditTime: 2020-10-22 18:10:26
 * @FilePath: /3rd-test-learning/17. openmp/omp_exercise4.cpp
 * @Description:  用于学习如何使用OMP 进行 worksharing 而不是SPMD(Single Program Multiple Data)
 *         
 *                API 使用 
 *                #pragma omp parallel for
 *                #pragma omp for
 *                #pragma omp parallel for reduction(+:var) 
 */
#include "omp.h"
#include <iostream>
#include <cmath>
#include <chrono>


const unsigned int step_num = 1000;
double A[step_num];
double result =0;
void integratePi_parallel_for()
{  
    omp_set_num_threads(4);
    result =0;

    // omp parallel for + atomic
    auto start = std::chrono::steady_clock::now();
    #pragma omp parallel
    {      
        #pragma omp for
        for(int i = 0;i < step_num;i++)
        {
            auto tmp = (4/(1+A[i]*A[i]) * 1/step_num); 
            #pragma omp atomic   // 没有这个的话 就很容易出问题
            result = tmp+result;
        }

    }
    auto diff = std::chrono::steady_clock::now() - start;

    std::cout<<" the comsumed time is " 
            << std::chrono::duration_cast<std::chrono::microseconds>(diff).count()
            <<"milliseconds"<<std::endl;

    // omp parallel for reduction （+ - ×） 计算操作比 atomic 进一步缩小
    // 经过测试 下面这个 reduction 比上面的方法还是要快很多
    start = std::chrono::steady_clock::now();
    #pragma omp parallel for reduction(+:result)
    for(int i =0;i<step_num;i++)
    {
        result += (4/(1+A[i]*A[i]) * 1/step_num);
    }
    diff = std::chrono::steady_clock::now() - start;
    
    std::cout<<" the comsumed time is " 
        << std::chrono::duration_cast<std::chrono::microseconds>(diff).count()
        <<"milliseconds"<<std::endl;

    double pi = result;
    std::cout<<"pi is "<<pi <<std::endl;
}

int main()
{
    for(int i =0;i<1000;i++)
    {
        A[i] = 1.0/1000.0 *float(i+1); // 一定要注意 整数 计算的截断 问题
    }
    
    integratePi_parallel_for();
}


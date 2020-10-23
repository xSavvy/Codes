/*
 * @Author: Liu Weilong
 * @Date: 2020-10-23 14:00:20
 * @LastEditors: Liu Weilong 
 * @LastEditTime: 2020-10-23 14:06:14
 * @FilePath: /3rd-test-learning/17. openmp/omp_exercise4_for_detail.cpp
 * @Description: omp parallel 常见错误
 *               1. 使用 omp parallel  worksharing 打印for 结果整个for 被打印了四次
 *               2. 使用 在 omp parallel 内部 omp parallel for ：想要打印四次结果 只打印了一次 
 *               3. 使用 omp parallel 想要并行之后所有的代码，结果只并行了一个for
 */

#include "omp.h"
#include <iostream>
using namespace std;

// 第一种错误
void printMistake_for_omp_parallel()
{
    cout<<"here is printMistake_for_omp_parallel"<<endl;

}

/*
 * @Author: Liu Weilong
 * @Date: 2021-01-21 17:41:14
 * @LastEditors: Liu Weilong 
 * @LastEditTime: 2021-01-31 13:40:43
 * @FilePath: /3rd-test-learning/30. supplement_material/plucker_line/code/plucker_test.cpp
 * @Description: 
 * 
 *              Plucker 代码验证
 *              1. 四个点进行代码验证
 *              2. 
 * 
 * 
 * 
 */

#include "plucker.h"

int main()
{
    
    Eigen::Matrix<double,6,1> plucker;
    GeneratorPlucker(plane_1,plane_2,plucker);

    return 0;
}
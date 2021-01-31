/*
 * @Author: Liu Weilong
 * @Date: 2021-01-21 17:41:14
 * @LastEditors: Liu Weilong 
 * @LastEditTime: 2021-01-21 18:27:40
 * @FilePath: /3rd-test-learning/30. geometry/line/plucker_test.cpp
 * @Description: 
 */

#include "plucker.h"

int main()
{
    Eigen::Vector4d plane_1,plane_2;
    bool ok1 = GeneratePlane(Eigen::Vector3d(1.0,2.0,3.0),
                             Eigen::Vector3d(2.0,5.0,-1.0),
                             Eigen::Vector3d(-1.0,6.0,4.0),
                             plane_1);
    bool ok2 = GeneratePlane(Eigen::Vector3d(5.0,9.0,-1.0),
                             Eigen::Vector3d(10.0,11.0,-1.0),
                             Eigen::Vector3d(3.0,8.0,2.0),
                             plane_2);
    Eigen::Matrix<double,6,1> plucker;
    GeneratorPlucker(plane_1,plane_2,plucker);

    return 0;
}
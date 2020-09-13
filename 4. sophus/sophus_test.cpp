/*
 * @Author: Liu Weilong 
 * @Date: 2020-09-02 10:03:08 
 * @Last Modified by: Liu Weilong
 * @Last Modified time: 2020-09-02 10:39:41
 */

#include <iostream>

#include "Eigen/Eigen"
#include "sophus/geometry.hpp"
#include "sophus/so3.hpp"

using namespace Eigen;
using namespace Sophus;
using namespace std;

int main()
{
    float initAngle = 0.3;

    // 从 Vector3f 生成 旋转矩阵 Matrix3f
    // 此处的重点是SO3 后要显式地 实例化<foat >
    auto initRot = SO3<float>::exp(Vector3f(0,0,initAngle)).matrix();
    cout<<initRot<<endl;

    return 0;
}
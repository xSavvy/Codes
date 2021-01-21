/*
 * @Author: Liu Weilong
 * @Date: 2021-01-21 17:41:03
 * @LastEditors: Liu Weilong 
 * @LastEditTime: 2021-01-21 18:14:33
 * @FilePath: /3rd-test-learning/30. geometry/line/plucker.h
 * @Description: 
 */
#include <iostream>

#include "Eigen/Eigen"
#include "sophus/so3.hpp"

#include "pangolin/pangolin.h"

using namespace std;

bool GeneratePlane(Eigen::Vector3d point_1,
                   Eigen::Vector3d point_2,
                   Eigen::Vector3d point_3,
                   Eigen::Vector4d & plane_params)
{
    auto vec_12 = point_2-point_1;
    auto vec_13 = point_3-point_1;

    auto n = vec_12.cross(vec_13);

    if(n.norm()<1e-7)
    {return false;}

    double w = n.dot(point_1);
    plane_params<<n,w;
    return true;
}

bool GeneratorPlucker(Eigen::Vector4d plane_1,
                      Eigen::Vector4d plane_2,
                      Eigen::Matrix<double,6,1> & plucker)
{
    Eigen::Matrix4d L = plane_1*plane_2.transpose() -plane_2*plane_1.transpose();   
    Eigen::Matrix3d dx = L.block<3,3>(0,0);
    Eigen::Vector3d n = L.block<3,1>(0,3);
    
    auto d = Sophus::SO3d::vee(dx);
    
    plucker<<d,n;
    
    return true;
}
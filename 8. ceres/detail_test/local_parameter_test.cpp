/*
 * @Author: Liu Weilong
 * @Date: 2020-10-26 07:16:54
 * @LastEditors: Liu Weilong
 * @LastEditTime: 2020-10-26 08:01:04
 * @Description: 主要是为了测试和学习LocalParameter 
 * 
 *               ie.1   Auto Diff SE3 上的优化
 *               ie.2   Analystic Diff SE3 上的优化
 */

#include <vector>
#include <iostream>
#include <random>

#include <ceres/ceres.h>
#include <sophus/se3.hpp>
#include <Eigen/Eigen>

using namespace std;

std::vector<Eigen::Vector3d> point_cloud;

void buildPointCloud()
{
    for(int i = 0;i<30;i++)
    {
        Eigen::Vector3d tmp_point;
        tmp_point<< i * 0.3,i*0.3,i*0.3;
        point_cloud.push_back(tmp_point);
    }

    for(int i = 0;i<30;i++)
    {
        Eigen::Vector3d tmp_point;
        tmp_point<< 0.5,i*0.3 + i* 0.02,i*0.3;
        point_cloud.push_back(tmp_point);
    }
    
    for(int i = 0;i<30;i++)
    {
        Eigen::Vector3d tmp_point;
        tmp_point<< 0.9,i*0.3 + i* 0.04,i*0.3 - i*0.01;
        point_cloud.push_back(tmp_point);
    }    
}

bool transformPointCloud(const Sophus::SE3d & pose_camera_to_world, 
                         const vector<Eigen::Vector3d> & raw_point_array,
                         vector<Eigen::Vector3d> & transformed_point_array)
{
    if(raw_point_array.size() == 0)
    {
        std::cout<<"[Bad Data]: the size of point array is 0.Thus return false!"<<std::endl;
        return false;
    }
    
    Eigen::Matrix4d pose_world_to_camera = pose_camera_to_world.matrix().inverse();
    transformed_point_array.clear();
    transformed_point_array.reserve(raw_point_array.size());

    for(const auto & point:raw_point_array)
    {
        Eigen::Vector3d tmp_point = pose_world_to_camera * point;
        transformed_point_array.push_back(tmp_point);
    }
}

// 这里使用高斯分布的误差
bool AddNoise(std::vector<Eigen::Vector3d> & point_cloud)
{
    
}


class AutoDiffCostFunctor
{
    public:
    AutoDiffCostFunctor(const Sophus::SE3d value):value_(value){}
    template <typename T>
    bool operator()(const T* var, T * residual)const
    {
        value_
        return true;
    }

    Sophus::SE3d value_;
};

int main()
{
    
}
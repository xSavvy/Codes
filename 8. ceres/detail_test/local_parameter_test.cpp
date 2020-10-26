/*
 * @Author: Liu Weilong
 * @Date: 2020-10-26 07:16:54
 * @LastEditors: Liu Weilong 
 * @LastEditTime: 2020-10-26 16:05:47
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
#include <g2o/stuff/sampler.h>

using namespace std;

std::vector<Eigen::Vector4d> point_cloud;

void buildPointCloud()
{
    for(int i = 0;i<30;i++)
    {
        Eigen::Vector4d tmp_point;
        tmp_point<< i * 0.3,i*0.3,i*0.3,1;
        point_cloud.push_back(tmp_point);
    }

    for(int i = 0;i<30;i++)
    {
        Eigen::Vector4d tmp_point;
        tmp_point<< 0.5,i*0.3 + i* 0.02,i*0.3,1;
        point_cloud.push_back(tmp_point);
    }
    
    for(int i = 0;i<30;i++)
    {
        Eigen::Vector4d tmp_point;
        tmp_point<< 0.9,i*0.3 + i* 0.04,i*0.3 - i*0.01,1;
        point_cloud.push_back(tmp_point);
    }    
}

bool transformPointCloud(const Sophus::SE3d & pose_camera_to_world, 
                         const vector<Eigen::Vector4d> & points_in_world,
                         vector<Eigen::Vector4d> & points_in_camera)
{
    if(points_in_world.size() == 0)
    {
        std::cout<<"[Bad Data]: the size of point array is 0.Thus return false!"<<std::endl;
        return false;
    }
    
    Eigen::Matrix4d pose_world_to_camera = pose_camera_to_world.matrix().inverse();
    points_in_camera.clear();
    points_in_camera.reserve(points_in_world.size());

    for(const auto & point:points_in_world)
    {
        Eigen::Vector4d tmp_point = pose_world_to_camera * point;
        points_in_camera.push_back(tmp_point);
    }
}

// 这里使用高斯分布的误差(0,1) 高斯分布
// TODO 这里的参数可以进行调节，如果出问题可以注意这里
bool AddNoise(std::vector<Eigen::Vector4d> & point_cloud)
{
    Eigen::Matrix3d covar = Eigen::Matrix3d::Identity();
    g2o::GaussianSampler<Eigen::Matrix<double,3,1>,Eigen::Matrix<double,3,3>> sampler;
    sampler.setDistribution(covar);
    for(auto & point :point_cloud)
    {
        Eigen::Vector4d noise;
        noise<<sampler.generateSample(),0;
        point = point + noise;
    }
}


class AnalyticCostFunction:public ceres::SizedCostFunction<3,6>
{
    public:
    AnalyticCostFunction(const Eigen::Vector3d watched_point, const Eigen::Vector3d point_in_world):
                         watched_point_(watched_point),point_in_world_(point_in_world){}

    virtual bool Evaluate(double const * const * params,
                          double * residuals,
                          double **jacobians)const
    {
        Eigen::Map<Eigen::Matrix<double,3,1>> residual_map(residuals);
        Eigen::Map<const Sophus::SE3<double>> se3_map(params[0]);

        residual_map = se3_map*watched_point_ -point_in_world_;

        if (!jacobians) return true;
        double* jacobian = jacobians[0];
        if (!jacobian) return true;
        
        // 这里不使用Sophus 的SE3 求导
        // 因为Sophus的SE3 是四元数 + 位姿的一个组合

        
        
    }

    Eigen::Vector3d watched_point_;
    Eigen::Vector3d point_in_world_;
};



int main()
{
    
}
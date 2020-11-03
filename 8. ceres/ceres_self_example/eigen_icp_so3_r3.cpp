/*
 * @Author: Liu Weilong
 * @Date: 2020-11-03 07:19:03
 * @LastEditors: Liu Weilong
 * @LastEditTime: 2020-11-03 08:12:40
 * @Description:  基于Eigen 实现的ICP 算法 据说是又快又好
 */
#include <vector>
#include <iostream>
#include <random>

#include <sophus/se3.hpp>
#include <sophus/so3.hpp>
#include <Eigen/Eigen>
#include <g2o/stuff/sampler.h>
#include <pcl/kdtree/kdtree_flann.h>

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
    // scale 再大基本就挂了  因为点在设置的时候就比较密集
    double scale = 0.001;
    Eigen::Matrix3d covar = Eigen::Matrix3d::Identity()*scale;
    g2o::GaussianSampler<Eigen::Matrix<double,3,1>,Eigen::Matrix<double,3,3>> sampler;
    sampler.setDistribution(covar);
    for(auto & point :point_cloud)
    {
        Eigen::Vector4d noise;
        noise<<sampler.generateSample(),0;
        // cout<<"the noise is "<<noise.transpose()<<endl;
        point = point + noise;
    }
}

template <typename T>
void ToPclPointType(const std::vector<Eigen::Vector4d> & point_array, 
                    pcl::PointCloud<T> & point_cloud)
{
    CHECK_NE(point_array.size(),0);
    point_cloud.clear();
    for(auto & point:point_array)
    {
        T tmp_point(point(0),point(1),point(2));
        point_cloud.push_back(tmp_point);
    }
}

int main()
{
    buildPointCloud();

    // ================================ 生成变化 ================================
    double transform_lie [6] {0.2,0.5,0.6,0.7,0.7,0.8};
    Eigen::Map<Eigen::Matrix<double,6,1>> lie_map(transform_lie);
    Sophus::SE3d transform_se3 = Sophus::SE3d::exp(lie_map);
    
    cout<<"the targeted transform is "<< endl
        << transform_se3.log().transpose()<<endl;

    // ================================ 点云变换 ================================

    std::vector<Eigen::Vector4d> point_in_camera;
    transformPointCloud(transform_se3,point_cloud,point_in_camera);
    AddNoise(point_in_camera);

    // ================================ 变换到pcl类型并存入Kdtree ===========================

    pcl::PointCloud<pcl::PointXYZ>::Ptr point_cloud_in_world (new pcl::PointCloud<pcl::PointXYZ>());
    pcl::PointCloud<pcl::PointXYZ>::Ptr point_cloud_in_camera(new pcl::PointCloud<pcl::PointXYZ>());
    ToPclPointType(point_cloud,*point_cloud_in_world);
    ToPclPointType(point_in_camera,*point_cloud_in_camera);

    pcl::KdTreeFLANN<pcl::PointXYZ> kdtree;
    kdtree.
    



}
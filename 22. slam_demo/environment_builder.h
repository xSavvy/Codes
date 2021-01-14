/*
 * @Author: Liu Weilong
 * @Date: 2021-01-05 09:33:25
 * @LastEditors: Liu Weilong
 * @LastEditTime: 2021-01-13 23:11:25
 * @FilePath: /3rd-test-learning/25. slam_demo/environment_builder.h
 * @Description: 
 */
#include <iostream>
#include <vector>
#include <cmath>

#include "Eigen/Eigen"
#include "opencv2/core/core.hpp"

using namespace std;

#define _S_SLAM_DEMO_ namespace slam_demo {
#define _E_SLAM_DEMO_ };


_S_SLAM_DEMO_

using Point = Eigen::Vector3d;
using Transfrom = Eigen::Matrix4d;
using Rot = Eigen::Matrix3d;
using InsParam = Eigen::Matrix3d;
using Translation = Eigen::Vector3d;
using UV = Eigen::Vector2d;


class Landmark
{
    public:
    Eigen::Vector3d position_;
    unsigned int label_;
};
class EnvironmentBuilderOptions
{
    public:
    void LoadOptions();
    double x_min_, y_min_,z_min_;
    double x_scale_,y_scale_,z_scale_;
    double x_interval_,y_interval_,z_interval_;
    bool initial = false;
};
class EnvironmentBuilder
{
    public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW
    EnvironmentBuilder(const string & config_path):
    config_path_(config_path){}

    bool BuildEnvironment(double x_min,double y_min,double z_min ,
                          double x_scale, double y_scale, double z_scale ,
                          double x_interval,double y_interval,double z_interval,
                          std::vector<Landmark,Eigen::aligned_allocator<Landmark>> &landmark_array);
    bool ShowEnvironment();
                        
    private:
    const string config_path_;
};

bool TransformPoints(const std::vector<Eigen::Vector3d> & points_world,
                     const Eigen::Matrix4d & Twc,
                     std::vector<Eigen::Vector3d> & points_camera);

bool NormalizePoints(const std::vector<Eigen::Vector3d> & points_camera,
                     std::vector<Eigen::Vector3d> & normalized_points);

bool CameraPointToUV(const std::vector<Eigen::Vector3d> & points_camera,
                     const Eigen::Matrix3d & camera_intrinsic,
                     std::vector<Eigen::Vector2d> & uvs);

bool UVToCameraPoint(const std::vector<Eigen::Vector2d> & uvs,
                     const Eigen::Matrix3d & camera_intrinsic,
                     std::vector<Eigen::Vector3d> & points_camera);


_E_SLAM_DEMO_
/*
 * @Author: Liu Weilong
 * @Date: 2021-01-05 09:33:25
 * @LastEditors: Liu Weilong 
 * @LastEditTime: 2021-01-05 09:48:45
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

    EnvironmentBuilder(const string & config_path):
    config_path_(config_path)
    {
        
    }

    bool BuildEnvironment(double x_min,double y_min,double z_min ,
                          double x_scale, double y_scale, double z_scale ,
                          double x_interval,double y_interval,double z_interval,
                          std::vector<Landmark,Eigen::aligned_allocator<Landmark>> &landmark_array);

    bool ShowEnvironment();
                        
    private:
    const string config_path_;
};

void TransfromPointIntoNewFrame(const Point &  point_a ,Point & point_b,
                                const Rot & r_ab,const Translation& t_ab);

void TransformNormalizedPointIntoUV(const Eigen::Matrix3d & intrinc_params,
                                    const Eigen::Vector3d landmark,
                                    UV & uv);

_E_SLAM_DEMO_
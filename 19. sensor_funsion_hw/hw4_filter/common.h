/*
 * @Author: Liu Weilong
 * @Date: 2020-11-22 16:04:51
 * @LastEditors: Liu Weilong
 * @LastEditTime: 2020-11-22 16:12:46
 * @Description: 
 */
#include <g2o/stuff/sampler.h>
#include "sophus/so3.hpp"

bool AddNoise(std::vector<Eigen::Vector3d> & point_cloud)
{
    // scale 再大基本就挂了  因为点在设置的时候就比较密集
    double scale = 0.01;
    Eigen::Matrix3d covar = Eigen::Matrix3d::Identity()*scale;
    g2o::GaussianSampler<Eigen::Matrix<double,3,1>,Eigen::Matrix<double,3,3>> sampler;
    sampler.setDistribution(covar);
    for(auto & point :point_cloud)
    {
        Eigen::Vector3d noise;
        noise<<sampler.generateSample();
        // cout<<"the noise is "<<noise.transpose()<<endl;
        point = point + noise;
    }
}

bool AddNoiseSO3(std::vector<Eigen::Vector3d> & point_cloud)
{
    // scale 再大基本就挂了  因为点在设置的时候就比较密集
    double scale = 0.001;
    Eigen::Matrix3d covar = Eigen::Matrix3d::Identity()*scale;
    g2o::GaussianSampler<Eigen::Matrix<double,3,1>,Eigen::Matrix<double,3,3>> sampler;
    sampler.setDistribution(covar);
    for(auto & point :point_cloud)
    {
        Eigen::Vector3d noise;
        noise<<sampler.generateSample();
        point = (Sophus::SO3d::exp(point)* Sophus::SO3d::exp(noise)).log();
    }
}
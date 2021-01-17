/*
 * @Author: Liu Weilong
 * @Date: 2021-01-18 07:33:28
 * @LastEditors: Liu Weilong
 * @LastEditTime: 2021-01-18 07:48:02
 * @Description: 
 */

#pragma once

#include <vector>

#include "Eigen/Eigen"
#include "opencv2/core/core.hpp"

#define _S_SLAM_DEMO_ namespace slam_demo {
#define _E_SLAM_DEMO_ };

_S_SLAM_DEMO_


class Converter
{
    public:
    template<>
    cv::Mat toMat(Eigen::Matrix<double,N,M> & temp);
    std::vector<cv::Mat> toMat(std::vector<Eigen::Matrix<double,N,M,Allocator>>);

    cv::Mat toMat(Eigen::Matrix<float,N,M> & temp);
    std::vector<cv::Mat> toMat(std::vector<Eigen::Matrix<float,N,M,Allocator>>);

};

template<size_t N,size_t M>
cv::Mat Converter::toMat(Eigen::Matrix<double,N,M> & temp)
{
    cv::Mat temp(N,M,CV)
}
_E_SLAM_DEMO_
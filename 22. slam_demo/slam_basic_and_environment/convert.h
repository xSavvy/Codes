/*
 * @Author: Liu Weilong
 * @Date: 2021-01-18 07:33:28
 * @LastEditors: Liu Weilong 
 * @LastEditTime: 2021-01-18 11:08:03
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
    
    template<size_t N, size_t M>
    cv::Mat toMat(Eigen::Matrix<double,N,M> & temp);
    template<template Allocator,size_t N, size_t M>
    std::vector<cv::Mat> toMat(const std::vector<Eigen::Matrix<double,N,M>,Allocator> &);

    template<size_t N, size_t M>
    cv::Mat toMat(Eigen::Matrix<float,N,M> & temp);
    template<template Allocator,size_t N, size_t M>
    std::vector<cv::Mat> toMat(const std::vector<Eigen::Matrix<float,N,M>,Allocator> &);

};


cv::Mat toMat(Eigen::Matrix<double,6,5> & temp)
{
    
}
_E_SLAM_DEMO_
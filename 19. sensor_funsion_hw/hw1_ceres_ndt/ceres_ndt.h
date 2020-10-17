/*
 * @Author: Liu Weilong
 * @Date: 2020-10-17 21:41:02
 * @LastEditors: Liu Weilong
 * @LastEditTime: 2020-10-18 07:21:48
 * @Description:  基于ceres 的ndt 算法
 */
#include <iostream>
#include "Eigen/Eigen"
#include "sophus/se3.hpp"
#include "glog/logging.h"
#include "ceres/ceres.h"

template <typename Scalar>
Sophus::SO3<Scalar> getCeresSO3AndTheta(const Eigen::Matrix<Scalar,3,1> & rotation)
{
    LOG_IF(INFO,theta != NULL);
    using ceres::abs;
    using ceres::cos;
    using ceres::sin;
    using ceres::sqrt;
    Scalar theta_sq = rotation(0) * rotation(0) +
                      rotation(1) * rotation(1) + 
                      rotation(2) * rotation(2);

    Scalar imag_factor;
    Scalar real_factor;
    if (theta_sq < Scalar(0.0)) {
      *theta = Scalar(0);
      Scalar theta_po4 = theta_sq * theta_sq;
      imag_factor = Scalar(0.5) - Scalar(1.0 / 48.0) * theta_sq +
                    Scalar(1.0 / 3840.0) * theta_po4;
      real_factor = Scalar(1) - Scalar(1.0 / 8.0) * theta_sq +
                    Scalar(1.0 / 384.0) * theta_po4;
    } else {
      *theta = sqrt(theta_sq);
      Scalar half_theta = Scalar(0.5) * (*theta);
      Scalar sin_half_theta = sin(half_theta);
      imag_factor = sin_half_theta / (*theta);
      real_factor = cos(half_theta);
    }

    SO3 q;
    q.unit_quaternion_nonconst() =
        QuaternionMember(real_factor, imag_factor * omega.x(),
                         imag_factor * omega.y(), imag_factor * omega.z());
    SOPHUS_ENSURE(abs(q.unit_quaternion().squaredNorm() - Scalar(1)) <
                      Sophus::Constants<Scalar>::epsilon(),
                  "SO3::exp failed! omega: %, real: %, img: %",
                  omega.transpose(), real_factor, imag_factor);
    return q;
}


template <typename Scalar>
Sophus::SE3<Scalar> getCeresSE3(const Eigen::Matrix<Scalar,6,1>& pose)
{
    
}


class NDTCostFunctor
{
    public:

    NDTCostFunctor(const Eigen::Matrix3f & covar, 
                   const Eigen::Vector3f & mean,
                   const Eigen::Vector3f & point):
                   covar_(covar),mean_(mean)
    {
        Eigen::LLT<Eigen::Matrix3f> llt_of_covar(covar);
        l_matrix_ = llt_of_covar.matrixL();
        LOG(INFO)<<"A  cost function is built"<<std::endl;
    }
    
    template <typename T>
    bool operator()(const T* pose , T* resiudal)const
    {
        Eigen::Map<Eigen::Matrix<T,3,1>> residual_map(residual);
        Eigen::Map<Eigen::Matrix<T,6,1>> pose_map;
        Sophus::SE3<T> se3_ = Sophus::SE3<T>::exp(pose_map);
        Eigen::Matrix<T,3,1> point_homo_;
        point_homo_<<T(point_(0)),T(point_(1)),T(point(2));

        residual_map = se3_*point_homo_;
        return true;
    }
    
    private:
    Eigen::Matrix3f covar_;
    Eigen::Vector3f mean_;
    Eigen::Vector3f point_;
    Eigen::Matrix3f l_matrix_;
};

class SE3LocalParam :public ceres::LocalParameterization
{
    public:

    virtual bool Plus(const double* x,
                    const double* delta,
                    double* x_plus_delta) const 
    {
        
        
        return true;
    }
};
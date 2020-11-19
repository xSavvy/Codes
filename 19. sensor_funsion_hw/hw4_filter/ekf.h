/*
 * @Author: Liu Weilong
 * @Date: 2020-11-18 07:23:29
 * @LastEditors: Liu Weilong
 * @LastEditTime: 2020-11-19 08:14:33
 * @Description:  因为IEKF 和 固定xk-1 估计 xk 的优化是等价的 所以这里直接使用 预积分+观测一起进行优化的形式在实现EKF
 */

#include "ImuTypes.h"

#include "Eigen/Eigen"
#include "sophus/so3.hpp"
#include "ceres/ceres.h"

#include <iostream>
using namespace std;

class EKF
{
    public:
    EKF(Eigen::Matrix<double,15,1> initial_state, Eigen::Matrix<double,15,15> initial_covar,
        Eigen::Matrix<double,6,6> laser_measurement_covar,
        IMU::Bias bias,IMU::Calib calib):
        imu_preintegrated_(bias,calib),
        cur_state_(initial_state),cur_covar_(initial_covar),
        laser_meassurement_covar_(laser_measurement_covar){}

    // interface
    void addImuMeasurement(const cv::Point3f &acceleration, const cv::Point3f &angVel, const float &dt);
    void addLaserMeasurement(Eigen::Vector3d delta_rotation, Eigen::Vector3d delta_translation);
    
    auto getResult() const;
    
    protected:
    // internal
    void updateImuPreintegration(IMU::Bias bias,IMU::Calib calib);
    void buildProblem(Eigen::Vector3d rotation, Eigen::Vector3d translation);
    void UpdateIMU();
    private:

    IMU::Preintegrated imu_preintegrated_;

    Eigen::Matrix<double,3,1> cur_rotation_;
    Eigen::Matrix<double,3,1> cur_translation_;
    Eigen::Matrix<double,15,1>  cur_state_;
    Eigen::Matrix<double,15,15> cur_covar_;
    Eigen::Matrix<double,6,6>   laser_meassurement_covar_;
};

class EKFPredictError:public ceres::SizedCostFunction<15,15>
{
    
};

class EKFObserError
{
    public:
    EKFObserError(Eigen::Matrix<double,6,6> laser_measurement_covar,
                                Eigen::Vector3d delta_rotation_meas, Eigen::Vector3d delta_translation_meas):
                                laser_measurement_covar_(laser_measurement_covar),
                                delta_rotation_(delta_rotation_meas),
                                delta_translation_(delta_translation_meas)
    {
        Eigen::LLT<Eigen::Matrix<double,6,6>> LLTSolver(laser_measurement_covar_);
        Lt_=LLTSolver.matrixL().transpose();
    }
    
    template<typename T>
    bool operator()(const T * rotation,const T* translation, T * residual)const
    {
        Eigen::Map<Eigen::Matrix<T,6,1>> residual_map(residual);
        Eigen::Map<Eigen::Matrix<T,3,1>> rotation_map(rotation);
        Eigen::Map<Eigen::Matrix<T,3,1>> translation_map(translation);

        residual_map.block(0,0,3,1) = rotation_map - delta_rotation_;
        residual_map.block(3,0,3,1) = translation_map - delta_translation_;

        return true;
    }

    private:
    Eigen::Matrix<double,6,6> laser_measurement_covar_;
    Eigen::Matrix<double,6,6> Lt_;
    Eigen::Vector3d delta_rotation_;
    Eigen::Vector3d delta_translation_;
};

class SO3LocalParameterization: public ceres::LocalParameterization
{
    public:
    virtual bool Plus(const double* x,
                const double* delta,
                double* x_plus_delta) const 
    {
        Eigen::Map<const Eigen::Vector3d> delta_x_map(delta);
        Eigen::Map<const Eigen::Vector3d> x_map(x);
        Eigen::Map<const Eigen::Vector3d> new_so3(x_plus_delta);

        auto x_SO3 = Sophus::SO3d::exp(x_map);
        auto delta_x_SO3 = Sophus::SO3d::exp(delta_x_map);

        new_so3 = (x_SO3*delta_x_SO3).log();

        return true;
    }

    virtual bool ComputeJacobian(const double* x, double* jacobian) const
    {
        
        
        return true;
    }

    virtual int GlobalSize() const { return 3; }
    virtual int LocalSize() const { return 3; }
};
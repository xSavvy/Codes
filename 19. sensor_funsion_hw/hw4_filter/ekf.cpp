/*
 * @Author: Liu Weilong
 * @Date: 2020-11-18 07:49:24
 * @LastEditors: Liu Weilong
 * @LastEditTime: 2020-11-19 07:38:37
 * @Description: 
 */
#include "ekf.h"

void EKF::addImuMeasurement(const cv::Point3f &acceleration, const cv::Point3f &angVel, const float &dt)
{
    imu_preintegrated_.IntegrateNewMeasurement(acceleration,angVel,dt);
}

void EKF::addLaserMeasurement(Eigen::Vector3d delta_rotation, Eigen::Vector3d delta_translation)
{
    // 构建优化
    buildProblem(delta_rotation,delta_translation);
    // 更新IMU
    UpdateIMU();
}

auto EKF::getResult() const
{
    return std::make_pair(cur_rotation_,cur_translation_);
}

void EKF::buildProblem(Eigen::Vector3d delta_rotation_measure, Eigen::Vector3d delta_translation_measure)
{
    ceres::Problem problem;
    
}



EKFObserError::EKFObserError(Eigen::Matrix<double,6,6> laser_measurement_covar,
                             Eigen::Vector3d delta_rotation_meas, Eigen::Vector3d delta_translation_meas):
                             laser_measurement_covar_(laser_measurement_covar),
                             delta_rotation_(delta_rotation_meas),
                             delta_translation_(delta_translation_meas)
{
    Eigen::LLT<Eigen::Matrix<double,6,6>> LLTSolver(laser_measurement_covar_);
    Lt_=LLTSolver.matrixL().transpose();
}

bool EKFObserError::Evaluate(const double * const * params, 
                             double * residual,
                             double ** jacobians)const
{
    
}

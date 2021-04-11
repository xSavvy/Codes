/*
 * @Author: Liu Weilong
 * @Date: 2021-04-11 09:18:45
 * @LastEditors: Liu Weilong
 * @LastEditTime: 2021-04-11 22:42:25
 * @Description: 
 */

#include <iostream>
#include <vector>
#include <string>

#include "Eigen/Eigen"

class IMU
{
    public:
    
    Eigen::Vector3d AccBias; 
    Eigen::Vector3d OmegaBias;
    Eigen::Vector3d AccNoise;
    Eigen::Vector3d GyroNoise;
};

class IMUMeasurement
{
    public:

    Eigen::Vector3d Acc;
    Eigen::Vector3d Omega;

    Eigen::Vector3d RealAcc;
    Eigen::Vector3d RealOmega;
};

class IMUState
{
    public:
    
    Eigen::Vector3d Position;
    Eigen::Vector3d Velocity;
    Eigen::Vector3d Theta;

    Eigen::Matrix3d PositionCov;
    Eigen::Matrix3d VelocityCov;
    Eigen::Matrix3d ThetaCov;

    Eigen::Matrix<double,15,15> Jacobian;
};

class IMUPropogator
{
    public:
    
    void prepogate();

    std::vector<IMUMeasurement> imu_measurement; 
};
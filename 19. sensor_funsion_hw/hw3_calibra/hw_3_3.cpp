/*
 * @Author: Liu Weilong
 * @Date: 2020-11-09 23:06:06
 * @LastEditors: Liu Weilong
 * @LastEditTime: 2020-11-11 08:23:23
 * @Description: 半系统级 imu 标定
 */

#include "Eigen/Eigen"
#include "ceres/ceres.h"
#include <utility>
#include <iostream>
#include <vector>

using namespace std;

class CalibAccel
{
    CalibAccel(std::vector<std::vector<Eigen::Vector3d>> * accel_data_ptr,
              std::vector<Eigen::Vector3d> * corresponding_gravity_ptr):
              gyro_motion_array_(gyro_data_ptr),
              corresponding_gravity_array_(corresponding_gravity_ptr){}
    
    void buildProblem()
    {
        
    }

    const auto getResult(){
        return std::tuple<Eigen::Matrix<double,3,1>,Eigen::Matrix<double,3,1>,
                          Eigen::Matrix<double,3,1>>(K_,S_,Bias_);
    }
    private:
    std::vector<std::vector<Eigen::Vector3d>> * gyro_motion_array_;
    std::vector<Eigen::Vector3d> * corresponding_gravity_array_;
    Eigen::Matrix<double,3,1> K_ = Eigen::Vector3d::Zero();
    Eigen::Matrix<double,3,1> S_ = Eigen::Vector3d::Zero();
    Eigen::Matrix<double,3,1> Bias_ = Eigen::Vector3d::Zero();

};

class CalibGyro
{
    public:
    CalibGyro(std::vector<std::vector<Eigen::Vector3d>> * gyro_data_ptr,
              std::vector<Eigen::Vector3d> * corresponding_gravity_ptr,
              std::vector<double> * dt_ptr):
              gyro_motion_array_(gyro_data_ptr),
              corresponding_gravity_array_(corresponding_gravity_ptr),
              dt_array_(dt_ptr){}
    
    void buildProblem()
    {
        
    }

    const auto getResult(){
        return std::tuple<Eigen::Matrix<double,3,1>,Eigen::Matrix<double,6,1>,
                          Eigen::Matrix<double,3,1>>(K_,S_,Bias_); 
    }
    
    private:
    std::vector<std::vector<Eigen::Vector3d>> * gyro_motion_array_;
    std::vector<Eigen::Vector3d> * corresponding_gravity_array_;
    std::vector<double> * dt_array_;
    Eigen::Matrix<double,3,1> K_;
    Eigen::Matrix<double,6,1> S_;
    Eigen::Matrix<double,3,1> Bias_ = Eigen::Vector3d::Zero();

    class GyroCostFunctor
    {
        public:
        private:
        
    }
};

int main()
{
    
}
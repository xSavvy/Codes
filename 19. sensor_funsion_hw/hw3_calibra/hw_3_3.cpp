/*
 * @Author: Liu Weilong
 * @Date: 2020-11-09 23:06:06
 * @LastEditors: Liu Weilong
 * @LastEditTime: 2020-11-12 08:00:43
 * @Description: 半系统级 imu 标定
 *               
 */
#include "sophus/so3.hpp"
#include "Eigen/Eigen"
#include "ceres/ceres.h"
#include <utility>
#include <iostream>
#include <vector>

using namespace std;


template<typename T>
bool buildErrorMatrix(const T * k, const T * s,
                        Eigen::Matrix<T,3,3> & error_matrix) 
{
    error_matrix<<k[0],s[0],s[1]
                 ,s[2],k[1],s[3]
                 ,s[4],s[5],k[2];
    return true;
}
template<typename T>
void integrateGyroMeasurementEuler(Eigen::Matrix<T,3,3> & K_and_S,
                                   std::vector<Eigen::Vector3d> gyro_motion_measurements,
                                   Eigen::Matrix<T,3,3> & integrated_result)
{
    Eigen::Vector3d sum = Eigen::Vector3d::Zero();
    for(auto & measurement:gyro_motion_measurements)
    {
        sum += measurement;
    }
    integrated_result = K_and_S * Sophus::SO3d::hat(sum).cast<T>()* K_and_S.transpose();
}

class CalibAccel
{
    CalibAccel(std::vector<std::vector<Eigen::Vector3d>> * accel_data_ptr,
              std::vector<Eigen::Vector3d> * corresponding_gravity_ptr):
              gyro_motion_array_(accel_data_ptr),
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
        GyroCostFunctor(std::vector<Eigen::Vector3d> * gyro_motion_measurment,
                        Eigen::Vector3d corresponding_gravity_front,
                        Eigen::Vector3d corresponding_gravity_back):
                        gyro_motion_measurement_(gyro_motion_measurment),
                        corresponding_gravity_front_(corresponding_gravity_front),
                        corresponding_gravity_back_(corresponding_gravity_back){}

        template<typename T>
        bool operator()(const T* K, const T* S, T* residual)const
        {
            Eigen::Matrix<T,3,3> error_model;
            buildErrorMatrix(K,S,error_model);
            Eigen::Matrix<T,3,3> integration;
            integrateGyroMeasurementEuler(error_model,*gyro_motion_measurement_,integration);

            Eigen::Map<Matrix<T,3,1>> residual_map(residual);
            Eigen::Matrix<double,3,3> one = Eigen::Matrix3d::Identity();

            residaul_map = corresponding_gravity_back_.cast<T>()-(one.cast<T>()+integration)*corresponding_gravity_front_;
            return true;
        }
        
        static ceres::CostFunction * Create(std::vector<Eigen::Vector3d> * gyro_motion_measurment,
                                            Eigen::Vector3d corresponding_gravity_front,
                                            Eigen::Vector3d corresponding_gravity_back)
        {
            return new ceres::AutoDiffCostFunction<GyroCostFunctor,3,9>
                       (new GyroCostFunctor(gyro_motion_measurment,
                                            corresponding_gravity_front,
                                            corresponding_gravity_back));
        }

        private:
        const std::vector<Eigen::Vector3d> * gyro_motion_measurement_;
        Eigen::Vector3d corresponding_gravity_front_;
        Eigen::Vector3d corresponding_gravity_back_;
    };
};

int main()
{
    
}
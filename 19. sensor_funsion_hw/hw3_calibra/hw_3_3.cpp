/*
 * @Author: Liu Weilong
 * @Date: 2020-11-09 23:06:06
 * @LastEditors: Liu Weilong
 * @LastEditTime: 2020-11-13 08:16:49
 * @Description: 半系统级 imu 标定
 *               
 */
#include "read_csv.h"
#include "sophus/so3.hpp"
#include "Eigen/Eigen"
#include "ceres/ceres.h"
#include <utility>
#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
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

// 这里是SO3 的泰勒一阶展开
template<typename T>
void integrateGyroMeasurementEuler(Eigen::Matrix<T,3,3> & K_and_S,
                                   std::vector<Eigen::Vector3d> gyro_motion_measurements,
                                   Eigen::Matrix<T,3,3> & integrated_result)
{
    Eigen::Vector3d sum = Eigen::Vector3d::Zero();
    for(auto & measurement:gyro_motion_measurements)
    {
        sum += measurement/180.0*M_PI;
    }
    integrated_result = K_and_S * Sophus::SO3d::hat(sum).cast<T>()* K_and_S.transpose();
}

void transformIntoVector(const std::vector<std::vector<double>> & data, std::vector<Eigen::Vector3d> & output)
{
    output.clear();
    output.reserve(data.front().size());
    for(int i=0;i<data.front().size();i++)
    {
        output.push_back(Eigen::Vector3d(data.at(0)[i],data.at(1)[i],data.at(2)[i]));
    }

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
    CalibGyro(std::vector<Eigen::Vector3d> * gyro_data_ptr,
              std::vector<Eigen::Vector3d> * gyro_data_real_ptr,
              std::vector<Eigen::Vector3d> * corresponding_gravity_ptr,
              double hz):
              gyro_motion_array_(gyro_data_ptr),
              gyro_motion_real_(gyro_data_real_ptr),
              corresponding_gravity_array_(corresponding_gravity_ptr),
              hz_(hz){}
    
    void buildProblem()
    {
        ceres::Problem problem;
        bool motion_interval = false;
        
        std::vector<Eigen::Vector3d> gyro_in_motion_interval;
        unsigned int pre_index= 0;
        // 用于寻找motion_interval
        for(int i =0;i< gyro_motion_real_->size();i++)
        {
            if(!motion_interval)
            {
                if(gyro_motion_real_->at(i).norm()!=0.0)
                {
                    motion_interval = true;
                    pre_index=i;
                    gyro_in_motion_interval.push_back(gyro_motion_array_->at(i));
                }
            }
            else
            {
                if(gyro_motion_real_->at(i).norm()==0.0)
                {
                    motion_interval = false;
                    gyro_in_motion_interval.clear();
                    
                    continue;
                }
                gyro_in_motion_interval.push_back(gyro_motion_array_->at(i));
            }
            
        }    
    }

    const auto getResult(){
        return std::tuple<Eigen::Matrix<double,3,1>,Eigen::Matrix<double,6,1>,
                          Eigen::Matrix<double,3,1>>(K_,S_,Bias_); 
    }
    
    private:
    std::vector<Eigen::Vector3d> * gyro_motion_array_;
    std::vector<Eigen::Vector3d> * gyro_motion_real_;
    std::vector<Eigen::Vector3d> * corresponding_gravity_array_;
    double hz_;
    Eigen::Matrix<double,3,1> K_;
    Eigen::Matrix<double,6,1> S_;
    Eigen::Matrix<double,3,1> Bias_ = Eigen::Vector3d::Zero();

    class GyroCostFunctor
    {
        public:
        GyroCostFunctor(std::vector<Eigen::Vector3d> * gyro_motion_measurment,
                        Eigen::Vector3d corresponding_gravity_front,
                        Eigen::Vector3d corresponding_gravity_back,
                        double dt):
                        gyro_motion_measurement_(gyro_motion_measurment),
                        corresponding_gravity_front_(corresponding_gravity_front),
                        corresponding_gravity_back_(corresponding_gravity_back),
                        deltaT(dt){}

        template<typename T>
        bool operator()(const T* K, const T* S, T* residual)const
        {
            Eigen::Matrix<T,3,3> error_model;
            buildErrorMatrix(K,S,error_model);
            Eigen::Matrix<T,3,3> integration;
            integrateGyroMeasurementEuler(error_model,*gyro_motion_measurement_,integration);

            integration = integration * deltaT;
            Eigen::Map<Eigen::Matrix<T,3,1>> residual_map(residual);
            Eigen::Matrix<double,3,3> one = Eigen::Matrix3d::Identity();

            residual_map = corresponding_gravity_back_.cast<T>()-(one.cast<T>()+integration)*corresponding_gravity_front_;
            return true;
        }
        
        static ceres::CostFunction * Create(std::vector<Eigen::Vector3d> * gyro_motion_measurment,
                                            Eigen::Vector3d corresponding_gravity_front,
                                            Eigen::Vector3d corresponding_gravity_back,
                                            double dt)
        {
            return new ceres::AutoDiffCostFunction<GyroCostFunctor,3,3,6>
                       (new GyroCostFunctor(gyro_motion_measurment,
                                            corresponding_gravity_front,
                                            corresponding_gravity_back,
                                            dt));
        }

        private:
        std::vector<Eigen::Vector3d> * gyro_motion_measurement_;
        Eigen::Vector3d corresponding_gravity_front_;
        Eigen::Vector3d corresponding_gravity_back_;
        double deltaT;
    };
};

int main()
{
    // ==================================== read_csv =================================================
    
    std::string gyro_real_measurement = "/home/lwl/workspace/HW/gnss-ins-sim/demo_motion_def_files/imu_simulation_hw1/ref_gyro.csv";
    std::string gyro_measurement = "/home/lwl/workspace/HW/gnss-ins-sim/demo_motion_def_files/imu_simulation_hw1/gyro-0.csv";
    std::string gravity_measurement = "/home/lwl/workspace/HW/gnss-ins-sim/demo_motion_def_files/imu_simulation_hw1/ref_accel.csv";
    std::vector<std::string> headers_real;
    std::vector<std::vector<double>> data_real;
    std::vector<std::string> headers;
    std::vector<std::vector<double>> data;
    std::vector<std::string> headers_gravity;
    std::vector<std::vector<double>> data_gravity;

    std::vector<Eigen::Vector3d> gyro_in_vector;
    std::vector<Eigen::Vector3d> gyro_real_in_vector;
    std::vector<Eigen::Vector3d> gravity_in_vector;
    
    if(!readCSV(headers_real,data_real,gyro_real_measurement))
    {
        std::abort();
    };
    if(!readCSV(headers,data,gyro_measurement))
    {
        std::abort();
    };
    if(!readCSV(headers_gravity,data_gravity,gravity_measurement))
    {
        std::abort();
    };

    transformIntoVector(data_real,gyro_real_in_vector);
    transformIntoVector(data,gyro_in_vector);
    transformIntoVector(data_gravity,gyro_in_vector);

    // ================================== 添加 安装误差 ==========================================
    
    Eigen::Vector3d axis(1,0.3,0.4);
    Eigen::AngleAxisd angle_axis(0.05,axis.normalized());
    Eigen::Matrix3d error_matrix = angle_axis.matrix();
    error_matrix(0,0) = 1.02;
    error_matrix(1,1) = 0.88;
    error_matrix(2,2) = 1.10;

    std::cout<<"show the target error model is "<<endl
             << error_matrix<<endl;
    
    auto error_matrix_inv = error_matrix.inverse().matrix();

    for(auto & info:gyro_in_vector)
    {
        info = error_matrix_inv * info;
    }

}
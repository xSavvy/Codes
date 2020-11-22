/*
 * @Author: Liu Weilong
 * @Date: 2020-11-22 10:47:26
 * @LastEditors: Liu Weilong
 * @LastEditTime: 2020-11-22 16:49:21
 * @Description: EKF 测试代码 从gnss-ins-sim 之中提取真值加上噪声之后，
 *                           对激光得到数值进行模拟
 */
#include "ekf.h"
#include "common.h"
#include <iostream>

using namespace std;

void prepareLaserSimData(const std::vector<Eigen::Vector3d> & real_rotation_data,
                         const std::vector<Eigen::Vector3d> & real_translation_data,
                         std::vector<Eigen::Vector3d> & noise_rotation_data,
                         std::vector<Eigen::Vector3d> & noise_translation_data,
                         double IMU_hz , double measure_hz)
{ 
    // 尽量使用 可以整除 的 IMU_hz 和 measure_hz
    
    int gap = IMU_hz/measure_hz;
    int size_translation = static_cast<double>(real_translation_data.size())/
                           static_cast<double>(gap)+3;
    int size_rotation = size_translation;
    noise_rotation_data.reserve(size_translation);
    noise_translation_data.reserve(size_rotation);
    auto pre_position = real_translation_data.front();
    auto pre_rotation = real_rotation_data.front();
    
    Eigen::Matrix4d T_i_w = Eigen::Matrix4d::Identity();
    T_i_w.block(0,0,3,3) = Sophus::SO3d::exp(pre_rotation).matrix();
    T_i_w.block(0,3,3,1) = pre_position;
    Eigen::Matrix4d T_j_w = Eigen::Matrix4d::Identity();
    for(int j= gap-1;j<real_rotation_data.size();j=j+gap)
    {
        T_j_w.block(0,0,3,3) = Sophus::SO3d::exp(real_rotation_data.at(j)).matrix();
        T_j_w.block(0,3,3,1) = real_translation_data.at(j);
        auto T_j_i = T_i_w.inverse()*T_j_w;
        Eigen::AngleAxisd tmp_angleaxis(T_j_i.block(0,0,3,3));
        noise_rotation_data.push_back(Eigen::Vector3d(T_j_i.block(0,3,3,1)));
        T_i_w = T_j_w;   
    }
    AddNoise(noise_translation_data);
    AddNoiseSO3(noise_rotation_data);

}

int main()
{

    // ====================================   数据提取 ====================================================
    std::string gyro_real_measurement = "/home/lwl/workspace/HW/gnss-ins-sim/demo_motion_def_files/imu_simulation_hw1/ref_gyro.csv";
    std::string gyro_measurement = "/home/lwl/workspace/HW/gnss-ins-sim/demo_motion_def_files/imu_simulation_hw1/gyro-0.csv";
    std::string gravity_measurement = "/home/lwl/workspace/HW/gnss-ins-sim/demo_motion_def_files/imu_simulation_hw1/ref_accel.csv";
    std::string accel_measurement = "/home/lwl/workspace/HW/gnss-ins-sim/demo_motion_def_files/imu_simulation_hw1/accel-0.csv";
    std::string real_position = "";
    std::string real_rotation = " ";

    
    std::vector<std::string> headers_real;
    std::vector<std::vector<double>> data_real;
    std::vector<std::string> headers;
    std::vector<std::vector<double>> data;
    std::vector<std::string> headers_gravity;
    std::vector<std::vector<double>> data_gravity;
    std::vector<std::string> headers_accel;
    std::vector<std::vector<double>> accel_data;

    std::vector<Eigen::Vector3d> gyro_in_vector;
    std::vector<Eigen::Vector3d> gyro_real_in_vector;
    std::vector<Eigen::Vector3d> accel_in_vector;
    std::vector<Eigen::Vector3d> gravity_in_vector;


    
}


/*
 * @Author: Liu Weilong
 * @Date: 2020-11-22 10:47:26
 * @LastEditors: Liu Weilong
 * @LastEditTime: 2020-11-23 08:10:51
 * @Description: EKF 测试代码 从gnss-ins-sim 之中提取真值加上噪声之后，
 *                           对激光得到数值进行模拟
 */

#include "ekf.h"
#include "common.h"
#include "read_csv.h"
#include <iostream>

using namespace std;

int main()
{

    // ====================================   数据提取 ====================================================
    std::string gyro_real_p = "/home/lwl/workspace/HW/gnss-ins-sim/demo_motion_def_files/imu_simulation_hw1/ref_gyro.csv";
    std::string gyro_measurement_p = "/home/lwl/workspace/HW/gnss-ins-sim/demo_motion_def_files/imu_simulation_hw1/gyro-0.csv";
    std::string accel_real_p = "/home/lwl/workspace/HW/gnss-ins-sim/demo_motion_def_files/imu_simulation_hw1/ref_accel.csv";
    std::string accel_measurement_p = "/home/lwl/workspace/HW/gnss-ins-sim/demo_motion_def_files/imu_simulation_hw1/accel-0.csv";
    std::string real_position_p = "/home/lwl/workspace/HW/gnss-ins-sim/demo_motion_def_files/imu_simulation_hw1/ref_pos.csv";
    std::string real_rotation_p = "/home/lwl/workspace/HW/gnss-ins-sim/demo_motion_def_files/imu_simulation_hw1/ref_att_quat.csv";
    
    std::vector<std::string> gyro_real_headers;
    std::vector<std::vector<double>> gyro_real;
    std::vector<std::string> gyro_meas_headers;
    std::vector<std::vector<double>> gyro_meas;
    std::vector<std::string> accel_real_headers;
    std::vector<std::vector<double>> accel_real;
    std::vector<std::string> accel_meas_headers;
    std::vector<std::vector<double>> accel_meas;
    std::vector<std::string> pos_real_headers;
    std::vector<std::vector<double>> pos_real;
    std::vector<std::string> rot_real_headers;
    std::vector<std::vector<double>> rot_real;

    std::vector<Eigen::Matrix<double,3,1>> gyro_in_vector;
    std::vector<Eigen::Matrix<double,3,1>> gyro_real_in_vector;
    std::vector<Eigen::Matrix<double,3,1>> accel_in_vector;
    std::vector<Eigen::Matrix<double,3,1>> accel_real_in_vector;
    std::vector<Eigen::Matrix<double,3,1>> pos_real_in_vector;
    std::vector<Eigen::Matrix<double,4,1>> rot_real_in_vector;

    {    
        if(!readCSV(gyro_real_headers,gyro_real,gyro_real_p,3))
        {
            std::abort();
        };
        if(!readCSV(gyro_meas_headers,gyro_meas,gyro_measurement_p,3))
        {
            std::abort();
        };
        if(!readCSV(accel_real_headers,accel_real,accel_real_p,3))
        {
            std::abort();
        };
        if(!readCSV(accel_meas_headers,accel_meas,accel_measurement_p,3))
        {
            std::abort();
        };
        if(!readCSV(pos_real_headers,pos_real,real_position_p,3))
        {
            std::abort();
        };
        if(!readCSV(rot_real_headers,rot_real,real_rotation_p,3))
        {
            std::abort();
        };
    }

    {
        transformIntoVector(gyro_meas,gyro_in_vector);
        transformIntoVector(gyro_real,gyro_real_in_vector);
        transformIntoVector(accel_meas,accel_in_vector);
        transformIntoVector(accel_real,accel_real_in_vector);
        transformIntoVector(pos_real,pos_real_in_vector);
        transformIntoVector(rot_real,rot_real_in_vector);
    }

    for(auto & element: rot_real_in_vector)
    {
        std::cout<<element.transpose()<<std::endl;
    }

    return 0;
}


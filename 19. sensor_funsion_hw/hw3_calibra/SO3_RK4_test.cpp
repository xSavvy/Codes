/*
 * @Author: Liu Weilong
 * @Date: 2020-11-12 10:40:57
 * @LastEditors: Liu Weilong 
 * @LastEditTime: 2020-11-12 15:05:09
 * @FilePath: /3rd-test-learning/19. sensor_funsion_hw/hw3_calibra/SO3_RK4_test.cpp
 * @Description: 用于验证SO3 RK4 的正确性
 */
#include "read_csv.h"
#include "sophus/so3.hpp"
#include "Eigen/Eigen"
#include <iostream>
#include <vector>
#include <string>

using namespace std;
using namespace Eigen;
void IntegrationEuler(const vector<Vector3d> & gyro_measurements,
                      double dt,vector<Matrix3d> & output)
{
    Sophus::SO3d cur = Sophus::SO3d::exp(Vector3d::Zero());
    output.reserve(gyro_measurements.size());
    for(auto & measurement: gyro_measurements)
    {
        cur = cur * Sophus::SO3d::exp(measurement *dt);
        output.push_back(cur.matrix());
    }
}

void IntegrationEulerWithNumeric1stApproximate(const vector<Vector3d> & gyro_measurements,
                                               double dt,vector<Matrix3d> & output)
{
    Sophus::SO3d cur = Sophus::SO3d::exp(Vector3d::Zero());
    output.reserve(gyro_measurements.size());
    for(auto & measurement: gyro_measurements)
    {
        auto numeric_matrix = cur.matrix()*(Matrix3d::Identity()+ Sophus::SO3d::hat(measurement)*dt);
        Eigen::AngleAxisd normal_angle_axis(numeric_matrix);
        Sophus::SO3d cur(normal_angle_axis.matrix());
        output.push_back(cur.matrix());
    }
}

void IntegrationMidValue(const vector<Vector3d> & gyro_measurements,
                         double dt,vector<Matrix3d> & output)
{
    Sophus::SO3d cur = Sophus::SO3d::exp(Vector3d::Zero());
    output.reserve(gyro_measurements.size());
    for(auto s_ptr = gyro_measurements.begin(),n_ptr = next(s_ptr);n_ptr!=gyro_measurements.end();next(s_ptr))
    {
        auto midvalue = 0.5*(*s_ptr + * n_ptr);
        cur = cur * Sophus::SO3d::exp(midvalue *dt);
        output.push_back(cur.matrix());
        s_ptr++;
    }
}

// void IntegrationRK4(const vector<Vector3d> & gyro_measurements,
//                     double dt,vector<Matrix3d> & output)
// {
//     Sophus::SO3d cur = Sophus::SO3d::exp(Vector3d::Zero());
//     output.reserve(gyro_measurements.size());
//     for(auto s_ptr = gyro_measurements.begin(),n_ptr = next(s_ptr);n_ptr!=gyro_measurements.end();next(s_ptr))
//     {
//         auto tmp_so3 = cur;
//         auto k1 = tmp_so3.matrix()*Sophus::SO3d::hat(*s_ptr);
//         tmp_so3 = tmp_so3 * Sophus::SO3d::exp(dt*(*s_ptr));
//         auto k2 = tmp_so3.matrix()*Sophus::SO3d::hat((*s_ptr+*n_ptr)*0.5);
//         tmp_so3 = tmp_so3 * Sophus::SO3d::exp((*s_ptr+*n_ptr)*0.5*dt);
//         auto k3 = tmp_so3.matrix()*Sophus::SO3d::hat((*s_ptr+*n_ptr)*0.5);
//         tmp_so3 = tmp_so3 * Sophus::SO3d::exp((*s_ptr+*n_ptr)*0.5*dt);
//         auto k4 = tmp_so3.matrix()*Sophus::SO3d::hat((*n_ptr)*0.5);
//         cur = cur * Sophus::SO3d::exp(dt*k1/6.0)*
//                     Sophus::SO3d::exp(dt*k2/3.0)*
//                     Sophus::SO3d::exp(dt*k3/3.0)*
//                     Sophus::SO3d::exp(dt*k4/6.0);
//         output.push_back(cur.matrix());
//         s_ptr++;
//     }
// }


int main()
{
    std::string gyro_real_measurement = "/home/sunny/workspace_private/gnss-ins-sim/demo_motion_def_files/sim_data/ref_gyro.csv";
    std::vector<std::string> headers;
    std::vector<std::vector<double>> data;
    std::vector<Vector3d> data_in_vector;
    
    readCSV(headers,data,gyro_real_measurement);
    
    data_in_vector.reserve(data.front().size());
    
    for(int i=0;i<data.front().size();i++)
    {
        data_in_vector.push_back(Eigen::Vector3d(data.at(0)[i],data.at(1)[i],data.at(2)[i]));
    }
    
    std::vector<Matrix3d> result_1,result_2,result_3,result_4;
    IntegrationEuler(data_in_vector,0.01,result_1);
    IntegrationEulerWithNumeric1stApproximate(data_in_vector,0.01,result_2);
    IntegrationMidValue(data_in_vector,0.01,result_3);
    // IntegrationRK4(data_in_vector,0.01,result_4);

    // show the final result
    Eigen::Matrix3d rotation_matrix1;
    rotation_matrix1 = Eigen::AngleAxisd(90.0, Eigen::Vector3d::UnitZ()) *
                Eigen::AngleAxisd(56.0, Eigen::Vector3d::UnitY()) *
                Eigen::AngleAxisd(88.0, Eigen::Vector3d::UnitX());
    cout<<"the result should be "<<endl
        << rotation_matrix1<<endl;
    cout<<"the IntegrationEuler result is "<<endl
        << result_1.back()<<endl;
    cout<<"the IntegrationEulerWithNumeric1stApproximate result is "<<endl
        << result_2.back()<<endl;
    cout<<"the IntegrationMidValue result is "<<endl
        << result_3.back()<<endl;
    cout<<"the IntegrationRK4 result is "<<endl
        << result_4.back()<<endl;

}
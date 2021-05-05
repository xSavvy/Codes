
#include "param.h"  // calib

#include "Eigen/Eigen"

#include <opencv2/core.hpp>
#include <iostream>
#include <algorithm>
#include <string>
#include <fstream>
#include <vector>
#include <limits>



void load_asl_calib(const std::string &asl_path,
                    XP::DuoCalibParam &calib_param) {
  std::string cam0_yaml = asl_path + "/mav0/cam0/sensor.yaml";
  std::string cam1_yaml = asl_path + "/mav0/cam1/sensor.yaml";
  std::string imu0_yaml = asl_path + "/mav0/imu0/sensor.yaml";
  YAML::Node cam0_calib = YAML::LoadFile(cam0_yaml);
  YAML::Node cam1_calib = YAML::LoadFile(cam1_yaml);
  YAML::Node imu0_calib = YAML::LoadFile(imu0_yaml);
  //intrinsics
  std::vector<float> v_float = cam0_calib["intrinsics"].as<std::vector<float>>();
  calib_param.Camera.cv_camK_lr[0] << v_float[0], 0, v_float[2],
      0, v_float[1], v_float[3],
      0, 0, 1;
  calib_param.Camera.cameraK_lr[0] << v_float[0], 0, v_float[2],
      0, v_float[1], v_float[3],
      0, 0, 1;
  v_float = cam1_calib["intrinsics"].as<std::vector<float>>();
  calib_param.Camera.cv_camK_lr[1] << v_float[0], 0, v_float[2],
      0, v_float[1], v_float[3],
      0, 0, 1;
  calib_param.Camera.cameraK_lr[1] << v_float[0], 0, v_float[2],
      0, v_float[1], v_float[3],
      0, 0, 1;
  //distortion_coefficients
  std::vector<double> v_double = cam0_calib["distortion_coefficients"].as<std::vector<double>>();
  calib_param.Camera.cv_dist_coeff_lr[0] = (cv::Mat_<float>(8, 1) << static_cast<float>(v_double[0]), static_cast<float>(v_double[1]),
      static_cast<float>(v_double[2]), static_cast<float>(v_double[3]), 0.0, 0.0, 0.0, 0.0);
  v_double = cam1_calib["distortion_coefficients"].as<std::vector<double>>();
  calib_param.Camera.cv_dist_coeff_lr[1] = (cv::Mat_<float>(8, 1) << static_cast<float>(v_double[0]), static_cast<float>(v_double[1]),
      static_cast<float>(v_double[2]), static_cast<float>(v_double[3]), 0.0, 0.0, 0.0, 0.0);
  //TBS
  v_double = cam0_calib["T_BS"]["data"].as<std::vector<double>>();
  Eigen::Matrix4d b_t_c0 = Eigen::Map<Eigen::Matrix<double, 4, 4, Eigen::RowMajor>>(&v_double[0]);
  v_double = cam1_calib["T_BS"]["data"].as<std::vector<double>>();
  Eigen::Matrix4d b_t_c1 = Eigen::Map<Eigen::Matrix<double, 4, 4, Eigen::RowMajor>>(&v_double[0]);
  v_double = imu0_calib["T_BS"]["data"].as<std::vector<double>>();
  Eigen::Matrix4d b_t_i = Eigen::Map<Eigen::Matrix<double, 4, 4, Eigen::RowMajor>>(&v_double[0]);
  //ASL {B}ody frame is the IMU
  //{D}evice frame is the left camera
  Eigen::Matrix4d d_t_cam0 = Eigen::Matrix4d::Identity();
  Eigen::Matrix4d d_t_b = d_t_cam0 * b_t_c0.inverse();
  Eigen::Matrix4d d_t_cam1 = d_t_b * b_t_c1;
  Eigen::Matrix4d d_t_imu = d_t_b * b_t_i;
  calib_param.Camera.D_T_C_lr[0] = Eigen::Matrix4f::Identity();
  calib_param.Camera.D_T_C_lr[1] = d_t_cam1.cast<float>();
  //Image size
  std::vector<int> v_int = cam0_calib["resolution"].as<std::vector<int>>();
  calib_param.Camera.img_size = cv::Size(v_int[0], v_int[1]);
  // //IMU
  calib_param.Imu.accel_TK = Eigen::Matrix3f::Identity();
  calib_param.Imu.accel_bias = Eigen::Vector3f::Zero();
  calib_param.Imu.gyro_TK = Eigen::Matrix3f::Identity();
  calib_param.Imu.gyro_bias = Eigen::Vector3f::Zero();
  calib_param.Imu.accel_noise_var = Eigen::Vector3f{0.0016, 0.0016, 0.0016};
  calib_param.Imu.angv_noise_var = Eigen::Vector3f{0.0001, 0.0001, 0.0001};
  calib_param.Imu.D_T_I = d_t_imu.cast<float>();
  calib_param.device_id = "ASL";
  calib_param.sensor_type = XP::DuoCalibParam::SensorType::UNKNOWN;

  // ! 第二个段错误
  calib_param.initUndistortMap(calib_param.Camera.img_size);
}




int main(int argc, char** argv) {

  std::cout<<"AAAAAAA"<<std::endl;
}

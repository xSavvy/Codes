/*
 * @Author: Liu Weilong
 * @Date: 2021-01-15 07:00:51
<<<<<<< HEAD
 * @LastEditors: Liu Weilong 
 * @LastEditTime: 2021-01-18 09:05:09
=======
 * @LastEditors: Liu Weilong
 * @LastEditTime: 2021-01-18 07:49:02
>>>>>>> 96e839dc1432c23b21200ab7d9ccff3ce78ca4c8
 * @Description:
 *              测试内容
 *              1. 测试颜色的转换          ColorConvert 
 *              2. 显示测试               EnvironmentShow
 *              3. 内参转换               CameraModel
 *              4. Eigen和Mat 的内存转换   EigenToMat   发现只有一行(列)或者方阵 用起来才不会有风险
 */

#include "opencv2/calib3d/calib3d.hpp"

#include "environment_builder.h"
#include "pointcloud_shower.h"
#include "frame_interface.h"
#include "common.h"
#include "camera_model.h"



using namespace slam_demo;
using namespace std;

void ColorConvert()
{
    PangolinPointCloudShower shower_;
    Eigen::Vector3i color(128,128,128);
    Eigen::Vector3i color_converted;
    uint32_t ui32;
    shower_.ColorConvert(color,ui32);
    shower_.ColorConvert(ui32,color_converted);
    cout<<"the origin color is "<< color.transpose()<<endl;
    cout<<"the converted color is "<<color_converted.transpose()<<endl;
}

void EnvironmentShow()
{
    const string config_path= "../config/Environment_H.yaml";
    EnvironmentBuilder eb(config_path);
    Eigen::Vector3i color(255,0,0);
    PangolinPointCloudShower pps;
    pps.LoadPointCloud(color,eb.GetLandmarksVec3d());
    pps.Show();
}

void CameraModel()
{
    const string config_path ="../config/EuRoC.yaml";
    CameraModelPinhole cm(config_path);
    Eigen::Vector3d temp_point(1.0,1.0,2.0);
    Eigen::Vector3d expect_point= temp_point/temp_point.z();
    std::vector<Eigen::Vector3d> vtemppts{temp_point};
    std::vector<Eigen::Vector2d> vuv;
    
    cm.CameraPointsToUVs(vtemppts,vuv);

    cm.UVToCameraPoint(vuv,vtemppts);

    cout<<"the expect result is "<<expect_point.transpose()<<endl;
    cout<<"the result from camera model is "<<vtemppts.front().transpose()<<endl;
}

// void H_matrix()
// {
//     //

//     const string env_path= "../config/Environment_H.yaml";
//     const string camera_path = "../config/EuRoC.yaml";

//     EnvironmentBuilder eb(env_path);
//     auto & lds = eb.GetLandmarksVec3d();
//     vector<Eigen::Vector3d> lds_in_camera;
//     lds_in_camera.reserve(lds.size());
    
//     // 设置初始值
    
//     Eigen::AngleAxisd aa(0.5,Eigen::Vector3d(1,2,3).normalized());
//     Eigen::Vector3d translation(0.4,0.5,0.6);
//     Eigen::Matrix4d transform;
//     transform.setZero();
//     transform.block<3,1>(0,3)= translation;
//     transform.block<3,3>(0,0)= aa.matrix();
//     TransformPoints(lds,transform,lds_in_camera);
    
//     Eigen::Matrix3d h;

//     CameraModelPinhole cm(camera_path);
    
//     std::vector<Eigen::Vector2d> uvs_world,uvs_camera;
//     cm.CameraPointsToUVs(lds,uvs_world);
//     cm.CameraPointsToUVs(lds_in_camera,uvs_camera);

//     cv::findHomography()

// }

void EigenToMat()
{
    Eigen::Matrix<double,6,5> temp_eigen;
    temp_eigen.setZero();
    temp_eigen.block<6,1>(0,4) = (Eigen::Matrix<double,6,1>()<<1,2,3,4,5,6).finished();
    cout<<"the matrix eigen is "<<endl<<temp_eigen<<endl;
    cv::Mat temp_cv(6,5,CV_64F);
    std::memcpy(temp_cv.data,temp_eigen.data(),temp_eigen.rows()*temp_eigen.cols()*8);
    cout<<"the matrix cv is "<<endl<<temp_cv.t()<<endl;
}

int main()
{
EigenToMat();
    


}

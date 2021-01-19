/*
 * @Author: Liu Weilong
 * @Date: 2021-01-15 07:00:51
 * @Description:
 *              测试内容
 *              1. 测试颜色的转换          ColorConvert 
 *              2. 显示测试               EnvironmentShow
 *              3. 内参转换               CameraModel
 *              4. Eigen和Mat 的内存转换   EigenToMat   发现只有一行(列)或者方阵 用起来才不会有风险
 *              5. 单应矩阵结算            H_matrix     验证平面 验证旋转
 */

#include "opencv2/calib3d/calib3d.hpp"

#include "environment_builder.h"
#include "pointcloud_shower.h"
#include "frame_interface.h"
#include "common.h"
#include "camera_model.h"
#include "convert.h"


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

void PnP()
{
    
}

void H_matrix()
{
    // 配置环境

    const string env_path= "../config/Environment_H.yaml";
    const string camera_path = "../config/EuRoC.yaml";

    EnvironmentBuilder eb(env_path);
    auto & lds = eb.GetLandmarksVec3d();
    vector<Eigen::Vector3d> lds_in_camera;
    lds_in_camera.reserve(lds.size());
    
    // 设置初始值
    
    Eigen::AngleAxisd aa(0.5,Eigen::Vector3d(1,2,3).normalized());
    Eigen::Vector3d translation(0.4,0.5,0.6);
    Eigen::Matrix4d transform;
    transform.setZero();
    transform.block<3,1>(0,3)= translation;
    transform.block<3,3>(0,0)= aa.matrix();
    TransformPoints(lds,transform,lds_in_camera);
    
    Eigen::Matrix3d h;

    CameraModelPinhole cm(camera_path);
    
    std::vector<Eigen::Vector2d> uvs_world,uvs_camera;
    
    // 去掉第一个0,0,0 的ld
    lds.erase(lds.begin());
    lds_in_camera.erase(lds_in_camera.begin());

    cm.CameraPointsToUVs(lds,uvs_world);
    cm.CameraPointsToUVs(lds_in_camera,uvs_camera);

    std::vector<cv::Point2f> uvs_cv_world{cv::Point2f(0.0,0.0),cv::Point2f(1.0,0.0),
                                          cv::Point2f(1.0,1.0),cv::Point2f(0.0,1.0)};
    std::vector<cv::Point2f> uvs_cv_camera{cv::Point2f(0.0,0.0),cv::Point2f(1.0,0.0),
                                           cv::Point2f(2.0,3.0),cv::Point2f(0.0,2.0)};

    auto H_cv = cv::findHomography(uvs_cv_world,uvs_cv_camera);
    cout<<"the H from opencv is "<<endl<<H_cv<<endl;

    auto temp = Converter::toVector2ds(uvs_cv_camera);

    // FrameInterface::EpipolarH4Pts(Converter::toVector2ds(uvs_cv_camera),
    //                               Converter::toVector2ds(uvs_cv_world),h);
    
    cout<<"the H from the frame interface is "<< endl<<h<<endl;

}

void EigenToMat()
{
    Eigen::Matrix<double,6,5> temp_eigen;
    temp_eigen.setZero();
    temp_eigen.block<6,1>(0,4) = (Eigen::Matrix<double,6,1>()<<1,2,3,4,5,6).finished();
    cout<<"the matrix eigen is "<<endl<<temp_eigen<<endl;
    
    auto temp_mat = Converter::toMat(temp_eigen);
    cout<<"the matrix cv is "<<endl<<temp_mat<<endl;

    std::vector<Eigen::Matrix<double,6,5>,Eigen::aligned_allocator<Eigen::Matrix<double,6,5>>> veigen;
    veigen.push_back(temp_eigen);
    veigen.push_back(temp_eigen*5);
    
    auto vtemp = Converter::toMats(veigen);
    
    for(auto & temp:vtemp)
    {
        cout<<"==========="<<endl;
        cout<<temp<<endl;
    }
}

int main()
{
    H_matrix();

}

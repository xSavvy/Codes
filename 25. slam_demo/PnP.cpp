/*
 * @Author: Liu Weilong
 * @Date: 2020-11-17 16:56:39
 * @LastEditors: Liu Weilong 
 * @LastEditTime: 2020-11-19 16:46:23
 * @FilePath: /3rd-test-learning/25. slam_demo/PnP.cpp
 * @Description: PnP 实现 
 *                   |__ 大规模优化
 *                   |__ P3P
 *                   |__ 三角测量      三角化还是有BUG
 */

#include <iostream>
#include "build_test_environment.h"
#include "sophus/so3.hpp"
using namespace std;



// 2D 和 2D 对应关系已知， 两个Frame 的关系已知，从中恢复深度
// 直接使用SVD 进行求解
void Triangulate(const Landmark & l1,const Landmark & l2,
                 Eigen::Matrix3d & rotation1,Eigen::Vector3d& translation1,
                 Eigen::Matrix3d & rotation2,Eigen::Vector3d& translation2)
{
    auto p1 = l1.position_.normalized();
    auto p2 = l2.position_.normalized();
    
    Eigen::Matrix4d transform1,transform2;
    transform1.block(0,0,3,3) = rotation1;
    transform1.block(0,3,3,1) = translation1;
    transform2.block(0,0,3,3) = rotation2;
    transform2.block(0,3,3,1) = translation2;

    Eigen::Matrix4d svd_source;
    svd_source.row(0) = p1.x()*transform1.row(2) - transform1.row(1);
    svd_source.row(1) = p1.y()*transform1.row(2) - transform1.row(0);
    svd_source.row(2) = p2.x()*transform2.row(2) - transform2.row(1);
    svd_source.row(3) = p2.y()*transform2.row(2) - transform2.row(0);

    Eigen::JacobiSVD<Eigen::Matrix4d> svd(svd_source,Eigen::ComputeFullV | Eigen::ComputeFullU);
    auto V = svd.matrixV();
    
    cout<<"the real point is "<<endl
        <<l1.position_.transpose()<<endl;
    cout<<"the estimation point is "<<endl
        << V.col(3).transpose()<<endl;
}


void TriangulateTwoFrame(const std::vector<Landmark> & vlandmarkInCamera1, 
                         const std::vector<Landmark> & vlandmarkInCamera2,
                         Eigen::Matrix3d &rotation1,Eigen::Vector3d & translation1,
                         Eigen::Matrix3d &rotation2,Eigen::Vector3d & translation2)
{
    for(auto & landmark1:vlandmarkInCamera1)
    {
        for(auto & landmark2:vlandmarkInCamera2)
        {
            if(landmark1.label_ == landmark2.label_)
            {
                Triangulate(landmark1,landmark2,
                            rotation1,translation1,
                            rotation2,translation2);
            }
        }
    }
}


int main()
{
    float x_min =0,y_min=0,z_min=0;
    float x_scale = 10,y_scale=10,z_scale=10;
    float x_interval=4,y_interval =4,z_interval=4;
    std::vector<Landmark> vLandmark;
    
    buildEnvironment(x_min,y_min,z_min,x_scale,y_scale,z_scale,x_interval,y_interval,z_interval,vLandmark);

    float hfov=120.0/180.0*M_PI/2.0,vfov = 75.0/180.0*M_PI/2.0;    
    std::vector<Landmark> vlandkInCamera;
    std::vector<unsigned int> vindex;
    Eigen::Matrix3d rotation1 = Eigen::Matrix3d::Identity();
    Eigen::Vector3d translation1 = Eigen::Vector3d::Ones()*3;
    findPointInCamera(hfov,vfov,vLandmark,rotation1,translation1,&vlandkInCamera,vindex);
    cout<<"print landmark in camera"<<endl;
    for(auto & landmark:vlandkInCamera)
    {
        cout<<landmark.position_(0)<<"  "<<landmark.position_(1)<<"  "<<landmark.position_(2)<<endl;
    }
    std::vector<Landmark> vlandkInCamera2;
    std::vector<unsigned int> vindex2;
    Eigen::AngleAxisd angle_axis(0.3,Eigen::Vector3d(0,0,1.0));
    Eigen::Matrix3d rotation2 = angle_axis.matrix();
    Eigen::Vector3d translation2 = Eigen::Vector3d::Zero();
    findPointInCamera(hfov,vfov,vLandmark,rotation2,translation2,&vlandkInCamera2,vindex2);

    TriangulateTwoFrame(vlandkInCamera,vlandkInCamera2,
                        rotation1,translation1,
                        rotation2,translation2);

}

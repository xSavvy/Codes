/*
 * @Author: Liu Weilong
 * @Date: 2020-11-17 16:56:39
 * @LastEditors: Liu Weilong 
 * @LastEditTime: 2020-11-17 17:32:53
 * @FilePath: /3rd-test-learning/25. slam_demo/PnP.cpp
 * @Description: PnP 实现 
 *                   |__ 大规模优化
 *                   |__ P3P
 *                   |__ 三角测量
 */

#include <iostream>
#include "build_test_environment.h"
#include "sophus/so3.hpp"
using namespace std;

void TriangulateTwoFrame(const std::vector<Landmark> & vlandmarkInCamera1, 
                         const std::vector<Landmark> & vlandmarkInCamera2,
                         Eigen::Matrix3d &rotation,Eigen::Vector3d & translation)
{
    
}


// 2D 和 2D 对应关系已知， 两个Frame 的关系已知，从中恢复深度
// 直接使用SVD 进行求解
void Triangulate(const Landmark & l1,const Landmark & l2,
                 Eigen::Matrix3d & rotation1,Eigen::Vector3d& translation1,
                 Eigen::Matrix3d & rotation2,Eigen::Vector3d& translation2)
{
    auto p1 = l1.position_.normalized();
    auto p2 = l2.position_.normalized();
    
    Eigen::Matrix4d transform1,transform2;
    transform1<<rotation1,translation1;
    transform2<<rotation2,translation2;

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
    findPointInCamera(hfov,vfov,vLandmark,Eigen::Matrix3d::Identity(),Eigen::Vector3d::Ones()*3,&vlandkInCamera,vindex);
    cout<<"print landmark in camera"<<endl;
    for(auto & landmark:vlandkInCamera)
    {
        cout<<landmark.position_(0)<<"  "<<landmark.position_(1)<<"  "<<landmark.position_(2)<<endl;
    }
}

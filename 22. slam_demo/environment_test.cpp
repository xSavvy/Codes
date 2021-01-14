/*
 * @Author: Liu Weilong
 * @Date: 2020-11-17 15:24:47
 * @LastEditors: Liu Weilong 
 * @LastEditTime: 2020-11-17 16:41:54
 * @FilePath: /3rd-test-learning/25. slam_demo/environment_test.cpp
 * @Description: 用于测试建立起来测试环境
 */
#include "build_test_environment.h"
#include <iostream>
#include <vector>
using namespace std;

int main()
{
    float x_min =0,y_min=0,z_min=0;
    float x_scale = 10,y_scale=10,z_scale=10;
    float x_interval=4,y_interval =4,z_interval=4;
    std::vector<Landmark> vLandmark;
    
    buildEnvironment(x_min,y_min,z_min,x_scale,y_scale,z_scale,x_interval,y_interval,z_interval,vLandmark);

    // cout<<"the size of landmark is "<< vLandmark.size()<<endl;
    cout<<" print all landmark"<<endl;
    for(auto & landmark:vLandmark)
    {
        cout<<landmark.position_(0)<<"  "<<landmark.position_(1)<<"  "<<landmark.position_(2)<<endl;
    }
    
    float hfov=120.0/180.0*M_PI/2.0,vfov = 75.0/180.0*M_PI/2.0;
    
    std::vector<Landmark> vlandkInCamera;
    std::vector<unsigned int> vindex;
    findPointInCamera(hfov,vfov,vLandmark,Eigen::Matrix3d::Identity(),Eigen::Vector3d::Ones()*3,&vlandkInCamera,vindex);
    cout<<"print landmark in camera"<<endl;
    for(auto & landmark:vlandkInCamera)
    {
        cout<<landmark.position_(0)<<"  "<<landmark.position_(1)<<"  "<<landmark.position_(2)<<endl;
    }

    


    return 0;
}

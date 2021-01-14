/*
 * @Author: Liu Weilong
 * @Date: 2021-01-13 22:41:49
 * @LastEditors: Liu Weilong
 * @LastEditTime: 2021-01-13 23:14:09
 * @Description: 
 */

#include "environment_builder.h"

_S_SLAM_DEMO_

bool EnvironmentBuilder::BuildEnvironment(double x_min,double y_min,double z_min ,
                                          double x_scale, double y_scale, double z_scale ,
                                          double x_interval,double y_interval,double z_interval,
                                          std::vector<Landmark,Eigen::aligned_allocator<Landmark>> &landmark_array)
{
    if(x_scale<0||y_scale<0 || z_scale<0)
    {
        std::cout<<" the scale should be positive"<<std::endl;
        return false;
    }
    unsigned int count =0;
    landmark_array.clear();
    landmark_array.reserve(static_cast<size_t>(std::ceil(x_scale/x_interval))*
                           static_cast<size_t>(std::ceil(y_scale/y_interval))*
                           static_cast<size_t>(std::ceil(z_scale/z_interval)));
    for(double x_cur = 0.0;x_cur<x_scale;x_cur+=x_interval)
    {
        for(double y_cur = 0.0;y_cur<y_scale;y_cur+=y_interval)
        {
            for(double z_cur=0.0;z_cur<z_scale;z_cur+=z_interval)
            {
                Landmark tmp_lk;
                tmp_lk.position_ = Eigen::Vector3d(x_cur+x_min,y_cur+y_min,z_cur+z_min);
                tmp_lk.label_ = count;
                landmark_array.push_back(tmp_lk);
                count++;
            }
        }
    }

    return true;
}

bool TransformPoints(const std::vector<Eigen::Vector3d> & points_world,
                     const Eigen::Matrix4d & Twc,
                     std::vector<Eigen::Vector3d> & points_camera)
{
    points_camera.clear();
    points_camera.reserve(points_world.size());
    const Eigen::Matrix3d R = Twc.block<3,3>(0,0);
    const Eigen::Vector3d t = Twc.block<3,1>(0,3);
    for(auto & point_world:points_world)
        points_camera.push_back(R*point_world+t);
    return true;
}


bool NormalizePoints(const std::vector<Eigen::Vector3d> & points_camera,
                     std::vector<Eigen::Vector3d> & normalized_points)
{
    normalized_points.clear();
    normalized_points.reserve(points_camera.size());
    for(auto & point:points_camera)
        normalized_points.emplace_back(point/point.z());
    return true;
}

bool CameraPointToUV(const std::vector<Eigen::Vector3d> & points_camera,
                     const Eigen::Matrix3d & camera_intrinsic,
                     std::vector<Eigen::Vector2d> & uvs)
{
    uvs.clear();
    uvs.reserve(points_camera.size());
    for(auto & point_camera:points_camera)
        uvs.emplace_back((camera_intrinsic*point_camera).head<2>(0));
    return true;
}

bool UVToCameraPoint(const std::vector<Eigen::Vector2d> & uvs,
                     const Eigen::Matrix3d & camera_intrinsic,
                     std::vector<Eigen::Vector3d> & points_camera)
{
    double fx,fy,cx,cy;

    fx = camera_intrinsic(0,0);
    fy = camera_intrinsic(1,1);
    cx = camera_intrinsic(0,2);
    cy = camera_intrinsic(1,2);

    points_camera.clear();
    points_camera.reserve(uvs.size());
    
    for(auto & uv:uvs)
        points_camera.emplace_back((uv.x()-cx)/fx,(uv.y()-cy)/fy,1.0);

    return true;
}


_E_SLAM_DEMO_
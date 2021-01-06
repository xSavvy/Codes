/*
 * @Author: Liu Weilong
 * @Date: 2021-01-06 11:01:19
 * @LastEditors: Liu Weilong 
 * @LastEditTime: 2021-01-06 17:34:22
 * @FilePath: /3rd-test-learning/9. ros-melodic/src/ros-melodic-test/src/9.6 tf_and_message_self_define.cpp
 * @Description: 用于进行 ros - melodic - tf 的学习
 */
#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>
#include <condition_variable>

#include "opencv2/core/core.hpp"
#include "Eigen/Eigen"
#include "sophus/so3.hpp"

#include "ros/ros.h"
#include "tf2/LinearMath/Quaternion.h"
#include "tf2_ros/transform_broadcaster.h"
#include "geometry_msgs/TransformStamped.h"

#define _S_TF_BROADCASTER_ namespace tf_broadcaster{
#define _E_TF_BROADCASTER_ };

_S_TF_BROADCASTER_

class TfBroadcaster
{
    public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW
    TfBroadcaster(const std::string & frame_id, const std::string & child_frame_id):
    nh_(),frame_id_(frame_id),child_frame_id_(child_frame_id)
    {
        
    }
    
    void RunTF();
    void RunMessage();

    bool SetTransform(const Eigen::Matrix4d & tf);
    bool SetTransform(const Eigen::Vector3d & translation, const Eigen::Matrix3d & rotation);
    bool SetTransform(const Eigen::Vector3d & translation, const Sophus::SO3d & rotation);
    bool SetTransform(const Eigen::Vector3d & translation, const Eigen::Quaterniond & rotation);

    private:

    bool CheckRotation(const Eigen::Matrix3d & rotation)const ;
    void LoadTransfromStamped(geometry_msgs::TransformStamped & tfs) const;
    void LoadVisualOdometryMsg()const;

    private:
    
    ros::NodeHandle nh_;
    ros::Publisher  pose_message_pub_;


    std::string     frame_id_;
    std::string     child_frame_id_;

    Eigen::Vector3d          translation_;
    Sophus::SO3d             rotation_;
    
    mutable std::mutex       transform_lock_;
    mutable std::atomic_bool pose_update_;
    mutable std::condition_variable pose_condition_variable_;
};


void TfBroadcaster::RunTF()
{
    geometry_msgs::TransformStamped tfs;
    while(ros::ok())
    {
        {
            std::unique_lock<std::mutex> locker(transform_lock_);
            pose_condition_variable_.wait(locker,[this]()->bool{return pose_update_ == true;});
            LoadTransfromStamped(tfs);
            static tf2_ros::TransformBroadcaster br;
            br.sendTransform(tfs);
            pose_update_ = false;
        }
    }
}

void TfBroadcaster::RunMessage()
{

}

bool TfBroadcaster::SetTransform(const Eigen::Matrix4d & tf)
{
    std::lock_guard<std::mutex> locker(transform_lock_);
    Eigen::Matrix3d rotation = tf.block<3,3>(0,0);
    Eigen::Vector3d translation = tf.block<3,1>(0,3);
    if(!CheckRotation(rotation))
    {
        std::cout<<"the input transfrom does not have a rotation matrix !"<<std::endl;
        return false;
    }
    Eigen::AngleAxisd aa(rotation);
    rotation_ = Sophus::SO3d::exp(aa.angle()*aa.axis());
    translation_ = translation;
    pose_update_ = true;
    pose_condition_variable_.notify_one();
    return true;
}

bool TfBroadcaster::SetTransform(const Eigen::Vector3d & translation, const Eigen::Matrix3d & rotation)
{
    std::lock_guard<std::mutex> locker(transform_lock_);
    if(!CheckRotation(rotation))
    {
        std::cout<<"the input transfrom does not have a rotation matrix !"<<std::endl;
        return false;
    }
    Eigen::AngleAxisd aa(rotation);
    rotation_ = Sophus::SO3d::exp(aa.angle()*aa.axis());
    translation_ = translation;
    pose_condition_variable_.notify_one();
    return true;
}

bool TfBroadcaster::SetTransform(const Eigen::Vector3d & translation, const Sophus::SO3d & rotation)
{
    std::lock_guard<std::mutex> locker(transform_lock_);
    rotation_ = rotation;
    translation_ = translation;
    pose_condition_variable_.notify_one();
    return true;
}

bool TfBroadcaster::SetTransform(const Eigen::Vector3d & translation, const Eigen::Quaterniond & rotation)
{
    std::lock_guard<std::mutex> locker(transform_lock_);
    Eigen::AngleAxisd aa(rotation);
    rotation_ = Sophus::SO3d::exp(aa.angle()*aa.axis());
    translation_ = translation;
    pose_condition_variable_.notify_one();
    return true;
}

bool TfBroadcaster::CheckRotation(const Eigen::Matrix3d & rotation)const 
{
    double norm = (rotation * rotation.transpose()).determinant();
    if(norm<1.0-1e-3&& norm > 1.0+1e-3)
    return false;
    return true;
}

void TfBroadcaster::LoadTransfromStamped(geometry_msgs::TransformStamped & tfs)const 
{
    tfs.child_frame_id = child_frame_id_;
    tfs.header.stamp = ros::Time::now();
    tfs.header.frame_id = frame_id_;

    // transfer the data type from SO3 to Quaternion
    Eigen::Quaterniond temp_q  = rotation_.unit_quaternion();
    tfs.transform.rotation.w = temp_q.w();
    tfs.transform.rotation.x = temp_q.x();
    tfs.transform.rotation.y = temp_q.y();
    tfs.transform.rotation.z = temp_q.z();
    
    tfs.transform.translation.x = translation_.x();
    tfs.transform.translation.y = translation_.y();
    tfs.transform.translation.z = translation_.z();
}

_E_TF_BROADCASTER_



int main(int argc, char ** argv)
{
    const std::string frame_id = "map2",child_frame_id="camera";
    tf_broadcaster::TfBroadcaster tf_broadcaster_(frame_id,child_frame_id);

    



    return 0;
}
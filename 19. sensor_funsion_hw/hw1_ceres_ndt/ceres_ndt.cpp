/*
 * @Author: Liu Weilong
 * @Date: 2020-10-18 11:31:25
 * @LastEditors: Liu Weilong
 * @LastEditTime: 2020-10-18 16:14:47
 * @Description:  NDT 运行文件
 */
#include "glog/logging.h"
#include "ceres_ndt.h"
#include "pcl/io/pcd_io.h"
#include "pcl/common/transforms.h"
#include "pcl/registration/ndt.h"
#include "filter.hpp"
#include <string>


int main(int argc,char **argv)
{
    FLAGS_alsologtostderr = 1;
    google::InitGoogleLogging(argv[0]);
    

    // ============================= 数值准备 =====================================================================
    pcl::PointCloud<pcl::PointXYZ>::Ptr point_cloud_(new pcl::PointCloud<pcl::PointXYZ>());
    pcl::PointCloud<pcl::PointXYZ>::Ptr transformed_point_cloud_(new pcl::PointCloud<pcl::PointXYZ>());
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr point_cloud_with_color_(new pcl::PointCloud<pcl::PointXYZRGB>());
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr transformed_point_cloud_with_color_(new pcl::PointCloud<pcl::PointXYZRGB>());
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr all_point_cloud_with_color_(new pcl::PointCloud<pcl::PointXYZRGB>());
    std::string pcd_name_ = "/home/lwl/workspace/3rdparty-test-learning/16. pcl/registration/key_frame_0.pcd";
    pcl::io::loadPCDFile(pcd_name_.c_str(),*point_cloud_);

    // 准备变换
    Eigen::AngleAxisf angle_axis(0.05,Eigen::Vector3f(0,0,1));
    Eigen::Vector3f translation_(0.1,0,0);
    Eigen::Matrix4f transform_;
    transform_<<angle_axis.toRotationMatrix(),
                translation_,0,0,0,1;
    
    std::cout<<" the transform matrix is "<< std::endl<< 
    transform_<<std::endl;
    
    // 变换点云
    pcl::transformPointCloud(*point_cloud_,*transformed_point_cloud_,transform_);

    // AssignColorToPointCloud(point_cloud_,point_cloud_with_color_,255,255,255);
    // AssignColorToPointCloud(transformed_point_cloud_,transformed_point_cloud_with_color_,0,255,0);
    
    *all_point_cloud_with_color_ = *point_cloud_with_color_ + *transformed_point_cloud_with_color_;
  
    // SimpleShow(all_point_cloud_with_color_);

    std::cout<<"the size of point cloud is "<<point_cloud_->size()<<std::endl;

    // ======================================= VoxelFilter 实验 ============================================

    VoxelFilter(point_cloud_,point_cloud_,0.6);
    VoxelFilter(transformed_point_cloud_,transformed_point_cloud_,0.6);

    std::cout<<"the size of point cloud is "<<point_cloud_->size()<<std::endl;

    // ======================================= Ceres NDT 实验 =============================================

    NDTProblem ndt_problem;
    ndt_problem.setResolution(1);
    ndt_problem.setInputTarget(transformed_point_cloud_);
    ndt_problem.setInputSource(point_cloud_);

    Eigen::Matrix4f result;
    ndt_problem.buildProlemAndSolve(result,result);

    // ======================================= PCL NDT 实验 =================================================
    Eigen::Matrix4f result_;
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_source_registered_ (new pcl::PointCloud<pcl::PointXYZ>());
    pcl::NormalDistributionsTransform<pcl::PointXYZ,pcl::PointXYZ> ndt_;
    ndt_.setResolution(1);
    ndt_.setMaximumIterations(20);
    ndt_.setStepSize(0.1);
    ndt_.setTransformationEpsilon(0.01);
    ndt_.setInputTarget(point_cloud_);
    ndt_.setInputSource(transformed_point_cloud_);
    ndt_.align(*cloud_source_registered_);
    result_ = ndt_.getFinalTransformation();
    std::cout<< " the NDT result transform is "<<std::endl<<
    result_<<std::endl;

}

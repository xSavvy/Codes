/*
 * @Author: Liu Weilong
 * @Date: 2020-10-17 21:41:02
 * @LastEditors: Liu Weilong
 * @LastEditTime: 2020-10-18 17:58:17
 * @Description:  基于ceres 的ndt 算法
 *                基于 translation 和 rotation的方式好像不太行
 */
#include <iostream>
#include <vector>
#include "Eigen/Eigen"
#include "sophus/so3.hpp"
#include "sophus/se3.hpp"
#include "glog/logging.h"
#include "ceres/ceres.h"
#include "pcl/filters/voxel_grid_covariance.h"

class NDTCostFunctorNumerical
{
    public:

    NDTCostFunctorNumerical(const Eigen::Matrix3d & covar, 
                            const Eigen::Vector3d & mean,
                            const Eigen::Vector3d & point):
                            mean_(mean),point_(point)
    {
        Eigen::LLT<Eigen::Matrix3d> llt_of_covar(covar);
        l_matrix_ = llt_of_covar.matrixL();
        // LOG(INFO)<<"A  cost function is built"<<std::endl;
    }
    
    bool operator()(const double* lie, double* resiudal)const
    {
        Eigen::Map<Eigen::Matrix<double,3,1>> residual_map(resiudal);
        Eigen::Map<const Eigen::Matrix<double,6,1>> lie_map(lie);
        Sophus::SE3<double> se3_ = Sophus::SE3<double>::exp(lie_map);
        residual_map = se3_*point_ -mean_;
        residual_map = l_matrix_*residual_map;
        
        return true;
    }
    
    private:

    Eigen::Vector3d mean_;
    Eigen::Vector3d point_;
    Eigen::Matrix3d l_matrix_;
};

class SE3LocalParam :public ceres::LocalParameterization
{
    public:

    virtual bool Plus(const double* x,
                    const double* delta,
                    double* x_plus_delta) const 
    {
        Eigen::Map<const Eigen::Matrix<double,6,1>> lie(x);
        Eigen::Map<const Eigen::Matrix<double,6,1>> delta_lie(delta);
        Eigen::Map<Eigen::Matrix<double,6,1>> new_lie(x_plus_delta);
        Sophus::SE3<double> so3_rotation = Sophus::SE3<double>::exp(lie);
        Sophus::SE3<double> so3_delta_rotation = Sophus::SE3<double>::exp(delta_lie);
        
        auto result = so3_delta_rotation*so3_rotation;
        
        new_lie = result.log();

        return true;
    }

    virtual bool ComputeJacobian(const double* x, double* jacobian) const
    {
        ceres::MatrixRef(jacobian, 6, 6) = ceres::Matrix::Identity(6, 6);
        return true;
    }

    virtual int GlobalSize() const { return 6; }
    virtual int LocalSize() const { return 6; }
};

class NDTCostFunctionWrapper
{
    public:

    NDTCostFunctionWrapper(const Eigen::Matrix3d & covar, 
                           const Eigen::Vector3d & mean,
                           const Eigen::Vector3d & point )
    {
        nolinear_equation_.reset(new ceres::CostFunctionToFunctor<3,6>(
            new ceres::NumericDiffCostFunction<NDTCostFunctorNumerical,ceres::CENTRAL,3,6>(
                new NDTCostFunctorNumerical(covar,mean,point))));
    }


    template<typename T>
    bool operator()(const T* lie,T*residual)const
    {
        (*nolinear_equation_)(lie,residual);
        return true;
    }


    private:
    std::unique_ptr<ceres::CostFunctionToFunctor<3,6>> nolinear_equation_;
};

class NDTProblem
{
    public:
    
    void setInputSource(const pcl::PointCloud<pcl::PointXYZ>::ConstPtr cloud);

    void setInputTarget(const pcl::PointCloud<pcl::PointXYZ>::ConstPtr cloud);

    void setResolution(double voxel_size){
        leaf_size_ = voxel_size;
        resolution_ = voxel_size;
    }
    
    void setRadius(double radius){

    }

    void buildProlemAndSolve(Eigen::Matrix4f & result, const Eigen::Matrix4f predict_pose);

    void buildProlemAndSolve(Eigen::Matrix4f & result, const Eigen::Matrix<double,6,1> predict_pose) =delete;

    private:
    pcl::VoxelGridCovariance<pcl::PointXYZ> voxel_covar_;
    pcl::PointCloud<pcl::PointXYZ>::ConstPtr source_point_cloud_;
    pcl::PointCloud<pcl::PointXYZ>::ConstPtr target_point_cloud_;
    double leaf_size_;
    double radius_;
    double resolution_;
};

void NDTProblem::setInputSource(const pcl::PointCloud<pcl::PointXYZ>::ConstPtr cloud)
{
    source_point_cloud_ = cloud;
}

void NDTProblem::setInputTarget(const pcl::PointCloud<pcl::PointXYZ>::ConstPtr cloud)
{
    target_point_cloud_ = cloud;
    voxel_covar_.setLeafSize(resolution_,resolution_,resolution_);
    voxel_covar_.setInputCloud(target_point_cloud_);
    voxel_covar_.filter(true);
}

void NDTProblem::buildProlemAndSolve(Eigen::Matrix4f & result, const Eigen::Matrix4f predict_pose)
{
    

    if(source_point_cloud_ == nullptr ||target_point_cloud_ == nullptr
       ||source_point_cloud_->empty()||target_point_cloud_->empty())
       {
           return;
       }
    
    ceres::Problem problem;

    double lie [6] = {0,0,0,0,0,0};
    
    for(auto & point:source_point_cloud_->points)
    {
        Eigen::Vector3d point_v3;
        point_v3<<point.x,point.y,point.z;
        std::vector<pcl::VoxelGridCovariance<pcl::PointXYZ>::LeafConstPtr> k_leaves;
        std::vector<float> distancess;
        voxel_covar_.radiusSearch(point,resolution_,k_leaves,distancess);
        // LOG(INFO)<<"the size of k_leaves is "<<k_leaves.size()<<std::endl;
        for (auto leaf:k_leaves)
        {
            // LOG(INFO)<<leaf->getPointCount()<<std::endl;
            ceres::CostFunction * cf = new ceres::AutoDiffCostFunction<NDTCostFunctionWrapper,3,6>(
                                        new NDTCostFunctionWrapper(leaf->cov_,leaf->mean_,point_v3));
            problem.AddResidualBlock(cf,new ceres::CauchyLoss(0.5),lie);
        }
    }

    problem.SetParameterization(lie,new SE3LocalParam());

    ceres::Solver::Options options;
    ceres::Solver::Summary summary;
    options.linear_solver_type = ceres::DENSE_QR;
    options.minimizer_type = ceres::TRUST_REGION;
    options.trust_region_strategy_type = ceres::LEVENBERG_MARQUARDT;

    ceres::Solve(options,&problem,&summary);

    std::cout<<summary.BriefReport()<<std::endl;

    Eigen::Map<Eigen::Matrix<double,6,1>> lie_map(lie);
    std::cout<<"the esitmation transform is "<<std::endl<<Sophus::SE3<double>::exp(lie_map).matrix3x4()<<std::endl;   
}


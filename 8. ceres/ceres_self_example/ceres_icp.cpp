/*
 * @Author: Liu Weilong
 * @Date: 2020-10-26 07:16:54
 * @LastEditors: Liu Weilong
 * @LastEditTime: 2020-10-29 08:09:51
 * @Description: 主要是为了测试和学习LocalParameter 
 * 
 *               ie.1   Auto Diff SE3 上的优化
 *               ie.2   Analystic Diff SE3 上的优化
 */

#include <vector>
#include <iostream>
#include <random>

#include <ceres/ceres.h>
#include <sophus/se3.hpp>
#include <sophus/so3.hpp>
#include <Eigen/Eigen>
#include <g2o/stuff/sampler.h>

using namespace std;

std::vector<Eigen::Vector4d> point_cloud;

void buildPointCloud()
{
    for(int i = 0;i<30;i++)
    {
        Eigen::Vector4d tmp_point;
        tmp_point<< i * 0.3,i*0.3,i*0.3,1;
        point_cloud.push_back(tmp_point);
    }

    for(int i = 0;i<30;i++)
    {
        Eigen::Vector4d tmp_point;
        tmp_point<< 0.5,i*0.3 + i* 0.02,i*0.3,1;
        point_cloud.push_back(tmp_point);
    }
    
    for(int i = 0;i<30;i++)
    {
        Eigen::Vector4d tmp_point;
        tmp_point<< 0.9,i*0.3 + i* 0.04,i*0.3 - i*0.01,1;
        point_cloud.push_back(tmp_point);
    }    
}

bool transformPointCloud(const Sophus::SE3d & pose_camera_to_world, 
                         const vector<Eigen::Vector4d> & points_in_world,
                         vector<Eigen::Vector4d> & points_in_camera)
{
    if(points_in_world.size() == 0)
    {
        std::cout<<"[Bad Data]: the size of point array is 0.Thus return false!"<<std::endl;
        return false;
    }
    
    Eigen::Matrix4d pose_world_to_camera = pose_camera_to_world.matrix().inverse();
    points_in_camera.clear();
    points_in_camera.reserve(points_in_world.size());

    for(const auto & point:points_in_world)
    {
        Eigen::Vector4d tmp_point = pose_world_to_camera * point;
        points_in_camera.push_back(tmp_point);
    }
}

// 这里使用高斯分布的误差(0,1) 高斯分布
// TODO 这里的参数可以进行调节，如果出问题可以注意这里
bool AddNoise(std::vector<Eigen::Vector4d> & point_cloud)
{
    // scale 再大基本就挂了  因为点在设置的时候就比较密集
    double scale = 0.001;
    Eigen::Matrix3d covar = Eigen::Matrix3d::Identity()*scale;
    g2o::GaussianSampler<Eigen::Matrix<double,3,1>,Eigen::Matrix<double,3,3>> sampler;
    sampler.setDistribution(covar);
    for(auto & point :point_cloud)
    {
        Eigen::Vector4d noise;
        noise<<sampler.generateSample(),0;
        cout<<"the noise is "<<noise.transpose()<<endl;
        point = point + noise;
    }
}


class AnalyticCostFunction:public ceres::SizedCostFunction<3,6>
{
    public:
    AnalyticCostFunction(const Eigen::Vector3d watched_point, const Eigen::Vector3d point_in_world):
                         watched_point_(watched_point),point_in_world_(point_in_world){}

    virtual bool Evaluate(double const * const * params,
                          double * residuals,
                          double **jacobians)const
    {
        Eigen::Map<Eigen::Matrix<double,3,1>> residual_map(residuals);
        Eigen::Map<const Eigen::Matrix<double,6,1>> lie_map(params[0]);
        // cout<<" the params is "<<lie_map.transpose()<<endl;
        Sophus::SE3<double> se3 = Sophus::SE3<double>::exp(lie_map);
        
        residual_map = se3*watched_point_ -point_in_world_;

        if (!jacobians) return true;
        double* jacobian = jacobians[0];
        if (!jacobian) return true;
        
        // 这里不使用Sophus 的SE3 求导
        // 因为Sophus的SE3 是四元数 + 位姿的一个组合

        Eigen::Map<Eigen::Matrix<double,3,6>> jacobian_map(jacobians[0]);
        
        Eigen::Matrix<double,4,6> point_jing = Eigen::Matrix<double,4,6>::Zero();

        // auto t_p = se3 * watched_point_;

        point_jing.block(0,0,3,3) = Eigen::Matrix<double,3,3>::Identity();

        point_jing.block(0,3,3,3) = -1*Sophus::SO3<double>::hat(watched_point_);
        
        auto result_4_6 = se3.matrix()*point_jing;
        
        auto jac = result_4_6.block(0,0,3,6);

        int count =0;
        for(int i = 0;i<3;i++)
        {
            for(int j =0;j<6;j++)
            {
                jacobian[count] = result_4_6(i,j);
                count++;
            }
        }
        return true;    
    }
    
    private:
    Eigen::Vector3d watched_point_;
    Eigen::Vector3d point_in_world_;
};

class SE3LocalParameterizaton:public ceres::LocalParameterization
{
    virtual bool Plus(const double* x,
                const double* delta,
                double* x_plus_delta) const 
    {
        
        Eigen::Map<const Eigen::Matrix<double,6,1>> lie(x);
        Eigen::Map<const Eigen::Matrix<double,6,1>> delta_lie(delta);
        // cout<< "show the delta"<< delta_lie.transpose()<<endl;
        Eigen::Map<Eigen::Matrix<double,6,1>> new_lie(x_plus_delta);
        Sophus::SE3<double> so3_rotation = Sophus::SE3<double>::exp(lie);
        Sophus::SE3<double> so3_delta_rotation = Sophus::SE3<double>::exp(delta_lie);
        
        auto result = so3_rotation*so3_delta_rotation;
        
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


int main()
{
    buildPointCloud();
    Eigen::Matrix4d transform = Eigen::Matrix4d::Identity();
    const double initial_lie [6] {0.4,0.6,0.7,0.6,0.7,0.8};
    Eigen::Map<const Eigen::Matrix<double,6,1>> k_lie(initial_lie);
    Sophus::SE3<double> se3 = Sophus::SE3d::exp(k_lie);
    std::vector<Eigen::Vector4d> point_in_camera;
    transformPointCloud(se3,point_cloud,point_in_camera);
    AddNoise(point_in_camera);

    cout<<" show the transform matrix from SE3"<<endl
        <<se3.matrix()<<endl;
    
    assert(point_in_camera.front()(3) == 1);
    assert(point_in_camera.back()(3) == 1);    

    ceres::Problem problem;
    double lie [6] {0.44,0.65,0.72,0.55,0.73,0.86};

    Eigen::Map<Sophus::SE3d> show_lie(lie);
    
    cout<<" the right SE3 is "<<endl
        << show_lie.matrix()<<endl;
    // 现在这么看的的确是节省了一些添加 LocalParameterization 的代码
    problem.AddParameterBlock(lie,6,new SE3LocalParameterizaton());
    for(int i = 0; i<point_in_camera.size();i++)
    {
        ceres::CostFunction * cf = new AnalyticCostFunction(point_in_camera[i].segment(0,3),point_cloud[i].segment(0,3));
        problem.AddResidualBlock(cf,new ceres::CauchyLoss(0.5),lie);       
    }
   

    ceres::Solver::Options options;
    ceres::Solver::Summary summary;
    options.linear_solver_type = ceres::DENSE_QR;
    options.minimizer_type = ceres::TRUST_REGION;
    options.trust_region_strategy_type = ceres::DOGLEG;
    options.minimizer_progress_to_stdout = true;

    // 这个Solve 和那个不能用的solve 看起来还是有区分度的
    ceres::Solve(options,&problem,&summary);
    Eigen::Map<Eigen::Matrix<double,6,1>> lie_map(lie);
    cout<<summary.BriefReport()<<endl;
    cout<<"the initial lie is "<< k_lie.transpose()<<endl
        <<"the result lie is "<< lie_map.transpose()<<endl;
    
    

};

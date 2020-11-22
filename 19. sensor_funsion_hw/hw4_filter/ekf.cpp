/*
 * @Author: Liu Weilong
 * @Date: 2020-11-18 07:49:24
 * @LastEditors: Liu Weilong
 * @LastEditTime: 2020-11-22 10:28:47
 * @Description: 
 */
#include "ekf.h"

void EKF::addImuMeasurement(const cv::Point3f &acceleration, const cv::Point3f &angVel, const float &dt)
{
    imu_preintegrated_.IntegrateNewMeasurement(acceleration,angVel,dt);
}

void EKF::addLaserMeasurement(Eigen::Vector3d delta_rotation, Eigen::Vector3d delta_translation)
{
    // 构建优化
    buildProblem(delta_rotation,delta_translation);
    // 更新IMU
    Update();
}

auto EKF::getResult()const
{
    return make_pair(cur_state_.block(0,0,3,1),cur_state_.block(6,0,3,1));
}

void EKF::buildProblem(Eigen::Vector3d delta_rotation_measure, Eigen::Vector3d delta_translation_measure)
{
    ceres::Problem problem;
    problem.AddParameterBlock(cur_state_.data(),3,new SO3PlusOnlyLocalParameterization());
    problem.AddParameterBlock(cur_state_.data()+6,3);
    auto cf1 = EKFObserError::Create(laser_meassurement_covar_,delta_rotation_measure,delta_translation_measure);
    problem.AddResidualBlock(cf1,NULL,cur_state_.data(),cur_state_.data()+6);
    
    Eigen::Matrix<double,15,15> whole_covar = cur_covar_ + IMU::TypeTransform(imu_preintegrated_.C);
    auto cf2 = EKFPredictError::Create(&imu_preintegrated_,whole_covar);
    problem.AddResidualBlock(cf2,NULL,cur_state_.data(),cur_state_.data()+3,
                                      cur_state_.data()+6,cur_state_.data()+9,
                                      cur_state_.data()+12);
    
    ceres::Solver::Options options;
    ceres::Solver::Summary summary;
    options.linear_solver_type = ceres::DENSE_QR;
    options.minimizer_type = ceres::TRUST_REGION;
    options.trust_region_strategy_type = ceres::LEVENBERG_MARQUARDT;
    
    options.max_num_iterations = 3;
    options.function_tolerance = 1e-3;

    // 这个Solve 和那个不能用的solve 看起来还是有区分度的
    ceres::Solve(options,&problem,&summary);
    UpdateCovar(problem);
}

void EKF::Update()
{
    // 数值更新
    pre_state_.block(3,0,12,1) += cur_state_.block(3,0,12,1);
    auto pre_SO3 = Sophus::SO3d::exp(pre_state_.block(0,0,3,1));
    auto delta_SO3 = Sophus::SO3d::exp(cur_state_.block(0,0,3,1));
    pre_state_.block(0,0,3,1) = (pre_SO3*delta_SO3).log();

    // IMU bias 更新
    IMU::Bias new_bias(pre_state_(12,0),pre_state_(13,0),pre_state_(14,0),
                       pre_state_(9,0), pre_state_(10,0),pre_state_(11,0));
    imu_preintegrated_.Initialize(new_bias);
}

void EKF::UpdateCovar(ceres::Problem & problem)
{
    
    ceres::Covariance::Options options_covar;
    ceres::Covariance covariance(options_covar);

    vector<pair<const double*, const double*> > covariance_blocks;

    for(int i=0;i<5;i++)
    {
        for(int j=0;j<5;j++)
        {
            covariance_blocks.push_back(make_pair(cur_state_.data()+i*3, cur_state_.data()+j*3));     
        }
    }

    covariance.Compute(covariance_blocks, &problem);

    Eigen::Matrix<double,15,15> covar = Eigen::Matrix<double,15,15>::Zero();
    Eigen::Matrix<double,3,3,Eigen::RowMajor>   element_covar = Eigen::Matrix<double,3,3>::Zero();
    for(int i=0;i<5;i++)
    {
        for(int j=0;j<5;j++)
        {
            covariance.GetCovarianceBlock(cur_state_.data()+i*3, cur_state_.data()+j*3, element_covar.data());
            covar.block(i*3,j*3,3,3)=element_covar;   
        }
    }
    cur_covar_ = element_covar;
}



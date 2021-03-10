/*
 * @Author: Liu Weilong
 * @Date: 2021-03-10 09:28:03
 * @LastEditors: Liu Weilong 
 * @LastEditTime: 2021-03-10 18:21:04
 * @FilePath: /3rd-test-learning/38. line_feature/sim/test_sim.cc
 * @Description: 
 */
#include "ceres_line_cost_function.h"

Camera cm;
Line l;
LinePx l_px;
Camera cm1,cm2,cm3,cm4;
Eigen::AngleAxisd delta_r(0.3,Eigen::Vector3d(0.,0.,1.));
Eigen::AngleAxisd delta_r1(0.3,Eigen::Vector3d(0.,1.,1.));
LinePx l_px1,l_px2,l_px3,l_px4;
cv::Mat img(480,752,CV_8U,255);
cv::Mat img1,img2,img3;


void Init()
{
    cm.T_w_c = Sophus::SE3d::exp(Eigen::Matrix<double,6,1>::Zero());
    l_px.start_px.x() = 380;
    l_px.start_px.y() = 80;
    l_px.end_px.x() = 400;
    l_px.end_px.y() = 300;

    l.start_point = cm.p2c(l_px.start_px,3.0);
    l.end_point = cm.p2c(l_px.end_px,6.0);

    cm1.T_w_c.so3() = Sophus::SO3d::exp(delta_r.angle()*delta_r.axis())*cm.T_w_c.so3();
    cm2.T_w_c.so3() = Sophus::SO3d::exp(delta_r.angle()*delta_r.axis())*cm1.T_w_c.so3();
    cm2.T_w_c.translation() = Eigen::Vector3d(0.3,0.3,0.);
    cm3.T_w_c.so3() = Sophus::SO3d::exp(delta_r1.angle()*delta_r1.axis())*cm1.T_w_c.so3();
    cm4.T_w_c.so3() = Sophus::SO3d::exp(delta_r1.angle()*delta_r1.axis())*cm2.T_w_c.so3();
    cm4.T_w_c.translation() = Eigen::Vector3d(-1.,-2.,0.);

    l_px1.start_px = cm1.c2p(cm1.w2c(l.start_point));
    l_px1.end_px = cm1.c2p(cm1.w2c(l.end_point));
    l_px2.start_px = cm2.c2p(cm2.w2c(l.start_point));
    l_px2.end_px = cm2.c2p(cm2.w2c(l.end_point));


    l_px3.start_px = cm3.c2p(cm3.w2c(l.start_point));
    l_px3.end_px = cm3.c2p(cm3.w2c(l.end_point));
    l_px4.start_px = cm4.c2p(cm4.w2c(l.start_point));
    l_px4.end_px = cm4.c2p(cm4.w2c(l.end_point));

    img1 = img.clone();
    img2 = img.clone();
    img3 = img.clone();

    l_px.Update();l_px1.Update();l_px2.Update();l_px3.Update();l_px4.Update();
}

void testTP()
{
    // 
    Eigen::Matrix<double,6,1> tp;
    tp.block<3,1>(0,0) = l.start_point;
    tp.block<3,1>(3,0) = l.end_point;
    tp += Eigen::Matrix<double,6,1>::Ones()*0.5;
    cout<<"the tp : "<< tp.transpose()<<endl;
    cout<<"the l.start: "<<l.start_point.transpose()<<"  the l.end: "<<l.end_point.transpose()<<endl;

    // 开始建立优化
    ceres::Problem problem;
    problem.AddParameterBlock(tp.data(),6);

    ceres::CostFunction * t1 = new TPCostFunction(l_px1.start_px,l_px1.end_px,&cm1);
    ceres::CostFunction * t2 = new TPCostFunction(l_px2.start_px,l_px2.end_px,&cm2);
    ceres::CostFunction * t3 = new TPCostFunction(l_px3.start_px,l_px3.end_px,&cm3);
    ceres::CostFunction * t4 = new TPCostFunction(l_px4.start_px,l_px4.end_px,&cm4);
    problem.AddResidualBlock(t1,NULL,tp.data());
    problem.AddResidualBlock(t2,NULL,tp.data());
    problem.AddResidualBlock(t3,NULL,tp.data());
    problem.AddResidualBlock(t4,NULL,tp.data());

    ceres::Solver::Options options;
    ceres::Solver::Summary summary;
    options.linear_solver_type = ceres::DENSE_QR;
    options.minimizer_type = ceres::TRUST_REGION;
    options.trust_region_strategy_type = ceres::LEVENBERG_MARQUARDT;

    options.max_num_iterations = 8;
    options.function_tolerance = 1e-3;

    // 这个Solve 和那个不能用的solve 看起来还是有区分度的
    ceres::Solve(options,&problem,&summary);

    cout<<summary.BriefReport()<<endl;

    cout<<"the result is "<< tp.transpose()<<endl;
    
}

void testPlucker()
{

}

int main()
{
    Init();
    testTP();



    // 测试生成的线是不是对应的
    // 发现旋转的线是对的，但是含有的平移的线存在问题 最后发现是c2w初始化的问题

    // cout<<"origin start: "<<cm.p2c(l_px.start_px).transpose()<<endl;
    // cout<<"back expolated start :" << cm1.c2w(cm1.p2c(l_px1.start_px)).transpose()<<endl;
    // cout<<"the interval point :  " <<cm2.p2c(l_px2.start_px).transpose()<<endl;
    // cout<<"back expolated start :" << cm2.c2w(cm2.p2c(l_px2.start_px)).transpose()<<endl;
    // cout<<"back expolated start :" << cm3.c2w(cm4.p2c(l_px3.start_px)).transpose()<<endl;
    // cout<<"back expolated start :" << cm4.c2w(cm4.p2c(l_px4.start_px)).transpose()<<endl;

    // cv::line(img,l_px4.cv_start_px,l_px4.cv_end_px,0,2,8);
    // cv::line(img,l_px3.cv_start_px,l_px3.cv_end_px,0,2,8);
    // cv::line(img,l_px2.cv_start_px,l_px2.cv_end_px,0,2,8);
    // cv::line(img,l_px1.cv_start_px,l_px1.cv_end_px,0,2,8);
    // cv::line(img,l_px.cv_start_px,l_px.cv_end_px,0,2,8);
    // cv::imshow("check",img);
    // cv::waitKey(0);

}
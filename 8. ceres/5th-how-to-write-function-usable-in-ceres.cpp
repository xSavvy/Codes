/*
 * @Author: Liu Weilong
 * @Date: 2020-09-18 07:08:43
 * @LastEditors: Liu Weilong
 * @LastEditTime: 2020-09-22 07:08:05
 * @Description: 如何编写一个在ceres中可用的函数
 *               目前分析： 之前写的函数不可用的原因是 没有进行jet部分的重载
 */

#include <iostream>
#include <ceres/ceres.h>
#include <cmath>

const int kNumObservations = 67;
const double data[] = {
  0.000000e+00, 1.133898e+00,
  7.500000e-02, 1.334902e+00,
  1.500000e-01, 1.213546e+00,
  2.250000e-01, 1.252016e+00,
  3.000000e-01, 1.392265e+00,
  3.750000e-01, 1.314458e+00,
  4.500000e-01, 1.472541e+00,
  5.250000e-01, 1.536218e+00,
  6.000000e-01, 1.355679e+00,
  6.750000e-01, 1.463566e+00,
  7.500000e-01, 1.490201e+00,
  8.250000e-01, 1.658699e+00,
  9.000000e-01, 1.067574e+00,
  9.750000e-01, 1.464629e+00,
  1.050000e+00, 1.402653e+00,
  1.125000e+00, 1.713141e+00,
  1.200000e+00, 1.527021e+00,
  1.275000e+00, 1.702632e+00,
  1.350000e+00, 1.423899e+00,
  1.425000e+00, 1.543078e+00,
  1.500000e+00, 1.664015e+00,
  1.575000e+00, 1.732484e+00,
  1.650000e+00, 1.543296e+00,
  1.725000e+00, 1.959523e+00,
  1.800000e+00, 1.685132e+00,
  1.875000e+00, 1.951791e+00,
  1.950000e+00, 2.095346e+00,
  2.025000e+00, 2.361460e+00,
  2.100000e+00, 2.169119e+00,
  2.175000e+00, 2.061745e+00,
  2.250000e+00, 2.178641e+00,
  2.325000e+00, 2.104346e+00,
  2.400000e+00, 2.584470e+00,
  2.475000e+00, 1.914158e+00,
  2.550000e+00, 2.368375e+00,
  2.625000e+00, 2.686125e+00,
  2.700000e+00, 2.712395e+00,
  2.775000e+00, 2.499511e+00,
  2.850000e+00, 2.558897e+00,
  2.925000e+00, 2.309154e+00,
  3.000000e+00, 2.869503e+00,
  3.075000e+00, 3.116645e+00,
  3.150000e+00, 3.094907e+00,
  3.225000e+00, 2.471759e+00,
  3.300000e+00, 3.017131e+00,
  3.375000e+00, 3.232381e+00,
  3.450000e+00, 2.944596e+00,
  3.525000e+00, 3.385343e+00,
  3.600000e+00, 3.199826e+00,
  3.675000e+00, 3.423039e+00,
  3.750000e+00, 3.621552e+00,
  3.825000e+00, 3.559255e+00,
  3.900000e+00, 3.530713e+00,
  3.975000e+00, 3.561766e+00,
  4.050000e+00, 3.544574e+00,
  4.125000e+00, 3.867945e+00,
  4.200000e+00, 4.049776e+00,
  4.275000e+00, 3.885601e+00,
  4.350000e+00, 4.110505e+00,
  4.425000e+00, 4.345320e+00,
  4.500000e+00, 4.161241e+00,
  4.575000e+00, 4.363407e+00,
  4.650000e+00, 4.161576e+00,
  4.725000e+00, 4.619728e+00,
  4.800000e+00, 4.737410e+00,
  4.875000e+00, 4.727863e+00,
  4.950000e+00, 4.669206e+00,
};
using namespace std;

// 第一步配置仿函数
struct CostFunctor
{
    CostFunctor(const double x,const double y ):ober_x(x),ober_y(y){}

    template<typename T>
    bool operator()(const T* const m,const T* const c,T* residual)const
    {
        Evaluate(m[0],c[0],residual[0]); 
        return true; 
    }

    //  提示：1. 这里的成员函数也需要是const，目前看起来在调用的时候，使用的是一个const functor 对象
    template<typename JetT>
    void Evaluate(const JetT m,const JetT c,JetT & residual) const
    {
         residual =ober_y -  ceres::exp(m*ober_x+c);
        cout<<"--------------------------------------------------"<<endl;
        cout<<"now we show the differece"<<endl;
        cout<<"from the ceres::exp,the real part is "<<residual.a<<endl<<
        "the dual part is"<<residual.v<<endl;

        // 之前求导公式一直写错
        Evaluate(m.a,c.a,residual.a);
        residual.v = -ober_x*std::exp(m.a*ober_x+c.a)*m.v -std::exp(m.a*ober_x+c.a)*c.v;
        cout<<"now we show the differece"<<endl;
        cout<<"from the self-define ,the real part is "<<residual.a<<endl<<
        "the dual part is"<<residual.v<<endl;
    }
    void Evaluate(const double  m,const double c,double& residual) const
    {
        residual = ober_y - std::exp(m*ober_x+c);
    }
    

    const double ober_x;
    const double ober_y;
};
int main(int argc,char **argv)
{
    
    // 第二部分 构建求解的方程
    double m = 0.0;
    double c = 0.0;
    
    ceres::Problem problem;
    for(int i = 0;i<kNumObservations;i++)
    {
        ceres::CostFunction* cost_function =
            new ceres::AutoDiffCostFunction<CostFunctor, 1, 1, 1>(
                new CostFunctor(data[2 * i], data[2 * i + 1]));
        problem.AddResidualBlock(cost_function, NULL, &m, &c);
    }

    // 第三部分 配置求解器

    ceres::Solver::Options options;
    ceres::Solver::Summary summary;
    options.linear_solver_type = ceres::DENSE_QR;
    options.minimizer_progress_to_stdout = true;
    // options.max_num_iterations = 10;
    ceres::Solve(options,&problem,&summary);

    std::cout<<summary.BriefReport()<<std::endl;

    std::cout<<"initial_m is "<<0.0<<std::endl
    <<"initial_c is "<<0.0<<std::endl
    <<"m is "<<m<<std::endl<<"c is "<<c<<std::endl;




    return 0;
}
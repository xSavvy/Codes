/*
 * @Author: Liu Weilong
 * @Date: 2021-01-17 10:37:07
 * @LastEditors: Liu Weilong
 * @LastEditTime: 2021-01-17 11:04:33
 * @Description: 
 */
#include <iostream>
#include <vector>

#include "Eigen/Eigen"
#include "opencv2/core/core.hpp"

#define _S_SLAM_DEMO_ namespace slam_demo {
#define _E_SLAM_DEMO_ };
_S_SLAM_DEMO_


//  基础方法类
class FrameInterface
{
    public:
    using UVs = std::vector<Eigen::Vector2d> ;
    using H = Eigen::Matrix3d;
    // 四点生成H 矩阵
    // x_2 = Hx_1
    static bool EpipolarH4Pts(const UVs & uvs_1,const UVs & uvs_2,H& H12);
};

bool FrameInterface::EpipolarH4Pts(const UVs & uvs_1,const UVs & uvs_2,H& H12)
{
    if(uvs_1.size()!=uvs_2.size()||uvs_1.size()<4)
    return false;
    
    Eigen::MatrixXd A(uvs_1.size()*2,9); 
    A.setZero();
    Eigen::Matrix<double,2,9> temp_A;
    for(int i =0; i<4;i++)
    {
        auto & x1 = uvs_1.at(i);
        auto & x2 = uvs_2.at(i);
        temp_A<<x1.x(),x1.y(),1,0,0,0,-1*x2.x()*x1.x(),-1*x2.x()*x1.y(),-1*x2.x(),
                0,0,0,x1.x(),x1.y(),1,-1*x2.y()*x1.x(),-1*x2.y()*x1.y(),-1*x2.y();
        A.block<2,9>(i*2,0) = temp_A;
    }

    Eigen::SelfAdjointEigenSolver<Eigen::Matrix<double,9,9>> eigen_solver(A.transpose()*A);
    
    if(eigen_solver.eigenvalues()(7,0)<1e-6)
    {
        return false;
    }

    Eigen::Matrix<double,1,9> h = eigen_solver.eigenvectors().col(8);
    
    h.normalize();
    H12<<h;
}


_E_SLAM_DEMO_

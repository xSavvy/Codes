/*
 * @Author: Liu Weilong
<<<<<<< HEAD
 * @Date: 2021-01-16 09:09:33
 * @LastEditors: Liu Weilong 
 * @LastEditTime: 2021-01-16 14:20:52
 * @FilePath: /3rd-test-learning/22. slam_demo/frame_interface.h
 * @Description: 
 */
#include <iostream>
#include <random>
#include "opencv2/core/core.hpp"

#include "Eigen/Eigen"

using namespace std;

#define _S_SLAM_DEMO_ namespace slam_demo {
#define _E_SLAM_DEMO_ };


_S_SLAM_DEMO_

class FrameInterface
{
    public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW
    
    using UVs = std::vector<Eigen::Vector2d>;
    using UV = Eigen::Vector2d;
    using H = Eigen::Matrix3d;
    using F = Eigen::Matrix3d;

    bool EpipolarConstraintH(const UVs & uvs_img1,const UVs & uvs_img2,
                             Eigen::Matrix3d & T21, std::vector<double> & errs);
    bool EpipolarConstraintF(const UVs & uvs_img1,const UVs & uvs_img2,
                             Eigen::Matrix4d & T21, std::vector<double> & errs);

    bool Triangulate(const UVs & uvs_img1, const UVs & uvs_img2, 
                     const Eigen::Matrix4d & T21, std::vector<Eigen::Vector3d> & pts);
    bool PnP(const std::vector<Eigen::Vector3d> & pts, const UVs & uvs, Eigen::Matrix4d & transform );

    bool ICP(const std::vector<Eigen::Vector3d> & pts_1,const std::vector<Eigen::Vector3d> & pts_2, Eigen::Matrix4d & T21);
    
    // DLT_matrix  return false
    bool BuildHDLT(const UVs & uvs_1,const UVs & uvs_2, Eigen::Matrix<double,8,8> & DLT_matrix);

};

bool FrameInterface::BuildHDLT(const UVs & uvs_1,const UVs & uvs_2, Eigen::Matrix<double,8,9> & DLT_matrix)
{
    DLT_matrix.setZero();
    Eigen::Matrix<double,2,9> temp;
    for(int i =0;i<4;i++)
    {
        temp<<uvs_1[i].x(),uvs_1.y(),1,0,0,0,-1*uvs_1[i].x()*uvs_2[i].x(),-1*uvs_1[i].y()*uvs_2[i].x(),-1*uvs_2.x(),
              0,0,0,uvs_1[i].x(),uvs_1.y(),1,-1*uvs_1[i].x()*uvs_2[i].y(),-1*uvs_1[i].y()*uvs_2[i].y(),-1*uvs_2.y();
        DLT_matrix.block<2,9>(i*2,0) = temp;
    }
}


bool FrameInterface::EpipolarConstraintH(const UVs & uvs_img1,const UVs & uvs_img2,
                                         Eigen::Matrix3d & transform, std::vector<double> & errs)
{
    // RANSAC DLT H 
    // if(uvs_img1.size()<4 || uvs_img2.size()<4)
    // return false;
    
    // std::random_device rd; 
    // std::mt19937 gen(rd());

    // std::uniform_int_distribution<> int_random(0,uvs_img1.size());
    // size_t idx1=int_random(gen), idx2=int_random(gen), idx3=int_random(gen),idx4 = int_random(gen);

    // if(idx1==idx2||idx2==idx3||idx2==idx3||idx3==idx4||
    //    idx1==idx3||idx2==idx4||
    //    idx1==idx4)
    // continue;
    
    // UVs uvs_1{uvs_img1[idx1],uvs_img1[idx2],uvs_img1[idx3],uvs_img1[idx4]};
    // UVs uvs_2{uvs_img2[idx1],uvs_img2[idx2],uvs_img2[idx3],uvs_img2[idx4]};

    
    Eigen::Matrix<double,8,9> DLT_matrix;
    BuildHDLT(uvs_img1,uvs_img2,DLT_matrix);
    Eigen::SelfAdjointEigenSolver<Eigen::Matrix<double,9,9>> eigen_solver(DLT_matrix.transpose()*DLT_matrix);
    
    eigen_solver.eigenvectors();
    Eigen::Matrix3d H(eigen_solver.eigenvectors().col(8).data());
    
    errs.clear();
    errs.reserve(uvs_img1.size());
    for(int i=0;i<uvs_img1.size();i++)
    {
        errs.push_back()
    }

     
}





_E_SLAM_DEMO_
=======
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
>>>>>>> 96e839dc1432c23b21200ab7d9ccff3ce78ca4c8

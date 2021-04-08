/*
 * @Author: Liu Weilong
 * @Date: 2021-04-07 13:56:01
 * @LastEditors: Liu Weilong 
 * @LastEditTime: 2021-04-07 18:15:01
 * @FilePath: /3rd-test-learning/38. line_feature/vanishing_point/code/extrinc_calib.cpp
 * @Description: 
 * 1. 旋转外参标定的测试，因为在实际测试的情况下出现了外参无法标定的情况，这里需要进一步看一下
 * 2. 结论：
 *         单轴旋转，外参无法进行标定
 *         两个单轴旋转就可以对外参进行标定了。
 *         这说明了，地面水平运动的无法标定 Manhattan 和Camera 之间的外参 是 Manhattan VPTracker 最大的问题。
 *         这个时候能够自由运动的SO3 反而成了Manhanttan最好用的地方，因为外参是可以标定的。
 * 
 */

#include <vector>
#include <string>
#include <iostream>

#include "Eigen/Eigen"
#include "environment_builder.h"

using namespace std;

template <typename Derived>
static Eigen::Matrix<typename Derived::Scalar, 3, 3> skewSymmetric(const Eigen::MatrixBase<Derived> &q)
{
	Eigen::Matrix<typename Derived::Scalar, 3, 3> ans;
	ans << typename Derived::Scalar(0), -q(2), q(1),
		q(2), typename Derived::Scalar(0), -q(0),
		-q(1), q(0), typename Derived::Scalar(0);
	return ans;
}

int main()
{
    Object obj = Object(1);
    
    Rotation rot = Rotation::create(Eigen::Vector3d(0.,0.,1.),6,0.05);
    // 不添加 rot1 无法标定外参成功
    // Rotation rot1 = Rotation::create(Eigen::Vector3d(1.,1.,1.).normalized(),3.3,0.1);
    TrajectoryEngine te;
    te.addRotation(rot);
    // te.addRotation(rot1);
    te.addMotionForObject(obj);

    // 进行 Vehicle 和 Camera 的代码测试
    for(int i =1;i<obj.CameraMotion.size();i++)
    {
        // 测试外参
        Eigen::Quaterniond relative_c1_c2 = obj.CameraMotion[i-1].inverse() * obj.CameraMotion[i];
        Eigen::Quaterniond relative_v1_v2 = obj.VehicleMotion[i-1].inverse() * obj.VehicleMotion[i];
        
        double angle = relative_v1_v2.angularDistance(obj.Camera*relative_c1_c2*obj.Camera.inverse());
        cout<<angle<<endl;
    }
    
    cout<<"======================"<<endl<<"the real extrinc is "<<endl<<obj.Camera.coeffs().transpose()<<endl;

    // 外参推测测试
    Eigen::MatrixXd A(4*obj.CameraMotion.size(),4);
    for(int i =0;i<obj.CameraMotion.size();i++)
    {
        Eigen::Quaterniond R_f1d_f2d(obj.VehicleMotion[i]);
        Eigen::Quaterniond R_f1_f2(obj.CameraMotion[i]);

        double abs_angle = fabs(R_f1d_f2d.angularDistance(R_f1_f2));
        double huber = abs_angle>0.15? 1.0/abs_angle:1.0;

        double w = R_f1d_f2d.w();
        Eigen::Vector3d q = R_f1d_f2d.vec();
        Eigen::Matrix4d L = Eigen::Matrix4d::Zero();
        L.block<3, 3>(0, 0) = w * Eigen::Matrix3d::Identity() + skewSymmetric(q);
        L.block<3, 1>(0, 3) = q;
        L.block<1, 3>(3, 0) = -q.transpose();
        L(3, 3) = w;

        w = R_f1_f2.w();
        q = R_f1_f2.vec();
        Eigen::Matrix4d R = Eigen::Matrix4d::Zero();
        R.block<3, 3>(0, 0) = w * Eigen::Matrix3d::Identity() - skewSymmetric(q);
        R.block<3, 1>(0, 3) = q;
        R.block<1, 3>(3, 0) = -q.transpose();
        R(3, 3) = w; 

        A.block<4,4>(4*i,0) = huber*(L-R);	
    }

    Eigen::JacobiSVD<Eigen::MatrixXd> svd(A,Eigen::ComputeThinU|Eigen::ComputeThinV);
    cout<<"the V:"<<endl<<svd.matrixV()<<endl;
    Eigen::Matrix<double, 4, 1> x = svd.matrixV().col(3);
    Eigen::Quaterniond estimated_R(x);
    //cout << svd.singularValues().transpose() << endl;



    cout<<"the esti extrinc : "<<endl<<estimated_R.coeffs().transpose()<<endl;
    Eigen::Vector3d ric_cov;
    ric_cov = svd.singularValues().tail<3>();
    cout<<"the sigular"<<endl<<svd.singularValues().transpose()<<endl;

    for(int i =1;i<obj.CameraMotion.size();i++)
    {
        // 测试外参
        Eigen::Quaterniond relative_c1_c2 = obj.CameraMotion[i-1].inverse() * obj.CameraMotion[i];
        Eigen::Quaterniond relative_v1_v2 = obj.VehicleMotion[i-1].inverse() * obj.VehicleMotion[i];
        cout<<"real relative v1 v2 "<< relative_v1_v2.coeffs().transpose()<<endl;
        cout<<"esti relative v1 v2 "<<(estimated_R*relative_c1_c2*estimated_R.inverse()).coeffs().transpose()<<endl;
        double angle = relative_v1_v2.angularDistance(estimated_R*relative_c1_c2*estimated_R.inverse());
        cout<<angle<<endl;
    }

    
}
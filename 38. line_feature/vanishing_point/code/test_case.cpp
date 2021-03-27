/*
 * @Author: Liu Weilong
 * @Date: 2021-03-25 18:53:46
 * @LastEditors: Liu Weilong 
 * @LastEditTime: 2021-03-26 15:57:32
 * @FilePath: /3rd-test-learning/38. line_feature/vanishing_point/code/test_case.cpp
 * @Description: 
 * 
 * 1. vp 的估计存在方向问题 用防止突变的方法解决了这个问题
 * 
 * 
 * 
 */
#include "environment_builder.h"

Box b1 = Box::create(Eigen::Vector3d(0,0,0+0.3),0.2);
Box b2 = Box::create(Eigen::Vector3d(0,0,0+0.5),0.2,cv::Scalar(0,255,0));
Box b3 = Box::create(Eigen::Vector3d(0,0,0+0.7),0.2,cv::Scalar(0,0,255));
Box b4 = Box::create(Eigen::Vector3d(0,0.1,0+0.7),0.6,cv::Scalar(0,200,100));
BoxDisplayer bd;
Camera cm;
Eigen::Matrix<double,6,1> se3;
int x=0.,y=0.,z=0.,r=0.,p=0.,yaw=0.;
Eigen::Matrix3d K_inv = cm.K().inverse();
Eigen::Vector3d pre_x(1.0,0.,0.),pre_y(0.,1.0,0.),pre_z(0.,0.,1.);

void Adjust(int, void *)
{
    bd.vboxobs.clear();

    double x_ = float(x)/100;
    double y_ = float(y)/100;
    double z_ = float(z)/100;
    
    double r_ = float(r)/300;
    double p_ = float(p)/300;
    double yaw_ = float(yaw)/300;

    se3<<x_,y_,z_,r_,p_,yaw_;
    cm.T_w_c = Sophus::SE3d::exp(se3);

    cout<<"real SO3"<<endl<<cm.T_w_c.so3().matrix().inverse()<<endl;

    bd.vboxobs.push_back(b1.generateObs(&cm));
    bd.vboxobs.push_back(b2.generateObs(&cm));
    bd.vboxobs.push_back(b3.generateObs(&cm));
    bd.vboxobs.push_back(b4.generateObs(&cm));
    
    ImageLineEigen x_l1 = bd.vboxobs.front().v2dobs_x[0],
                   x_l2 = bd.vboxobs.front().v2dobs_x[1];
    ImageLineEigen y_l1 = bd.vboxobs.front().v2dobs_y[0],
                   y_l2 = bd.vboxobs.front().v2dobs_y[1];
    ImageLineEigen z_l1 = bd.vboxobs.front().v2dobs_z[0],
                   z_l2 = bd.vboxobs.front().v2dobs_z[1];

    // 测试性代码  start

    Eigen::Vector3d vp_x = (K_inv*getVPFromeLine(x_l1,x_l2)).normalized();
    Eigen::Vector3d vp_y = (K_inv*getVPFromeLine(y_l1,y_l2)).normalized();
    Eigen::Vector3d vp_z = (K_inv*getVPFromeLine(z_l1,z_l2)).normalized();
    
    if(vp_x.dot(pre_x)<0)
    vp_x *=-1;
    if(vp_y.dot(pre_y)<0)
    vp_y *=-1;
    if(vp_z.dot(pre_z)<0)
    vp_z *=-1;
    
    pre_x = vp_x;
    pre_y = vp_y;
    pre_z = vp_z;

    Eigen::Matrix3d est;
    est<<vp_x,vp_y,vp_x.cross(vp_y);
    cout<<"esitimate :"<<endl<<est<<endl;
    cout<<"the norm of estimate :"<<est.determinant()<<endl;
    






    // 测试性代码  end

    
    cv::Mat img_box = bd.showBox().clone();
    cv::Mat img_xyz = bd.showXYZ(true).clone();

    cv::imshow("box_test",img_box);
    cv::imshow("xyz_test",img_xyz);

}

int main()
{
    
    cv::namedWindow("ir_gray", CV_WINDOW_NORMAL);			//滑动窗口选择ir图canny阈值
    cv::createTrackbar("value1：", "ir_gray", &x,300 , Adjust);
    cv::createTrackbar("value2", "ir_gray", &y, 300, Adjust);
    cv::createTrackbar("value3：", "ir_gray", &z, 300, Adjust);
    cv::createTrackbar("value4", "ir_gray", &r, 300, Adjust);
    cv::createTrackbar("value5：", "ir_gray", &p, 300, Adjust);
    cv::createTrackbar("value6", "ir_gray", &yaw, 300, Adjust);
    Adjust(0, 0);
    cv::waitKey(0);

}
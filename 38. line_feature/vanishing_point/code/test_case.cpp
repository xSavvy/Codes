/*
 * @Author: Liu Weilong
 * @Date: 2021-03-25 18:53:46
 * @LastEditors: Liu Weilong 
 * @LastEditTime: 2021-03-25 20:18:04
 * @FilePath: /3rd-test-learning/38. line_feature/vanishing_point/code/test_case.cpp
 * @Description: 
 */
#include "environment_builder.h"

Box b1 = Box::create(Eigen::Vector3d(0,0,0+0.3),0.2);
Box b2 = Box::create(Eigen::Vector3d(0,0,0+0.5),0.2,cv::Scalar(0,255,0));
Box b3 = Box::create(Eigen::Vector3d(0,0,0+0.7),0.2,cv::Scalar(0,0,255));

BoxDisplayer bd;
Camera cm;
Eigen::Matrix<double,6,1> se3;
int x=0.,y=0.,z=0.,r=0.,p=0.,yaw=0.;

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
    bd.vboxobs.push_back(b1.generateObs(&cm));
    bd.vboxobs.push_back(b2.generateObs(&cm));
    bd.vboxobs.push_back(b3.generateObs(&cm));
    
    cv::Mat img_box = bd.showBox().clone();
    cv::Mat img_xyz = bd.showXYZ().clone();

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
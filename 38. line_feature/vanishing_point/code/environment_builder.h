/*
 * @Author: Liu Weilong
 * @Date: 2021-03-25 18:13:18
 * @LastEditors: Liu Weilong 
 * @LastEditTime: 2021-03-25 20:16:30
 * @FilePath: /3rd-test-learning/38. line_feature/vanishing_point/code/environment_builder.h
 * @Description: 
 */

#include <iostream>
#include <vector>

#include "Eigen/Eigen"
#include "sophus/se3.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace std;

class BoxObservation;
class ImageLine;
class ImageLineEigen;

ImageLineEigen toEigenLine(const ImageLine & input);
ImageLine toLine(const ImageLineEigen & input);

Eigen::Vector4d toV4d(const Eigen::Vector3d & p)
{
    return (Eigen::Vector4d()<<p,1.0).finished();
}

vector<Eigen::Vector4d> toV4d(const vector<Eigen::Vector3d> & vp)
{
    vector<Eigen::Vector4d> vp4d;
    vp4d.reserve(vp.size());
    for(auto & p:vp) vp4d.push_back(toV4d(p));
    return vp4d;
}

class Camera
{
    public:
    
    using M23 = Eigen::Matrix<double,2,3>;
    using M66 = Eigen::Matrix<double,6,6>;
    using M61 = Eigen::Matrix<double,6,1>;
    static double fx,fy,cx,cy;
    static double width,height;

    Sophus::SE3d T_w_c;
    Eigen::Vector2d c2p(Eigen::Vector3d point) const ;
    Eigen::Vector3d p2c(Eigen::Vector2d px,double depth=1.0)const;  
    Eigen::Vector3d c2w(Eigen::Vector3d point) const;
    Eigen::Vector3d w2c(Eigen::Vector3d point) const;
    M23 J_uv_xyz(Eigen::Vector3d point)const;

};


double Camera::fx = 307.3070580996126;
double Camera::fy = 307.3070580996126;
double Camera::cx = 372.865217584225;
double Camera::cy = 240.0338623810578;
double Camera::width = 752;
double Camera::height = 480;


Eigen::Vector2d Camera::c2p(Eigen::Vector3d point) const
{
    Eigen::Vector2d px;
    point /= point.z();
    px << fx*point.x() + cx,
          fy*point.y() + cy;
    return px;
}

Eigen::Vector3d Camera::p2c(Eigen::Vector2d px,double depth) const
{
    Eigen::Vector3d point;
    point<< (px.x()-cx)/fx,
            (px.y()-cy)/fy,
            1.0;
    point *= depth;
    return point;
}

Eigen::Vector3d Camera::c2w(Eigen::Vector3d point_c) const
{
    Eigen::Vector3d p_w = T_w_c * point_c;
    return p_w;
}

Eigen::Vector3d Camera::w2c(Eigen::Vector3d point_w) const
{
    Eigen::Vector3d p_c = T_w_c.inverse() * point_w;
    return p_c;
}

Camera::M23 Camera::J_uv_xyz(Eigen::Vector3d point) const
{
    M23 result;
    double z_inv = 1./point.z();
    double z_inv_2 = z_inv*z_inv;

    result<< fx*z_inv,0.,-1.*fx*point.x()*z_inv_2,
             0.,fy*z_inv,-1.*fy*point.y()*z_inv_2;

    return result;
}



class Line
{
    public:
    Eigen::Vector3d start_point, end_point;
};

class Box
{
    public:
    
    static Box create(const Eigen::Vector3d & start,double length,cv::Scalar color = cv::Scalar(255,0,0));
    
    BoxObservation generateObs(Camera * cm);

    vector<Line> vl;
    vector<Line> x_axis_l;
    vector<Line> y_axis_l;
    vector<Line> z_axis_l;
    double length;
    Eigen::Vector3d start;
    cv::Scalar color;
};



class ImageLine
{
    public:
    cv::Point2f start_point,end_point;  
};

class ImageLineEigen
{
    public:
    Eigen::Vector2d start_point,end_point;
};


class BoxObservation
{
    public:

    vector<ImageLineEigen> v2dobs;

    vector<ImageLineEigen> v2dobs_x;
    vector<ImageLineEigen> v2dobs_y;
    vector<ImageLineEigen> v2dobs_z;
    
    vector<ImageLine>  vpixelobs_x;
    vector<ImageLine>  vpixelobs_y;
    vector<ImageLine>  vpixelobs_z;
    
    vector<ImageLine>  vpixelobs;
    cv::Scalar color;
};

class BoxDisplayer
{
    public:
    vector<BoxObservation> vboxobs;
    cv::Mat showBox()const;
    cv::Mat showXYZ()const;
};

cv::Mat BoxDisplayer::showBox()const
{
    cv::Mat img = cv::Mat::zeros(480,752,CV_8U);
    cv::cvtColor(img,img,CV_GRAY2RGB);

    for(auto & obs:vboxobs)
    {
        for(auto & l:obs.vpixelobs)
        {
            cv::line(img,l.start_point,l.end_point,obs.color,2,8);
        }
    }
    return img;
}

cv::Mat BoxDisplayer::showXYZ()const
{
    cv::Mat img = cv::Mat::zeros(480,752,CV_8U);
    cv::cvtColor(img,img,CV_GRAY2RGB);

    cv::Scalar X (255,0,0);
    cv::Scalar Y (0,255,0);
    cv::Scalar Z (0,0,255);
    
    for(auto & obs:vboxobs)
    {
        for(auto & l:obs.vpixelobs_x)
        {
            cv::line(img,l.start_point,l.end_point,X,2,8);
        }
        for(auto & l:obs.vpixelobs_y)
        {
            cv::line(img,l.start_point,l.end_point,Y,2,8);
        }
        for(auto & l:obs.vpixelobs_z)
        {
            cv::line(img,l.start_point,l.end_point,Z,2,8);
        }
    }
    return img;
}

ImageLineEigen toEigenLine(const ImageLine & input)
{
    ImageLineEigen output;
    output.start_point.x() =  input.start_point.x;
    output.start_point.y() =  input.start_point.y;
    output.end_point.x() =  input.end_point.x;
    output.end_point.y() =  input.end_point.y;
    return output;
};


ImageLine toLine(const ImageLineEigen & input)
{
    ImageLine output;
    output.start_point.x = input.start_point.x();
    output.start_point.y = input.start_point.y();
    output.end_point.x = input.end_point.x();
    output.end_point.y = input.end_point.y();
    return output;
}
Box Box::create(const Eigen::Vector3d & start,double length,cv::Scalar color )
{
    Box output;
    output.length = length;
    output.start = start;
    output.color = color;
    
    Line l1,l2,l3,l4,l5,l6,l7,l8,l9,l10,l11,l12;
    l1.start_point = start;
    l1.end_point = start;
    l1.end_point.z() += length;

    l2.start_point = start;
    l2.end_point = start;
    l2.end_point.x() += length;

    l3.start_point = start;
    l3.end_point = start;
    l3.end_point.y() += length;

    l4.start_point = l1.end_point;
    l4.end_point = l1.end_point;
    l4.end_point.x() += length;
    
    l5.start_point = l1.end_point;
    l5.end_point = l1.end_point;
    l5.end_point.y() += length;

    l6.start_point = l2.end_point;
    l6.end_point = l2.end_point;
    l6.end_point.y() +=length;

    l7.start_point = l2.end_point;
    l7.end_point = l2.end_point;
    l7.end_point.z() +=length;

    l8.start_point = l3.end_point;
    l8.end_point = l3.end_point;
    l8.end_point.z() +=length;
    
    l9.start_point = l3.end_point;
    l9.end_point = l3.end_point;
    l9.end_point.x() +=length;

    l10.start_point = Eigen::Vector3d(length,length,length)+start;
    l10.end_point = Eigen::Vector3d(0,length,length)+start;

    l11.start_point = Eigen::Vector3d(length,length,length)+start;
    l11.end_point = Eigen::Vector3d(length,0,length)+start;

    l12.start_point = Eigen::Vector3d(length,length,length)+start;
    l12.end_point = Eigen::Vector3d(length,length,0)+start;

    output.vl.push_back(l1);
    output.vl.push_back(l2);
    output.vl.push_back(l3);
    output.vl.push_back(l4);
    output.vl.push_back(l12);
    output.vl.push_back(l11);
    output.vl.push_back(l10);
    output.vl.push_back(l9);
    output.vl.push_back(l8);
    output.vl.push_back(l7);
    output.vl.push_back(l6);
    output.vl.push_back(l5);

    output.z_axis_l.push_back(l1);
    output.z_axis_l.push_back(l12);
    output.z_axis_l.push_back(l7);
    output.z_axis_l.push_back(l8);

    output.x_axis_l.push_back(l4);
    output.x_axis_l.push_back(l10);
    output.x_axis_l.push_back(l9);
    output.x_axis_l.push_back(l2);

    output.y_axis_l.push_back(l3);
    output.y_axis_l.push_back(l6);
    output.y_axis_l.push_back(l5);
    output.y_axis_l.push_back(l11);



    return output;
}

BoxObservation Box::generateObs( Camera * cm)
{
    
    BoxObservation output;
    output.color = color;
    for(int i=0;i<vl.size();i++)
    {
        ImageLine t1;
        ImageLineEigen t2;
        t2.start_point = cm->c2p(cm->w2c(vl[i].start_point));
        t2.end_point = cm->c2p(cm->w2c(vl[i].end_point));
        t1 = toLine(t2);

        output.v2dobs.push_back(t2);
        output.vpixelobs.push_back(t1);
    }

    for(int i =0;i<x_axis_l.size();i++)
    {
        ImageLine t1;
        ImageLineEigen t2;
        t2.start_point = cm->c2p(cm->w2c(x_axis_l[i].start_point));
        t2.end_point = cm->c2p(cm->w2c(x_axis_l[i].end_point));
        t1 = toLine(t2);

        output.v2dobs_x.push_back(t2);
        output.vpixelobs_x.push_back(t1);
    }
    for(int i =0;i<y_axis_l.size();i++)
    {
        ImageLine t1;
        ImageLineEigen t2;
        t2.start_point = cm->c2p(cm->w2c(y_axis_l[i].start_point));
        t2.end_point = cm->c2p(cm->w2c(y_axis_l[i].end_point));
        t1 = toLine(t2);

        output.v2dobs_y.push_back(t2);
        output.vpixelobs_y.push_back(t1);
    }
    for(int i =0;i<z_axis_l.size();i++)
    {
        ImageLine t1;
        ImageLineEigen t2;
        t2.start_point = cm->c2p(cm->w2c(z_axis_l[i].start_point));
        t2.end_point = cm->c2p(cm->w2c(z_axis_l[i].end_point));
        t1 = toLine(t2);

        output.v2dobs_z.push_back(t2);
        output.vpixelobs_z.push_back(t1);
    }

    return output;
}

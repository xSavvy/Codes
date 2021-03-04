/*
 * @Author: Liu Weilong
 * @Date: 2021-03-03 09:50:42
 * @LastEditors: Liu Weilong 
 * @LastEditTime: 2021-03-04 18:19:52
 * @FilePath: /3rd-test-learning/28. vslam_course/HW6/code/Direct_tracker.h
 * @Description: 
 */
#include "tracker_base.h"
#include "sophus/se3.hpp"
#include "common.h"


using namespace std;

class CameraInstrinc
{
    public:
    CameraInstrinc(const std::string & config){LoadInstrinc(config);}
    void LoadInstrinc(const std::string & config);
    void jaocobian_uv_xyz(const Eigen::Vector3f &p,Eigen::Matrix<float,2,3> & jacobian);
    Eigen::Vector2f c2p(const Eigen::Vector3f & p);
    float fx,fy,cx,cy;
};

void CameraInstrinc::LoadInstrinc(const std::string & config)
{
    cv::FileStorage fin(config.c_str(),CV_STORAGE_READ);
    fx = double(fin["DirectTracker.Camera.fx"]);
    fy = double(fin["DirectTracker.Camera.fy"]);
    cx = double(fin["DirectTracker.Camera.cx"]);
    cy = double(fin["DirectTracker.Camera.cy"]);

    cout<<"DirectTracker.Camera.fx: "<<fx<<endl;
    cout<<"DirectTracker.Camera.fy: "<<fy<<endl;
    cout<<"DirectTracker.Camera.cx: "<<cx<<endl;
    cout<<"DirectTracker.Camera.cy: "<<cy<<endl;
}

void CameraInstrinc::jaocobian_uv_xyz(const Eigen::Vector3f &p, Eigen::Matrix<float,2,3> & jacobian)
{
    jacobian.setZero();
    jacobian<<fx/p.z(),0,-1*fx*p.x()/p.z()/p.z(),
              0,fy/p.z(),-1*fy*p.y()/p.z()/p.z();
}


Eigen::Vector2f CameraInstrinc::c2p(const Eigen::Vector3f & p)
{
    return Eigen::Vector2f(fx*p.x()/p.z()+cx,fy*p.y()/p.z()+cy);
}

class DirectTracker:public TrackerBase
{
    public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW

    DirectTracker(std::string & config,bool inverse):TrackerBase(config),inverse_(inverse)
    {
        instrinc_ptr_ = new CameraInstrinc(config);
    }
    virtual void Impl() override;
    void SetLastFramePose(Eigen::Matrix<float,6,1> & init){pre_pose_ = init;} 
    private:
    /**
     *  param:
     *  @pts 应该是在世界坐标系下
     *  @pre_pose 应该是在世界坐标系下
     *  @result_pose 应该是在世界坐标系下
    */
    void SingleLayerCalc(const cv::Mat & pre_img,const cv::Mat & cur_img,
                         const std::vector<Eigen::Vector3f> & pts,
                         const Eigen::Matrix<float,6,1> & pre_pose,
                         Eigen::Matrix<float,6,1> & result_pose,  bool inverse);
    
    Eigen::Matrix<float,6,1> pre_pose_;
    Eigen::Matrix<float,6,1> result_;
    CameraInstrinc * instrinc_ptr_;
    std::vector<bool> success_;
    bool inverse_;
};

void DirectTracker::SingleLayerCalc(const cv::Mat & pre_img,const cv::Mat & cur_img,
                                    const std::vector<Eigen::Vector3f> & pts,
                                    const Eigen::Matrix<float,6,1> & pre_pose,
                                    Eigen::Matrix<float,6,1> & result_pose,  bool inverse)
{
    // 初始化 H b J
    int half_patch_size = options_ptr_->template_/2;
    int itertations = 10;

    Eigen::Matrix<float,6,6> H;
    Eigen::Matrix<float,6,1> b;

    Eigen::Matrix<float,1,2> J_uv;
    Eigen::Matrix<float,2,3> J_xyz;
    Eigen::Matrix<float,3,6> J_xi;
    Eigen::Matrix<float,1,6> J;
    Eigen::Matrix<float,3,3> I = Eigen::Matrix<float,3,3>::Identity();

    Eigen::Matrix<float,6,1> dxi;

    Sophus::SE3f se3_pre = Sophus::SE3f::exp(pre_pose);
    Sophus::SE3f se3_cur = Sophus::SE3f::exp(result_pose);
    Sophus::SE3f d_se3 = Sophus::SE3f::exp(Eigen::Matrix<float,6,1>::Zero());

    Eigen::Vector3f p3d_pre,p3d_cur;
    
    float cost = 0.,Lastcost=0.,error=0.;
    
    for(auto & p :pts)
    {
        H.setZero();
        b.setZero();
        
        p3d_pre = se3_pre*p;
        p3d_cur = d_se3*se3_cur*p;

        auto p2d_pre = instrinc_ptr_->c2p(p3d_pre);
        auto p2d_cur = instrinc_ptr_->c2p(p3d_cur);
        
        // 没有写迭代
        // 计算 Jacobian error
        for(int x = -half_patch_size; x < half_patch_size ; x++)
            for(int y = -half_patch_size; y<half_patch_size ; y++)
            {
                error = GetPixelValue(pre_img_,p2d_pre.x() + x,p2d_pre.y() + y) - 
                        GetPixelValue(cur_img_,p2d_cur.x() + x,p2d_cur.y() + y);
                // jacobian 需要进一步进行检查
                J_uv = -1.0 * Eigen::Vector2d(
                            0.5 * (GetPixelValue(cur_img_, p2d_cur.x() + x + 1, p2d_cur.y() + y) -
                                   GetPixelValue(cur_img_, p2d_cur.x() + x - 1, p2d_cur.y() + y)),
                            0.5 * (GetPixelValue(cur_img_, p2d_cur.x() + x, p2d_cur.y() + y + 1) -
                                   GetPixelValue(cur_img_, p2d_cur.x() + x, p2d_cur.y() + y - 1))
                        );
                instrinc_ptr_->jaocobian_uv_xyz(p3d_cur,J_xyz);
                J_xi.block<3,3>(0,0) = I;
                J_xi.block<3,3>(0,3) = -1*Sophus::SO3f::hat(p3d_cur);
                J = J_uv*J_xyz*J_xi;
                H += J.transpose() * J;
                b += -1* error * J.transpose();
                cost += error * error;
            }

        // 更新 \delta \xi
        Eigen::Matrix<float,6,1> update = H.ldlt().solve(b);
        if(std::isnan(update[0]))
        {
            std::cout<<" not converge !"<<endl;
            continue;
        }
        if(cost>Lastcost)
        {
            continue;
        }
        
        d_se3 = Sophus::SE3f::exp(update)*d_se3;
        // 重置 H b J
        
    }

}
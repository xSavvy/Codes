/*
 * @Author: Liu Weilong
 * @Date: 2021-03-03 09:50:42
 * @LastEditors: Liu Weilong 
 * @LastEditTime: 2021-03-03 20:35:25
 * @FilePath: /3rd-test-learning/28. vslam_course/HW6/code/Direct_tracker.h
 * @Description: 
 */
#include "tracker_base.h"
#include "sophus/se3.hpp"

class CameraInstrinc
{
    public:
    float fx,fy,
}


class DirectTracker:public TrackerBase
{
    public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW
    using M66 = Eigen::Matrix<float,6,6>;
    using M61 = Eigen::Matrix<float,6,1>;
    DirectTracker(std::string & config,bool inverse):TrackerBase(config),inverse_(inverse){}
    virtual void Impl() override;
    
    private:
    void SingleLayerCalc(const cv::Mat & pre_img,const cv::Mat & cur_img,
                                 const std::vector<Eigen::Vector3f> & pts,bool inverse);
    
    Eigen::Matrix4f result_;
    std::vector<bool> success_;
    bool inverse_;
};


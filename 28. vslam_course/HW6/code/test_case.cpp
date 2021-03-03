/*
 * @Author: Liu Weilong
 * @Date: 2021-02-27 23:59:23
 * @LastEditors: Liu Weilong
 * @LastEditTime: 2021-03-03 08:06:51
 * @Description: 
 * 
 * opencv tracker 速度大概 1ms 已经不错了
 * 
 * 
 */

#include <string>

#include "opencv_tracker.h"
#include "LK_self_tracker.h"
#include "opencv2/opencv.hpp"
#include "common.h"

std::string img1,img2,config;


int main()
{
    img1 = "./1.png";
    img2 = "./2.png";
    config = "./config/config.yaml";

    // imread
    cv::Mat pre_img = cv::imread(img1,0);
    cv::Mat cur_img = cv::imread(img2,0);

    // find corners
    auto start = chrono::high_resolution_clock::now();
    std::vector<cv::Point2f> corners;
    cv::goodFeaturesToTrack(pre_img,corners,500,0.1,30);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> diff = end - start;
    int ms = std::chrono::duration_cast<chrono::milliseconds>(diff).count();
    cout<<"GFTT total used time : "<< ms<<" ms"<<endl;
    
    OpencvTracker::OpencvCorners corner_28;
    corner_28.push_back(corners[28]);


    // 算法主体
    Corners temp_pre_corners;
    cv2eigen(corner_28,temp_pre_corners);
    OpencvTracker cv_tracker(config);
    cv_tracker.SetInput(pre_img,temp_pre_corners);
    cv_tracker.SetTarget(cur_img);
    cv_tracker.Run();

    LKtracker lk_tracker(config,true);
    lk_tracker.SetInput(pre_img,temp_pre_corners);
    lk_tracker.SetTarget(cur_img);
    lk_tracker.Run();

    const auto result = lk_tracker.GetCorners();

    
    // draw
    cv::Mat RGB_pre,RGB_cur,RGB_cur_cv;
    cv::cvtColor(pre_img,RGB_pre,CV_GRAY2RGB);
    cv::cvtColor(cur_img,RGB_cur,CV_GRAY2RGB);
    cv::cvtColor(cur_img,RGB_cur_cv,CV_GRAY2RGB);
    DrawCorners(RGB_pre,corner_28);
    OpencvTracker::OpencvCorners temp_result,temp_result_cv;
    eigen2cv(result,temp_result);
    DrawForMatchResult(RGB_cur,corner_28,temp_result,cv::Scalar(0,255,0));
    
    cv::imshow("pre pic with corners",RGB_pre);
    cv::imshow("cur pic with corners",RGB_cur);
    cv::imshow("cur pic CV with corners",RGB_cur_cv);
    cv::waitKey(0);
}
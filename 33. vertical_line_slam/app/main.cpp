/*
 * @Author: Liu Weilong
 * @Date: 2021-02-01 16:08:26
 * @LastEditors: Liu Weilong 
 * @LastEditTime: 2021-02-01 17:57:09
 * @FilePath: /3rd-test-learning/33. vertical_line_slam/app/main.cpp
 * @Description: 
 */

#include <iostream>
#include <string>

#include "data_loader.h"
#include "preprocess.h"
#include "tic_toc.hpp"
#include "display.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/ximgproc/fast_line_detector.hpp"

#include <opencv2/line_descriptor.hpp>
#include <opencv2/features2d.hpp>

using namespace std;
using namespace cv;
using namespace cv::line_descriptor;
using namespace cv::ximgproc;
int main()
{
    DataLoader dl("./config/all_path.yaml");
    MyneyePreprocessor mp("./config/undistort.yml");

    cv::Mat img_l_raw,img_r_raw,img_l,img_r;
    TicToc tictoc_lsd("LSD"),tictoc_lbd("LBD"); 
    Ptr<FastLineDetector> fld_ = createFastLineDetector(60,1.414213562f,50,50,3,false);
    Ptr<BinaryDescriptor> bd_ = BinaryDescriptor::createBinaryDescriptor();
    while(dl.LoadImg(img_l_raw,img_r_raw))
    {
        // 取内参

        // 去畸变
        mp.UnDistort(img_l_raw,img_r_raw,img_l,img_r);
        // LSD提取
        tictoc_lsd.Tic();
        std::vector<Vec4f> lsd_l,lsd_r;
        fld_->detect(img_l,lsd_l);
        fld_->detect(img_r,lsd_r);
        tictoc_lsd.Toc();
            
        // LBD


        // Match
        


        // 生成plucker

        // 去非竖直线

        // 线段显示(image+pangolin)
        fld_->drawSegments(img_r,lsd_r);
        fld_->drawSegments(img_l,lsd_l);
        cv::imshow("Left Camera",img_l);
        cv::imshow("Right Camera",img_r);
        cv::waitKey(10);
    }
    
    
}
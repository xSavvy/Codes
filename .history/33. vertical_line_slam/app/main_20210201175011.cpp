/*
 * @Author: Liu Weilong
 * @Date: 2021-02-01 16:08:26
 * @LastEditors: Liu Weilong 
 * @LastEditTime: 2021-02-01 17:50:11
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

int main()
{
    DataLoader dl("./config/all_path.yaml");
    MyneyePreprocessor mp("./config/undistort.yml");

    cv::Mat img_l_raw,img_r_raw,img_l,img_r;
    TicToc tictoc_lsd("LSD"),tictoc_lbd("LBD"); 
    Ptr<FastLineDetector> fld_ = createFastLineDetector(60);
    Ptr<BinaryDescriptor> bd_ = BinaryDescriptor::createBinaryDescriptor(  );
    while(dl.LoadImg(img_l_raw,img_r_raw))
    {
        // 取内参

        // 去畸变
        mp.UnDistort(img_l_raw,img_r_raw,img_l,img_r);
        // LSD提取
        tictoc_lsd.Tic();
        std::vector<KeyLine> lsd_l,lsd_r, keylsd_l,keylsd_r;
        fld_->detect(img_l,lsd_l,2,2);
        fld_->detect(img_r,lsd_r,2,2);
        tictoc_lsd.Toc();
            
        // LBD
        Mat lbd_descr_r,lbd_descr_l;
        bd_->compute( img_r, keylsd_r, lbd_descr_r );
        bd_->compute( img_l, keylsd_l, lbd_descr_l );

        // Match
        


        // 生成plucker

        // 去非竖直线

        // 线段显示(image+pangolin)
        DrawLine(img_r,keylsd_r);
        DrawLine(img_l,keylsd_l);
        cv::imshow("Left Camera",img_l);
        cv::imshow("Right Camera",img_r);
        cv::waitKey(10);
    }
    
    
}
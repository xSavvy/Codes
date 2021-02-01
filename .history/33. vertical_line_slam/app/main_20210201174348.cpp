/*
 * @Author: Liu Weilong
 * @Date: 2021-02-01 16:08:26
 * @LastEditors: Liu Weilong 
 * @LastEditTime: 2021-02-01 17:43:48
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
    Ptr<LSDDetector> lsd_;
    lsd_ = cv::line_descriptor::LSDDetector::createLSDDetector();
    Ptr<BinaryDescriptor> bd_ = BinaryDescriptor::createBinaryDescriptor(  );
    while(dl.LoadImg(img_l_raw,img_r_raw))
    {
        // 取内参

        // 去畸变
        mp.UnDistort(img_l_raw,img_r_raw,img_l,img_r);
        // LSD提取
        tictoc_lsd.Tic();
        std::vector<KeyLine> lsd_l,lsd_r, keylsd_l,keylsd_r;
        lsd_->detect(img_l,lsd_l,2,2);
        lsd_->detect(img_r,lsd_r,2,2);
        tictoc_lsd.Toc();

        // 去掉一部分过短的线
        for ( int i = 0; i < (int) lsd_l.size(); i++ )
        {
            if( lsd_l[i].octave == 0 && lsd_l[i].lineLength >= 60)
            {
                keylsd_l.push_back( lsd_l[i] );
            }
        }
        for ( int i = 0; i < (int) lsd_r.size(); i++ )
        {
            if( lsd_r[i].octave == 0 && lsd_r[i].lineLength >= 60)
            {
                keylsd_r.push_back( lsd_r[i] );
            }
        }
        
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
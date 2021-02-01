/*
 * @Author: Liu Weilong
 * @Date: 2021-02-01 16:08:26
 * @LastEditors: Liu Weilong 
 * @LastEditTime: 2021-02-01 16:23:46
 * @FilePath: /3rd-test-learning/33. vertical_line_slam/app/main.cpp
 * @Description: 
 */

#include <iostream>
#include <string>

#include "data_loader.h"
#include "preprocess.h"
#include "opencv2/highgui/highgui.hpp"


using namespace std;
int main()
{
    DataLoader dl("./config/all_path.yaml");
    MyneyePreprocessor mp()
    cv::Mat img_l,img_r;
    
    while(dl.LoadImg(img_l,img_r))
    {
        // 取内参

        // 去畸变

        // LSD提取
        
        // 生成plucker

        // 去非竖直线

        // 线段显示(image+pangolin)

        cv::imshow("Left Camera",img_l);
        cv::imshow("Right Camera",img_r);
        cv::waitKey(10);
    }
    
    
}
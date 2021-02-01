/*
 * @Author: Liu Weilong
 * @Date: 2021-02-01 16:08:26
 * @LastEditors: Liu Weilong 
 * @LastEditTime: 2021-02-01 16:13:17
 * @FilePath: /3rd-test-learning/33. vertical_line_slam/src/main.cpp
 * @Description: 
 */

#include <iostream>
#include <string>

#include "data_loader.h"
#include "opencv2/highgui/highgui.hpp"
using namespace std;
int main()
{
    DataLoader dl("../all_path.yaml");

    cv::Mat img_l,img_r;
    
    while(dl.LoadImg(img_l,img_r))
    {
        cv::imshow("Left Camera",img_l);
        cv::imshow("Right Camera",img_r);
        cv::waitKey(10);
    }
    
    
}
/*
 * @Author: Liu Weilong
 * @Date: 2020-11-11 09:01:40
 * @LastEditors: Liu Weilong 
 * @LastEditTime: 2020-11-11 09:14:16
 * @FilePath: /3rd-test-learning/26. opencv/basic_io.cpp
 * @Description: 测试opencv cmake 和io 进行  
 */

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <string>
using namespace std;

int main()
{   
    std::string img_path1,img_path2;
    img_path1 = "/home/sunny/workspace_private/3rd-test-learning/26. opencv/1.png";
    img_path2 = "/home/sunny/workspace_private/3rd-test-learning/26. opencv/2.png";
    cv::Mat img1 = cv::imread(img_path1,0);
    cv::Mat img2 = cv::imread(img_path2,0);

    
    cv::imshow("img1",img1);
    cv::waitKey(0);
    cv::imshow("img2",img2);
    cv::waitKey(0);
    
    return 0;
}
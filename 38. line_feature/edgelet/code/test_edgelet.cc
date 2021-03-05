/*
 * @Author: Liu Weilong
 * @Date: 2021-03-05 16:32:55
 * @LastEditors: Liu Weilong 
 * @LastEditTime: 2021-03-05 17:55:34
 * @FilePath: /3rd-test-learning/38. line_feature/edgelet/code/test_edgelet.cc
 * @Description: 
 * 
 * 可以压缩到3ms 
 * 
 * 
 */
#include <iostream>
#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"

using namespace std;

std::string img_path;

int main()
{
    img_path = "../1.png";

    cv::Mat img = cv::imread(img_path.c_str(),0);
    cv::Mat img2 = img.clone();

    cv::Mat gradx = cv::Mat::zeros( img.rows, img.cols, CV_32F);
    cv::Mat grady = cv::Mat::zeros(img.rows, img.cols, CV_32F);
    cv::Mat mag =  cv::Mat::zeros(img.rows, img.cols, CV_32F);

    int cell_size = 200;    
    int cell_x = img.cols/cell_size;
    int cell_y = img.rows/cell_size;

    auto start = chrono::high_resolution_clock::now();

    int x_start = 0, y_start=0;


    for(int i=0;i<cell_x-1;i++){
        for(int j=0;j<cell_y-1;j++)
        {
            cv::Rect roi(x_start,y_start,cell_size,cell_size);
            cv::Mat canny;
            cv::imshow("aaa",img(roi));
            cv::waitKey(0);
            y_start+=cell_size;
        }
        x_start +=cell_size;
    }
    

    // cv::GaussianBlur(img,img2,cv::Size(3,3),0,0);
    // cv::Scharr(img2, gradx, CV_32F, 1, 0, 1/32.0);
    // cv::Scharr(img2, grady, CV_32F, 0, 1, 1/32.0);
    // cv::magnitude(gradx,grady,mag);

    // for(int i=0;i<cell_x;i++)
    //     for(int j=0;j<cell_y;j++)
    //     {
    //         cv::Rect roi(x_start,y_start,cell_size,cell_size);
    //         cv::Mat canny;
    //         cv::Canny(img(roi),canny,30,50);
    //     }
    
    // auto end = chrono::high_resolution_clock::now();
    // chrono::duration<double> diff = end - start;
    // cout<<"Edgelet Preparation Cost : "<< diff.count()<<" s"<<endl;

    // cv::imshow("origin img",img);
    // cv::imshow("canny",canny);
    // cv::waitKey(0);

}
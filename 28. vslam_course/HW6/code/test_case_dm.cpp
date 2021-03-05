/*
 * @Author: Liu Weilong
 * @Date: 2021-03-05 08:00:41
 * @LastEditors: Liu Weilong 
 * @LastEditTime: 2021-03-05 16:29:21
 * @Description: 
 */
#include "Direct_tracker.h"
#include "opencv2/opencv.hpp"

using namespace std;

std::string left_file,disparity_file;
std::string config;

int main()
{
    left_file = "./left.png";
    disparity_file = "./disparity.png";
    config = "./config/config.yaml";

    cv::Mat left_img = cv::imread(left_file,0);
    cv::Mat disparity_img = cv::imread(disparity_file,0);

    int nPoints,boarder;
    float baseline,fx;

    cv::RNG rng;
    cv::FileStorage fin(config.c_str(),CV_STORAGE_READ);
    nPoints = (int)fin["DirectTracker.nPoints"];
    boarder = (int)fin["DirectTracker.boarder"];
    baseline = (double)fin["DirectTracker.Camera.baseline"];
    fx = (double)fin["DirectTracker.Camera.fx"];

    std::vector<Eigen::Vector3f> p3d_ref;
    p3d_ref.reserve(nPoints);

    //
    for(int i =0;i<nPoints;i++)
    {
        int x = rng.uniform(boarder,left_img.cols - boarder);
        int y = rng.uniform(boarder,left_img.rows - boarder);
        int disparity = disparity_img.at<uchar>(y,x);
        float depth = fx*baseline/disparity;
        
    }




}

/*
 * @Author: Liu Weilong
 * @Date: 2021-02-01 16:36:25
 * @LastEditors: Liu Weilong 
 * @LastEditTime: 2021-02-01 16:50:05
 * @FilePath: /3rd-test-learning/33. vertical_line_slam/include/line_extractor.h
 * @Description: 
 */
#include <iostream>
#include <string>


#include "Eigen/Eigen"
#include "opencv2/core/core.hpp"

using namespace std;

class VerticalLineExtractor
{
    public:

    




    private:

    cv::Mat img_target_;



    private:
    class VerticalLineExtractorOptions
    {
        public:
        VerticalLineExtractorOptions(const string & path);
        unsigned int length_th_;
        double error_th_;
    };
    VerticalLineExtractorOptions  options_;
};



VerticalLineExtractor::
VerticalLineExtractorOptions::VerticalLineExtractorOptions(const string & path)
{
    cv::FileStorage fsread(path.c_str(), CV_STORAGE_READ);
    if (fsread.isOpened())
    {
        fsread["LineExtractor.Vertical.length"] >> length_th_;
        fsread["LineExtractor.Vertical.error"] >> error_th_;
    }

    cout<<"the length theshold is "<<length_th_<<endl;
    cout<<"the vertical error theshold is "<<error_th_<<endl;
}
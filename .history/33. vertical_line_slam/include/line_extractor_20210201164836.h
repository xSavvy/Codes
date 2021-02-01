/*
 * @Author: Liu Weilong
 * @Date: 2021-02-01 16:36:25
 * @LastEditors: Liu Weilong 
 * @LastEditTime: 2021-02-01 16:48:36
 * @FilePath: /3rd-test-learning/33. vertical_line_slam/include/line_extractor.h
 * @Description: 
 */
#include <string>


#include "Eigen/Eigen"
#include "opencv2/core/core.hpp"

using namespace std;

class VerticalLineExtractor
{
    public:




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

    cout<<"the "
}
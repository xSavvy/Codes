/*
 * @Author: Liu Weilong
 * @Date: 2021-02-01 16:36:25
 * @LastEditors: Liu Weilong 
 * @LastEditTime: 2021-02-01 16:47:34
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
        unsigned int length_;
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
        fsread["M1"] >> length_;
        fsread["D1"] >> D1;
        fsread["M2"] >> M2;
        fsread["D2"] >> D2;
        fsread["R"] >> R;
        fsread["T"] >> T;
        fsread["Camera.fx"]>>fx;
        fsread["Camera.fy"]>>fy;
        fsread["Camera.cx"]>>cx;
        fsread["Camera.cy"]>>cy;
    }
}
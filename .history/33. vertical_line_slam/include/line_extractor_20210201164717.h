/*
 * @Author: Liu Weilong
 * @Date: 2021-02-01 16:36:25
 * @LastEditors: Liu Weilong 
 * @LastEditTime: 2021-02-01 16:47:17
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

        const std::string config_path_;
        unsigned int length_;
        double error_th_;
    };
    VerticalLineExtractorOptions  options_;
};
VerticalLineExtractor::
VerticalLineExtractorOptions::VerticalLineExtractorOptions(const string & path)
{
    cv::FileStorage fsread(config.c_str(), CV_STORAGE_READ);
    cv::Mat R1, R2, P1, P2, Q, rmap[2][2];
    if (fsread.isOpened())
    {
        fsread["M1"] >> M1;
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
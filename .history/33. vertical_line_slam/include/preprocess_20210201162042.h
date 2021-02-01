/*
 * @Author: Liu Weilong
 * @Date: 2021-01-24 10:48:48
 * @LastEditors: Liu Weilong 
 * @LastEditTime: 2021-01-24 15:10:24
 * @FilePath: /ORB_SLAM2/Examples/sunny_orb/include/preprocess.h
 * @Description: 
 */

#include <string>
#include <vector>
#include <iostream>

#include "opencv2/core/core.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace std;

class MyneyePreprocessor
{
    public:
    MyneyePreprocessor(const string & config);
    bool UnDistort(const cv::Mat & img_l_raw, const cv::Mat & img_r_raw,
                   cv::Mat & img_l,cv::Mat & img_r);
    bool HistogramMatching(const cv::Mat & img_pre,cv::Mat & img_cur) = delete;

    private:
    void LoadParams(const string & config);

    private:
    cv::Mat M1l,M2l,M1r,M2r;
};


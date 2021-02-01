/*
 * @Author: Liu Weilong
 * @Date: 2021-02-01 16:36:25
 * @LastEditors: Liu Weilong 
 * @LastEditTime: 2021-02-01 16:41:33
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
};

void 
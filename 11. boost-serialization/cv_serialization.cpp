/*
 * @Author: Liu Weilong
 * @Date: 2021-01-22 13:25:27
 * @LastEditors: Liu Weilong 
 * @LastEditTime: 2021-01-22 17:32:00
 * @FilePath: /3rd-test-learning/11. boost-serialization/cv_serialization.cpp
 * @Description: 
 *              主要用于 vector<Mat> vector<Point_<T>> Mat 进行序列化
 */
#include <iostream>
#include <vector>

#include "opencv2/core/core.hpp"
#include "boost/archive/text_iarchive.hpp"
using namespace std;

template<class Archive>
void serialize(Archive &ar, cv::Mat& mat, const unsigned int)
{
    int cols, rows, type;
    bool continuous;

    if (Archive::is_saving::value) {
        cols = mat.cols; rows = mat.rows; type = mat.type();
        continuous = mat.isContinuous();
    }

    ar & cols & rows & type & continuous;

    if (Archive::is_loading::value)
        mat.create(rows, cols, type);

    if (continuous) {
        const unsigned int data_size = rows * cols * mat.elemSize();
        ar & boost::serialization::make_array(mat.ptr(), data_size);
    }
    else {
        const unsigned int row_size = cols*mat.elemSize();
        for (int i = 0; i < rows; i++) {
            ar & boost::serialization::make_array(mat.ptr(i), row_size);
        }
    }
}

template<class Archive,typename T>
void serialize(Archive &ar, cv::Point_<T>& point, const unsigned int)
{
    ar & point.x;
    ar & point.y;
}

class Frame
{
    public:

    template<typename Archive>
    void serialize(Archive &ar, const unsigned int);
    
    vector<cv::Mat> imgs_; 
    vector<cv::Point2f> pts_;
    cv::Mat ref_;
};

template<typename Archive>
void Frame::serialize(Archive &ar, const unsigned int)
{
    ar & imgs_;
    ar & pts_;
    ar & ref_;
}

int main()
{
    
}
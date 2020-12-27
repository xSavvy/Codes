/*
 * @Author: Liu Weilong
 * @Date: 2020-12-24 14:56:20
 * @LastEditors: Liu Weilong 
 * @LastEditTime: 2020-12-24 15:19:41
 * @FilePath: /3rd-test-learning/26. opencv/basic/basic_mat_operator.cpp
 * @Description: 
 */

#include <iostream>

#include "opencv2/core/core.hpp"
using namespace std;

int main()
{
    cv::FileStorage fin("../basic/mat_storage.yaml",CV_STORAGE_READ);
// =============================== 矩阵读取 ====================================
    cv::Mat WHAT;
    fin["WHAT"]>>WHAT;
    for(int row = 0;row<WHAT.rows;row++)
    {
        for(int col = 0;col<WHAT.cols;col++)
        {cout<< WHAT.at<double>(row,col)<<" ";}
        cout<<endl;
    }
// =============================== 矩阵部分数值处理 =============================
    WHAT(cv::Range(0,2),cv::Range(0,2))*=2;
    for(int row = 0;row<WHAT.rows;row++)
    {
        for(int col = 0;col<WHAT.cols;col++)
        {cout<< WHAT.at<double>(row,col)<<" ";}
        cout<<endl;
    }
// =============================== 矩阵浅拷贝 ================================== 
    cv::Mat what = WHAT(cv::Range(0,2),cv::Range(0,2));
    what*=2;
    for(int row = 0;row<WHAT.rows;row++)
    {
        for(int col = 0;col<WHAT.cols;col++)
        {cout<< WHAT.at<double>(row,col)<<" ";}
        cout<<endl;
    }

    cout<<WHAT;
// =============================== ??? =======================================

    return 0;
}
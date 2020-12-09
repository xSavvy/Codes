/*
 * @Author: Liu Weilong
 * @Date: 2020-12-08 19:12:09
 * @LastEditors: Liu Weilong
 * @LastEditTime: 2020-12-08 19:24:48
 * @Description: 测试SVD
 */

#include "Eigen/Eigen"
#include <iostream>
using namespace std;

int main()
{

    Eigen::MatrixXd rm = Eigen::MatrixXd::Random(5,3);
    Eigen::JacobiSVD<Eigen::MatrixXd> svd(rm,Eigen::ComputeThinU|Eigen::ComputeThinV);
    cout<<svd.matrixU()<<endl;
    cout<<"=================================="<<endl;
    cout<<svd.matrixV()<<endl;
}
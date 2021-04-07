/*
 * @Author: Liu Weilong
 * @Date: 2020-12-08 19:12:09
 * @LastEditors: Liu Weilong
 * @LastEditTime: 2021-04-07 08:04:51
 * @Description: 测试SVD
 * 
 * 1. 测试SVD 求解非零
 * 
 * 
 */

#include "Eigen/Eigen"
#include <iostream>
using namespace std;

int main()
{
    Eigen::MatrixXd rm = Eigen::MatrixXd::Random(200,3);
    Eigen::MatrixXd zeros = Eigen::MatrixXd::Zero(200,1);
    Eigen::JacobiSVD<Eigen::MatrixXd> svd(rm,Eigen::ComputeFullU|Eigen::ComputeFullV);
    cout<<svd.matrixU()<<endl;
    cout<<"=================================="<<endl;
    cout<<svd.matrixV()<<endl;
    Eigen::MatrixXd result = svd.solve(zeros);
    cout<<"=================================="<<endl;
    cout<<result.transpose()<<endl;
    cout<<"=================================="<<endl;
    cout<<svd.singularValues().transpose()<<endl;
    cout<<svd.singularValues().tail<2>()<<endl;
    
}
/*
 * @Author: Liu Weilong
 * @Date: 2020-12-08 19:12:09
 * @LastEditors: Liu Weilong 
 * @LastEditTime: 2021-04-07 11:26:07
 * @Description: 测试SVD
 * 
 * 1. 测试SVD 求解非零
 * 
 * 
 */

#include "Eigen/Eigen"
#include <iostream>
#include <vector>
using namespace std;

class TESTSVD
{
    public:
    
    TESTSVD(){
        for(int i =0 ;i<10;i++)
        {
            array.push_back(Eigen::Matrix<double,5,3>::Random());
        }
    }

    void compute()
    {
        Eigen::MatrixXd rm (5*array.size(),3);
        for(int i =0 ;i<10;i++)
        {
            rm.block<5,3>(5*i,0) = array[i];
        }
        Eigen::JacobiSVD<Eigen::MatrixXd> svd(rm,Eigen::ComputeThinU|Eigen::ComputeThinV);
        svd.computeV();
        svd.matrixV();
    }
    vector<Eigen::Matrix<double,5,3>> array;  
};




int main()
{
    Eigen::MatrixXd rm = Eigen::MatrixXd::Random(200,3);
    Eigen::MatrixXd zeros = Eigen::MatrixXd::Zero(200,1);
    Eigen::JacobiSVD<Eigen::MatrixXd> svd(rm,Eigen::ComputeThinU|Eigen::ComputeThinV);
    cout<<svd.matrixU()<<endl;
    cout<<"=================================="<<endl;
    cout<<svd.matrixV()<<endl;
    Eigen::MatrixXd result = svd.solve(zeros);
    cout<<"=================================="<<endl;
    cout<<result.transpose()<<endl;
    cout<<"=================================="<<endl;
    cout<<svd.singularValues().transpose()<<endl;
    cout<<svd.singularValues().tail<2>()<<endl;
    
    TESTSVD  p ;
}
/*
 * @Author: Liu Weilong
 * @Date: 2020-09-25 07:20:55
 * @LastEditors: Liu Weilong
 * @LastEditTime: 2020-09-25 07:37:16
 * @Description: Eigen Map 使用
 */


#include "eigen3/Eigen/Eigen"
#include <iostream>
using namespace std;
using namespace Eigen;
int main(int argc,char **argv)
{
    double _da [3]{1.0,2.0,3.0};
    Map<Matrix<double,3,1>> m_da(_da);

    for(int i =0;i<m_da.rows();i++)
    {
        cout<<m_da(i)<<endl;
    }
    return 0;
}

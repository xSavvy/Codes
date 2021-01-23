/*
 * @Author: Liu Weilong
 * @Date: 2021-01-22 18:44:13
 * @LastEditors: Liu Weilong
 * @LastEditTime: 2021-01-22 19:33:10
 * @Description: 
 */

#include <iostream>

#include "Eigen/Eigen"

using namespace std;

// LDU 
template <typename T,int M,int N>
bool GaussianElimination(const Eigen::Matrix<T,M,N> raw_matrix,
                         Eigen::Matrix<T,M,M>& L,
                         Eigen::Matrix<T,M,M>& D,
                         Eigen::Matrix<T,M,N>& U)
{
    Eigen::Matrix<T,M,N> raw_copy = raw_matrix;
    Eigen::Matrix<T,M,M> L_matrix = Eigen::Matrix<T,M,M>::Identity();
    
    // 求 L
    for(int i=0;i<N;i++)
    {
        for(int j=i+1;j<M;j++)
        {
            double scale = -1*raw_matrix(j,i)/raw_matrix(i,i);
            auto row = raw_matrix.row(i);
            raw_matrix.row(j) += scale* row;
            auto L_row = L_matrix().row(i);
            L_matrix.row(j) += scale * L_row;
        }
    }
    
    
    

    



}


int main()
{
    Eigen::Matrix3d temp;
    temp.block<3,3>(0,0);

}




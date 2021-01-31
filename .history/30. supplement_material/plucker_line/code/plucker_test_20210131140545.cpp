/*
 * @Author: Liu Weilong
 * @Date: 2021-01-21 17:41:14
 * @LastEditors: Liu Weilong 
 * @LastEditTime: 2021-01-31 14:05:44
 * @FilePath: /3rd-test-learning/30. supplement_material/plucker_line/code/plucker_test.cpp
 * @Description: 
 * 
 *              Plucker 代码验证
 *              1. 四个点进行验证得到 pi 和 plucker
 *              2. 两个点进行验证 plucker    
 *              3. 对比两个plucker
 * 
 * 
 * 
 */

#include "plucker.h"

int main()
{
    Eigen::Vector3d line_s,line_e,c1,c2;
    line_s << 3,3,3;
    line_e << 3,3,0;
    c1 << 1,2,3;
    c2 << 2,2,6;

    Eigen::Vector3d l,m;
    l = line_s-line_e;
    m = line_s.cross(l);
    
    std::cout<<"the direct plucker is "<<endl<<l.transpose()<<endl<<m.transpose()<<endl;

    Eigen::Vector4d pi_1,pi_2;
    GeneratePlane(c1,line_s,line_e,pi_1);
    GeneratePlane(c2,line_s,line_e,pi_2);
    
    Eigen::Matrix<double,6,1> plucker;
    GeneratorPlucker(pi_1,pi_2,plucker);

    std::cout<<"the indirect plucker is "<<endl<<plucker.transpose()<<endl;
    
    // 发现求出来的线是对称的
    

    
    return 0;
}
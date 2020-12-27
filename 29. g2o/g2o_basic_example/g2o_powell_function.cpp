/*
 * @Author: Liu Weilong
 * @Date: 2020-12-27 18:22:47
 * @LastEditors: Liu Weilong 
 * @LastEditTime: 2020-12-27 19:28:21
 * @FilePath: /3rd-test-learning/29. g2o/g2o_basic_example/g2o_powell_function.cpp
 * @Description: 
 */


#include "VE_self_powell_function.h"
using namespace std;
int main()
{
    X * vx1 = new X();
    X * vx2 = new X();
    X * vx3 = new X();
    X * vx4 = new X();

    X4 * vx = new X4();
    
    typedef g2o::BlockSolver<g2o::BlockSolverTraits<4,10>> BlockSolverType;
    typedef g2o::LinearSolverDense<g2o::BlockSolverX::PoseMatrixType> LinearSolverType;
    
    // 创建求解器
    auto solver = new g2o::OptimizationAlgorithmGaussNewton(
        g2o::make_unique<g2o::BlockSolverX>(g2o::make_unique<LinearSolverType>()));
    g2o::SparseOptimizer optimizer;     // 图模型
    optimizer.setAlgorithm(solver);   // 设置求解器
    optimizer.setVerbose(true);       // 打开调试输出

    double dx1=3.0,dx2=-1.0,dx3=0.0,dx4=1.0;

    // vx1->setId(0);
    // vx1->setEstimate(dx1);
    // optimizer.addVertex(vx1);
    // vx2->setId(1);
    // vx2->setEstimate(dx2);
    // optimizer.addVertex(vx2);
    // vx3->setId(2);
    // vx3->setEstimate(dx3);
    // optimizer.addVertex(vx3);
    // vx4->setId(3);
    // vx4->setEstimate(dx4);
    // optimizer.addVertex(vx4);
    vx->setEstimate(Eigen::Vector4d(dx1,dx2,dx3,dx4));
    vx->setId(0);
    optimizer.addVertex(vx);

    F1 * ef1 = new F1();
    F2 * ef2 = new F2();
    F3F4 * ef3f4 = new F3F4();

    ef1->setVertex(0,vx);
    ef2->setVertex(0,vx);
    ef3f4->setVertex(0,vx);

    // ef1->setId(0);
    // ef2->setId(1);
    // ef3f4->setId(2);
    
    // ef1->setVertex(0,vx1);
    // ef1->setVertex(1,vx2);
    // ef2->setVertex(0,vx3);
    // ef2->setVertex(1,vx4);
    // ef3f4->getVertices().resize(4,nullptr);
    // ef3f4->resize(6);
    // ef3f4->setVertex(0,vx1);
    // ef3f4->setVertex(1,vx2);
    // ef3f4->setVertex(2,vx3);
    // ef3f4->setVertex(3,vx4);
  
    ef1->setInformation(Eigen::Matrix<double,1,1>::Identity());
    ef2->setInformation(Eigen::Matrix<double,1,1>::Identity());
    ef3f4->setInformation(Eigen::Matrix<double,2,2>::Identity());

    optimizer.addEdge(ef1);
    optimizer.addEdge(ef2);
    optimizer.addEdge(ef3f4);

    cout << "start optimization" << endl;
    chrono::steady_clock::time_point t1 = chrono::steady_clock::now();
    optimizer.initializeOptimization();
    optimizer.optimize(10);
    chrono::steady_clock::time_point t2 = chrono::steady_clock::now();
    chrono::duration<double> time_used = chrono::duration_cast<chrono::duration<double>>(t2 - t1);
    cout << "solve time cost = " << time_used.count() << " seconds. " << endl;

    cout<<"x1 is "<<vx1->estimate()<<endl;
    cout<<"x2 is "<<vx2->estimate()<<endl;
    cout<<"x3 is "<<vx3->estimate()<<endl;
    cout<<"x4 is "<<vx4->estimate()<<endl;
    
    return 0;
}
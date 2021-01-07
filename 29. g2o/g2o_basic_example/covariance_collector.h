/*
 * @Author: Liu Weilong
 * @Date: 2021-01-07 16:06:50
 * @LastEditors: Liu Weilong 
 * @LastEditTime: 2021-01-07 19:45:00
 * @FilePath: /3rd-test-learning/29. g2o/g2o_basic_example/covariance_collector.h
 * @Description: 
 * 
 *              这个类专门用于计算 协方差
 * 
 * 
 */
#include <iostream>
#include <fstream>
#include <vector>
#include <map>


#include "g2o/core/base_binary_edge.h"
#include "g2o/core/base_unary_edge.h"
#include "Eigen/Eigen"


#define _S_COV_COLLECTOR_ namespace cov_collector{
#define _E_COV_COLLECTOR_ };


_S_COV_COLLECTOR_

class CovCollector
{
    public:

    template<int D, typename E, typename VertexXi>
    void push_back(g2o::BaseUnaryEdge<D,E,VertexXi>* edge_ptr);
    
    template<int D, typename E, typename VertexXi, typename VertexXj>
    void push_back(g2o::BaseBinaryEdge<D,E,VertexXi,VertexXj>* edge_ptr);

    Eigen::MatrixXd computeHessian();
    
    private:      
    std::vector<g2o::OptimizableGraph::Edge * > edge_pool_;
    std::vector<bool> type_pool_;
    std::map<g2o::OptimizableGraph::Vertex *,Eigen::MatrixXd> vertex_pool_;

};

template<int D, typename E, typename VertexXi>
void CovCollector::push_back(g2o::BaseUnaryEdge<D,E,VertexXi>* edge_ptr)
{
    auto tmp_edge_ptr = reinterpret_cast<g2o::OptimizableGraph::Edge *>(edge_pool_)
    edge_pool_.push_back(tmp_edge_ptr);
    edge_ptr->linearizeOplus();
    typename g2o::BaseUnaryEdge<D,E,VertexXi>::JacobianXiOplusType jacobian = edge_ptr->jacobianOplusXi();
    Eigen::Matrix<double,VertexXi::Dimension,VertexXi::Dimension> hessian;
    hessian = jacobian.transpose()*jacobian;
    auto tmp_vertex_ptr_1 = reinterpret_cast<g2o::OptimizableGraph::Vertex *>(edge_ptr->_vertices.front());
    if(!vertex_pool_.count(tmp_vertex_ptr_1))
    {
        vertex_pool_[tmp_vertex_ptr_1].resize(VertexXi::Dimension,VertexXi::Dimension);
        vertex_pool_[tmp_vertex_ptr_1].setZero();
    }
    // TODO 维数check
    vertex_pool_[tmp_vertex_ptr_1]+=hessian;
    type_pool_.push_back(0);
}
template<int D, typename E, typename VertexXi, typename VertexXj>
void CovCollector::push_back(g2o::BaseBinaryEdge<D,E,VertexXi,VertexXj>* edge_ptr)
{
    auto tmp_edge_ptr = reinterpret_cast<g2o::OptimizableGraph::Edge *>(edge_pool_)
    edge_pool_.push_back(tmp_edge_ptr);
    edge_ptr->linearizeOplus();
    typename g2o::BaseBinaryEdge<D,E,VertexXi,VertexXj>::JacobianXiOplusType jacobian1 = edge_ptr->jacobianOplusXi();
    Eigen::Matrix<double,VertexXi::Dimension,VertexXi::Dimension> hessian1;
    hessian1 = jacobian1.transpose()*jacobian1;
    auto tmp_vertex_ptr_1 = reinterpret_cast<g2o::OptimizableGraph::Vertex *>(edge_ptr->_vertices.front());
    if(!vertex_pool_.count(tmp_vertex_ptr_1))
    {
        vertex_pool_[tmp_vertex_ptr_1].resize(VertexXi::Dimension,VertexXi::Dimension);
        vertex_pool_[tmp_vertex_ptr_1].setZero();
    }
    vertex_pool_[tmp_vertex_ptr_1]+=hessian1;

    auto tmp_vertex_ptr_2 = reinterpret_cast<g2o::OptimizableGraph::Vertex *>(edge_ptr->_vertices[1]);

    type_pool_.push_back(1);
}








_E_COV_COLLECTOR_


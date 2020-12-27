/*
 * @Author: Liu Weilong
 * @Date: 2020-12-24 14:07:52
 * @LastEditors: Liu Weilong 
 * @LastEditTime: 2020-12-24 14:10:41
 * @FilePath: /3rd-test-learning/29. g2o/VE_self_defined.h
 * @Description: 
 */

#pragma once
#include <iostream>

#include "g2o/core/base_unary_edge.h"
#include "g2o/core/base_vertex.h"
#include "Eigen/Eigen"

class CurveFittingVertex:public g2o::BaseVertex


// class CurveFittingEdge :public g2o::BaseUnaryEdge<>
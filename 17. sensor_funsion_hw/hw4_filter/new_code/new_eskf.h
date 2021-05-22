/*
 * @Author: Liu Weilong
 * @Date: 2021-05-22 21:24:56
 * @LastEditors: Liu Weilong
 * @LastEditTime: 2021-05-22 22:33:58
 * @Description: 
 * 验证算法思想
 * 
 * ESKF 仅为IMU + GPS 版本
 * 
 */

#include <iostream>

#include "data_loader.h"
#include "sophus/so3.hpp"

using namespace Eigen;
using Input = DataLoader::ElementInfo;


class ESKF
{
    public:

    class State
    {
        public:
        
        State(){
            posi.setZero();
            vel.setZero();
            theta.setZero();
            bias_acc.setZero();
            bias_gyro.setZero();
        }

        Vector3d posi;
        Vector3d vel;
        
        Vector3d theta;

        Vector3d bias_acc;
        Vector3d bias_gyro;
    };

    ESKF():ref_state_(),state_(),error_state_(){}

    // void Init(const State & init_state);

    void PushIMUInfo(const Input & input)
    {
        PropagateRef(input);
        PropagateMean(input);
    }

    // void PushObservation();

    private:

    // ! 还没有考虑初始化的问题
    void PropagateRef(const Input & input)
    {
        // propagate ref value
        double delta_tiemstamp = input.timestamp - last_timestamp_;
        Sophus::SO3d rotation_SO3 = Sophus::SO3d::exp(ref_state_.theta).matrix();
        Eigen::Matrix3d rotation = rotation_SO3.matrix();
        ref_state_.posi += delta_tiemstamp * ref_state_.vel 
                        +0.5*delta_tiemstamp* delta_tiemstamp *rotation * input.ref_acc;
        ref_state_.vel += delta_tiemstamp *rotation * input.ref_acc;
        ref_state_.theta = rotation_SO3 * Sophus::SO3d::exp(input.ref_gyro * delta_tiemstamp)).log();
    }

    void PropagateMean(const Input & input)
    {
        // propagate mean value
        double delta_tiemstamp = input.timestamp - last_timestamp_;
        Sophus::SO3d rotation_SO3 = Sophus::SO3d::exp(state_.theta).matrix();
        Eigen::Matrix3d rotation = rotation_SO3.matrix();
        state_.posi += delta_tiemstamp * rotation * state_.vel 
                        +0.5*delta_tiemstamp* delta_tiemstamp *Sophus::SO3d::exp(state_.theta).matrix() * input.ref_acc;
        state_.vel += delta_tiemstamp *Sophus::SO3d::exp(state_.theta).matrix() * input.ref_acc;
        state_.theta = (Sophus::SO3d::exp(state_.theta) * Sophus::SO3d::exp(input.ref_gyro * delta_tiemstamp)).log();        
    }
    
    // void PropagateErrorState(const Input & input);
    
    // void UpdateObservation();
    // void RefreshState();

    public:

    State ref_state_;
    State state_;
    State error_state_;
    double last_timestamp_;
};
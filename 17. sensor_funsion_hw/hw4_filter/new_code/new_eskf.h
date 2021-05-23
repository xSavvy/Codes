/*
 * @Author: Liu Weilong
 * @Date: 2021-05-22 21:24:56
 * @LastEditors: Liu Weilong
 * @LastEditTime: 2021-05-23 21:21:43
 * @Description: 
 * 验证算法思想
 * 
 * ESKF 仅为IMU + GPS 版本
 * 
 */
#pragma once

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
        // 进行中值处理
        if(last_timestamp_ == 0.)
            last_input_ = input;
        Input mid_value_input;
        mid_value_input = MidValue(last_input_,input);

        PropagateRef(mid_value_input);
        PropagateMean(mid_value_input);
        last_timestamp_ =  input.timestamp;
        last_input_ = input;
    }

    // void PushObservation();

    const State & GetRefState()const{return ref_state_;}
    const State & GetState()const{return state_;}

    private:

    // ! 还没有考虑初始化的问题
    void PropagateRef(const Input & input)
    {
        // propagate ref value
        double delta_tiemstamp = input.timestamp - last_timestamp_;

        Sophus::SO3d rotation_SO3 = Sophus::SO3d::exp(ref_state_.theta).matrix();
        // Eigen::Matrix3d rotation = (rotation_SO3*Sophus::SO3d::exp(input.ref_gyro * delta_tiemstamp)).matrix();
        Eigen::Matrix3d rotation = (rotation_SO3).matrix();
        
        ref_state_.posi += delta_tiemstamp * ref_state_.vel 
                        +0.5*delta_tiemstamp* delta_tiemstamp *rotation * input.ref_acc;
        ref_state_.posi += 0.5 * delta_tiemstamp *delta_tiemstamp * g;
        ref_state_.vel += delta_tiemstamp *rotation * input.ref_acc;
        ref_state_.vel += delta_tiemstamp *g;
        ref_state_.theta = (rotation_SO3 * Sophus::SO3d::exp(input.ref_gyro * delta_tiemstamp)).log();
    }

    void PropagateMean(const Input & input)
    {
        // propagate mean value
        double delta_tiemstamp = input.timestamp - last_timestamp_;
        Sophus::SO3d rotation_SO3 = Sophus::SO3d::exp(state_.theta).matrix();
        Eigen::Matrix3d rotation = rotation_SO3.matrix();
        state_.posi += delta_tiemstamp * rotation * state_.vel 
                        +0.5*delta_tiemstamp* delta_tiemstamp *Sophus::SO3d::exp(state_.theta).matrix() * input.meas_acc;
        state_.posi += 0.5*delta_tiemstamp*delta_tiemstamp*g;
        state_.vel += delta_tiemstamp *Sophus::SO3d::exp(state_.theta).matrix() * input.meas_acc;
        state_.vel += delta_tiemstamp * g;
        state_.theta = (Sophus::SO3d::exp(state_.theta) * Sophus::SO3d::exp(input.meas_gyro * delta_tiemstamp)).log();        
    }
    
    // void PropagateErrorState(const Input & input);
    
    // void UpdateObservation();
    // void RefreshState();

    Input MidValue(const Input & pre_input, const Input & cur_input)
    {
        Input result;
        result.meas_acc = 0.5*(pre_input.meas_acc+cur_input.meas_acc);
        result.meas_gyro = 0.5*(pre_input.meas_gyro+cur_input.meas_gyro);
        result.ref_acc = 0.5*(pre_input.ref_acc+cur_input.ref_acc);
        result.ref_gyro = 0.5*(pre_input.ref_gyro+cur_input.ref_gyro);
        result.atti = cur_input.atti;
        result.posi = cur_input.posi;
        result.timestamp = cur_input.timestamp;
        return result;
    }
    
    public:
    static Eigen::Vector3d g;
    
    Input last_input_;

    State ref_state_;
    State state_;
    State error_state_;
    double last_timestamp_;
};

Eigen::Vector3d ESKF::g = Eigen::Vector3d(0,0,9.7803253359);
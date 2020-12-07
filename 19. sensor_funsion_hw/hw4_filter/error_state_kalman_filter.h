/*
 * @Author: Liu Weilong
 * @Date: 2020-12-04 23:13:20
 * @LastEditors: Liu Weilong
 * @LastEditTime: 2020-12-06 01:19:22
 * @Description: 之前对于问题粗浅的理解导致现在代码写得非常难受
 */
#include "kalman_filter_interface.h"
#include "measure_module.h"
#include "yaml-cpp/yaml.h"

using namespace std;

// #define UPDATESO3

#define SIMULATION

#define PHI_IDX 0
#define VEL_IDX 3
#define POS_IDX 6
#define BG_IDX 9
#define BA_IDX 12
#define NG_IDX 0
#define NA_IDX 3
#define NGW_IDX 6
#define NAW_IDX 9

class ESKF:public EKFInterface<IMU,Laser,15>
{
    public:
    
    ESKF()=default;
    ESKF(const Covar & covar,const State & s,const IMUNoise & in, const LaserNoise & ln);
    // ESKF(const string & init_path);
    
    // interface
    virtual Eigen::MatrixXd GetOM()const override;
    virtual void Predict(const IMU & u) override;
    virtual void Correct(const Laser & z) override;
    ~ESKF(){}

    // internal
    void UpdateState();

    private:
    using EKFInterface::mState;
    using EKFInterface::mCovar;
    State mdState = State::Zero();
    // 这个是用于迭代 nominal state
    State mPreState = State::Zero();
    IMUNoise mIN;
    LaserNoise mLN;
    IMU mpreIMU;
    IMU mpreLaser;
};

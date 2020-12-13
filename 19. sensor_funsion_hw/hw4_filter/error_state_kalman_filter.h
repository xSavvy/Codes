/*
 * @Author: Liu Weilong
 * @Date: 2020-12-04 23:13:20
 * @LastEditors: Liu Weilong
 * @LastEditTime: 2020-12-13 20:20:03
 * @Description: 之前对于问题粗浅的理解导致现在代码写得非常难受
 * 
 *               2020.12.13 
 *               现在基本确定 ESKF 流程为
 *               1. ErrorState 、 State 双递推
 *                  ES_k+1 = (I+F*delta_t)*ES_k + G*N 
 *                  这里的 N 哪怕期望是0, 这里也要附上一个随机值
 *                  不然ES_k+1 不会有任何修正效果
 *               2. Observeration - State 得到 ErrorState Obser
 *               3. 使用ErrorStateOb 放入 ErrorState KF 框架当中继续进行更新
 *               4. ErrorState 被更新到State 当中
 *                  IMU 的Bias 是否更新， 在GeYao的实现中，会check 一下Cov 是否收敛。 
 *               5. ErrorState 置零 然后从1 继续进行
 *
 *
 *               对于预积分的方法
 *               类似的误差分析主要是用于获取方差
 *
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

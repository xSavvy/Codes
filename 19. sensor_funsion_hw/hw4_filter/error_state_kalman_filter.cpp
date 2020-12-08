/*
 * @Author: Liu Weilong
 * @Date: 2020-12-05 09:48:17
 * @LastEditors: Liu Weilong
 * @LastEditTime: 2020-12-07 21:17:55
 * @Description:  ESKF 内部函数实现
 */

#include "error_state_kalman_filter.h"

ESKF::ESKF(const Covar & c,const State & s,
           const IMUNoise & in, const LaserNoise & ln)
{
    mIN = in;   
    mLN = ln;
    mState = s;
    mCovar = c;
}

//TODO not check mIN’s mCov

void ESKF::Predict(const IMU & u)
{

    static Eigen::Vector3d gravity_vector_w(0,0,9.794841972265039942);
    // update expectation
    // calculate imu measure without bias 
    Eigen::Vector3d AccNB = u.mAccel - mState.block<3,1>(BA_IDX,0);
    Eigen::Vector3d GyroNB = u.mGyro - mState.block<3,1>(BG_IDX,0);
    Eigen::Vector3d so3_b_n = mState.block<3,1>(PHI_IDX,0);
    Eigen::Matrix3d R_b_n = Sophus::SO3d::exp(so3_b_n).matrix();
    Eigen::Vector3d AccNBNG = AccNB + R_b_n.transpose()*gravity_vector_w;
    // calculate transfer equation 
    // the deritive form of error state is as below
    // EX_dot = F* EX + G * N
    // then the transfer equation can be written as below
    // EX_k+1 = (I+F*delta_t)EX_k + G*delta_t*N

    Eigen::Matrix<double,15,15> F = Eigen::Matrix<double,15,15>::Zero();
    F.block<3,3>(PHI_IDX,PHI_IDX) = -1*Sophus::SO3d::hat(GyroNB);
    F.block<3,3>(PHI_IDX,BG_IDX) = -1 * Eigen::Matrix<double,3,3>::Identity();
    F.block<3,3>(VEL_IDX,PHI_IDX) = -1*R_b_n*Sophus::SO3d::hat(AccNB);
    F.block<3,3>(VEL_IDX,BA_IDX) = -1*R_b_n;
    F.block<3,3>(VEL_IDX,POS_IDX) = Eigen::Matrix<double,3,3>::Identity();
    
    Eigen::Matrix<double,15,12> G = Eigen::Matrix<double,15,12>::Zero();
    
    G.block<3,3>(PHI_IDX,NG_IDX) = Eigen::Matrix<double,3,3>::Identity();
    G.block<3,3>(VEL_IDX,NA_IDX) = R_b_n;
    G.block<3,3>(BG_IDX,NG_IDX) = Eigen::Matrix<double,3,3>::Identity();
    G.block<3,3>(BA_IDX,NA_IDX) = Eigen::Matrix<double,3,3>::Identity();


#ifdef SIMULATION
    double delta_t = 0.01;
#else
    double delta_t = u.mTime - mpreIMU.mTime;
    if(delta_t <0.0)
    {
        std::cerr<<"[ERROR]: there must be something wrong with the imu timestamp!"<<endl;
        std::abort();
    }
#endif 

    // Nominal State Update
    Sophus::SO3d so3_k_n = Sophus::SO3d::exp(mState.block<3,1>(PHI_IDX,0));
    Sophus::SO3d so3_delta = Sophus::SO3d::exp(GyroNB*delta_t);
    
    mState.block<3,1>(PHI_IDX,0) = (so3_k_n*so3_delta).log();

    mState.block<3,1>(POS_IDX,0) += mState.block<3,1>(VEL_IDX,0)*delta_t +
                                    0.5*(so3_k_n*AccNB+gravity_vector_w)*delta_t*delta_t;

    mState.block<3,1>(VEL_IDX,0) += (so3_k_n*AccNB+gravity_vector_w)*delta_t;
    
    // here assuming the noise is normal distribution
    mdState = mdState + F*delta_t*mdState;
    
    // update covariance
    Eigen::Matrix<double,15,15> I = Eigen::Matrix<double,15,15>::Identity();
    mCovar = (I+F*delta_t)*mCovar*(I+F*delta_t).transpose() + G*delta_t*mIN.mCov*(G*delta_t).transpose();

}

void ESKF::Correct(const Laser & z)
{
    // build the observation equation
    // Z = H*X + D*N
    // Here the mCovar is the piror cov
    Eigen::Matrix<double,6,15> H = Eigen::Matrix<double,6,15>::Zero();
    H.block<3,3>(0,PHI_IDX) = Eigen::Matrix<double,3,3>::Identity();
    H.block<3,3>(3,POS_IDX) = Eigen::Matrix<double,3,3>::Identity();
    Eigen::Matrix<double,15,6> K ;
    K = mCovar*H.transpose()*(H*mCovar*H.transpose()+mLN.mCov).inverse();
    
    // the Updated mCovar is the postier cov
    Eigen::Matrix<double,15,15> I = Eigen::Matrix<double,15,15>::Identity();
    mCovar =(I-K*H)*mCovar*(I-K*H).transpose() + K*mLN.mCov*K.transpose();
#ifdef UPDATESO3
    
#else
    Eigen::Matrix<double,6,1> vz;
    vz.block<3,1>(0,0)=z.mDRot;
    vz.block<3,1>(3,0)=z.mDTra;
    Eigen::Matrix<double,15,1> dState = mState -mPreState;
    Sophus::SO3d so3_n_old = Sophus::SO3d::exp(-1*mPreState.block<3,1>(PHI_IDX,0));
    Sophus::SO3d so3_new_n = Sophus::SO3d::exp(mState.block<3,1>(PHI_IDX,0));

    dState.block<3,1>(PHI_IDX,0) = (so3_n_old*so3_new_n).log(); 

    cout<<"the current delta Angle is "<<endl
    <<  dState.block<3,1>(PHI_IDX,0).transpose()<<endl;
    cout<<"the current delta Pos is "<<endl
    <<  (so3_n_old*dState.block<3,1>(POS_IDX,0)).transpose()<<endl;
    dState.block<3,1>(POS_IDX,0) = so3_n_old*dState.block<3,1>(POS_IDX,0);
    // Eigen::Matrix<double,6,1> ddState = vz-H*(dState);
    // so3_n_old = Sophus::SO3d::exp(-1*vz.block<3,1>(PHI_IDX,0));
    // so3_new_n = Sophus::SO3d::exp(ddState.block<3,1>(PHI_IDX,0));
    // mdState = K*(vz-H*(dState));
    cout<< "the residual is "<<endl
    <<(vz-H*(dState)).transpose()<<endl;
    cout<<"the K is "<<endl
    <<K<<endl;
#endif

    UpdateState();
    
}

Eigen::MatrixXd ESKF::GetOM()const
{

}
void ESKF::UpdateState()
{
    mPreState = mState;
    cout<<"the current mState is "<<endl
    << mState.transpose()<<endl;
    cout<<"the current mdState is "<<endl
    << mdState.transpose()<<endl;
    mState.block<15,1>(0,0) += mdState.block<15,1>(0,0);
    // Eigen::Vector3d so3_old_n = mState.block<3,1>(PHI_IDX,0);
    // Eigen::Vector3d so3_new_old = mdState.block<3,1>(PHI_IDX,0);
    // mState.block<3,1>(PHI_IDX,0) = (Sophus::SO3d::exp(so3_old_n)*Sophus::SO3d::exp(so3_new_old)).log();
    cout<<"the current mState is "<<endl
    << mState.transpose()<<endl;
    mdState.setZero();
}
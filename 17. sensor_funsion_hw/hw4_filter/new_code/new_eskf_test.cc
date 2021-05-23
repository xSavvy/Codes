/*
 * @Author: Liu Weilong
 * @Date: 2021-05-22 22:34:25
 * @LastEditors: Liu Weilong
 * @LastEditTime: 2021-05-23 21:03:28
 * @Description:
 * 1. 角度递推基本没有问题
 * 2. 位置递推还是不行
 */
#include "new_eskf.h"

int main()
{
    DataLoader dl("../all_paths.yml");
    DataLoader::ElementInfo info;
    DataLoader::ElementInfo oldest_info;
    
    dl.GetInfo(oldest_info);
    dl.Reset();
    
    ESKF eskf;

    int count = 0;
    int count_th = 99990;
    while(dl.GetInfo(info))
    {
        eskf.PushIMUInfo(info);
        count++;
        if(count == count_th) break;
    }

    auto state = eskf.GetState();
    auto ref_state = eskf.GetRefState();
    
    // 对比 state 和 ref_state
    cout<<"----- State-----"<<endl;
    cout<<"State Position :"<<state.posi.transpose()<<endl;
    cout<<"State Attitude :"<<state.theta.transpose()<<endl;
    cout<<"----- Ref State-----"<<endl;
    cout<<"Ref State Position :"<<ref_state.posi.transpose()<<endl;
    cout<<"Ref State Attitude :"<<ref_state.theta.transpose()<<endl;    
    
    // 对比真值
    Sophus::SO3d rotation_SO3(Eigen::Quaterniond(info.atti(0),info.atti(1),info.atti(2),info.atti(3)));

    cout<<"the real position :"<< (info.posi - oldest_info.posi).transpose()<<endl;
    cout<<"the real attitude :"<< rotation_SO3.log().transpose()<<endl;
    
    return 0;
}
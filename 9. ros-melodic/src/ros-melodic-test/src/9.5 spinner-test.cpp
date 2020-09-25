/*
 * @Author: Liu Weilong
 * @Date: 2020-09-25 08:56:51
 * @LastEditors: Liu Weilong 
 * @LastEditTime: 2020-09-25 09:22:13
 * @FilePath: /3rd-test-learning/9. ros-melodic/src/ros-melodic-test/src/9.5 spinner-test.cpp
 * @Description: 用于测试ros spin 的性质    
 */

#include <iostream>
#include <ros/ros.h>
#include <ros/timer.h>
using namespace std;

// spin callback 需要添加 ros::TimerEven& 作为参数
void print(const ros::TimerEvent& event){
    cout<<"===================================="<<endl;

    for (int i =0;i<30;i++)
    {
        cout<<i<<endl;
    }
}
void print1(const ros::TimerEvent& event){
    cout<<"===================================="<<endl;

    for (int i =30;i<60;i++)
    {
        cout<<i<<endl;
    }
}



int main(int argc,char **argv)
{
    // ros 不允许存在- . 等符号
    ros::init(argc,argv,"simple_spin_test");
    
    ros::NodeHandle nh;
    auto timer = nh.createTimer(ros::Duration(0.1),print);
    auto timer2 = nh.createTimer(ros::Duration(0.1),print1);
    // 单线程测试用例 是一个block spinner
    //ros::spin();
    // 多线程测试用例 会出现很明显的多线程运行情况
    ros::MultiThreadedSpinner spinners(4);
    spinners.spin(); // 也是一个block spinner 

    return 0;
}

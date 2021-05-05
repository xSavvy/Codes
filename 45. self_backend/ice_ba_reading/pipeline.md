<!--
 * @Author: Liu Weilong
 * @Date: 2021-05-04 09:24:25
 * @LastEditors: Liu Weilong
 * @LastEditTime: 2021-05-05 22:43:56
 * @Description: 
-->

### ICE-BA 主要流程
主要内容来自 Euroc_test.cpp
1. 得到照片
2. 得到标定参数
3. 计算视场角和mask  mask就是说在去畸变后，哪些pixel 是在视场角内，哪些不在，不在视场角内的数值为Oxff 在的为Ox00
4. 加载imu数据


----
各种标号看蒙了
输入: keypoint 的观测
输出: CF KF 

信息流打不通    不知道为什么



1. create_iba_frame
   
2. create_iba_frame -> PushCurrentFrame() 把初始的CurrentFrame数据 ， convert to InputLocalFrame m_ILF
    |__ ConvertCamera  转换相机坐标
    |__ ConvertDepth   转换深度 和 尺度
    |__ ConvertFeatureMeasurements 转换测量特征
        |__ 
    |__ 保存imu数据
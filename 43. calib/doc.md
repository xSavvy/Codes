<!--
 * @Author: Liu Weilong
 * @Date: 2021-04-08 20:11:49
 * @LastEditors: Liu Weilong
 * @LastEditTime: 2021-04-11 08:59:44
 * @Description: 
-->
### 梗概
1. rot 外参标定
2. imu gyro bias 标定
3. 机器人学中的状态估计，旋转误差状态分析

======
1. rot 外参标定
   $$
   \begin{aligned}
           R^{a2}_{a1} &= R^{b}_a R^{b2}_{b1} R^{a}_{b}
    \\
     &= R^{b}_a R^{b2}_{b1} (R^{b}_a)^T
     \\
     & = exp(R^b_a \theta_b)
     \\
     & = exp(\theta_a)
   \end{aligned}
   $$
   标定目标就是R^{b}_a

2. imu gyro bias 标定
   
   基础推导
   $$
    RR^T=I \rightarrow \dot{R}R^T + R\dot{R}^T = 0 \rightarrow \dot{R}  = -\omega × R\\
    R^TR=I \rightarrow \dot{R}^TR +R^T\dot{R} = 0\rightarrow \dot{R}^T   \\
    

   $$
   误差状态分析<font color = "Red">见3.</font>
   主体内容:

3. 机器人学中的状态估计，旋转误差状态分析
   P227
   $$
   nominal:\\
   \dot{C} = \omega \times C\\
   true:\\
   \cfrac{d}{dt}(1+\delta \theta\times)C = (\omega + \delta \omega)\times (1+\delta \theta \times)C \\
   left:\\
   
   \dot{\delta \theta×}C+(1+\delta \theta \times)\omega \times C \\
   left+right:\\
   \dot{\delta \theta×}+(1+\delta \theta \times)\omega \times = (\omega + \delta \omega)\times (1+\delta \theta \times)
   \\
   \dot{\delta \theta×} = (\omega + \delta \omega)\times (1+\delta \theta \times) - (1+\delta \theta \times)\omega \times
   \\
   formula 1：\\
   V1 \times V2 \times - V2 \times V1 \times = (V1 \times V2)\times
   \\
   continue:\\
   \begin{aligned}
      \dot{\delta \theta×} &= (\omega + \delta \omega)\times (1+\delta \theta \times) - (1+\delta \theta \times)\omega \times
      \\
      &= \omega \times + \omega \times \delta{\theta}\times + \delta{\omega}\times + \omega \times -\delta{\theta}\times \omega \times
      \\
      &=(\omega×\delta{\theta})\times + \delta{\omega}\times      
   \end{aligned}
   $$
   这里存在的符号正负号转变。认为只是符号定义的问题
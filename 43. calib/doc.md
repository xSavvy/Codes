<!--
 * @Author: Liu Weilong
 * @Date: 2021-04-08 20:11:49
 * @LastEditors: Liu Weilong
 * @LastEditTime: 2021-04-09 07:56:52
 * @Description: 
-->
### 梗概
1. rot 外参标定
2. imu gyro bias 标定

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
   误差状态分析
   $$
   nominal:\\
    exp(\dot{\theta}) = -\omega× exp(\theta) = exp(\theta)\omega ×
    \\
   true:\\
    \begin{aligned}
    exp(\dot{\theta})exp(\delta{\dot{\theta}}) &= -(\omega + b + n_{m})× exp(\theta)exp(\delta{\theta})
    \\
    exp(\dot{\theta})exp(\delta{\dot{\theta}}) &= -(\omega + b + n_{m})× exp(\theta)(1+\delta{\theta} ×)
    \\
    exp(\dot{\theta})(1 + \delta{\dot{\theta}}×) & = -(\omega + b + n_m)× exp(\theta) -(\omega + b + n_m)× exp(\theta)\theta×
    \\
   
    \end{aligned}

   $$
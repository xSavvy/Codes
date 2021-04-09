<!--
 * @Author: Liu Weilong
 * @Date: 2021-04-08 20:11:49
 * @LastEditors: Liu Weilong 
 * @LastEditTime: 2021-04-09 18:21:47
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
   标定目标就是$R^{b}_a$

2. imu gyro bias 标定
   
   基础推导
   $$
    RR^T=I \rightarrow \dot{R}R^T + R\dot{R}^T = 0 \rightarrow \dot{R}  = -\omega × R\\
    R^TR=I \rightarrow \dot{R}^TR +R^T\dot{R} = 0\rightarrow \dot{R}^T=(R\omega×)^T   \\
    

   $$
   误差状态分析
   $$
   nominal:\\
    \dot{exp({\theta})} = -\omega× exp(\theta) = exp(\theta)\omega ×
    \\
   $$
   这里一定要注意点的位置，因为这里还没有论证过
   $$
   \dot{exp(\theta)} = exp(\dot{\theta}) 
   $$
   之前的错误，应该就是这里导致的

   继续进行剩下内容的推导
   $$
   true:\\
    \begin{aligned}
    \dot{[exp({\theta})exp(\delta{{\theta}})]} &= -(\omega + b + n_{m})× exp(\theta)exp(\delta{\theta})
    \\

    left:
    \\
    \dot{[exp(\theta)(1+\delta \theta×)]} &= \dot{exp(\theta)} + exp(\theta) \dot{\delta \theta}× + \dot{exp(\theta)}\delta \theta×\\
    & = \dot{exp(\theta)}(1+\delta \theta×)+ exp(\theta)\dot{\delta \theta}×
    \\
    &= exp(\theta)\omega ×(1+\delta \theta ×) +exp(\theta)\dot{\delta \theta}×
    \\
    right:
    \\
    -(\omega + b + n_{m})× exp(\theta)exp(\delta{\theta})&=exp(\theta)(\omega + b + n_{m})×(1+\delta \theta)
    \\
    left+right:
    \\
    exp(\theta)\omega ×(1+\delta \theta ×) +exp(\theta)\dot{\delta \theta}× &= exp(\theta)(\omega + b + n_{m})×(1+\delta \theta)
    \\
    \omega ×(1+\delta \theta ×)+\dot{\delta \theta}× &= (\omega + b + n_{m})×(1+\delta \theta)
    \\
    \dot{\delta \theta}× &= b+n_m+
   \end{aligned}
   $$

   这里的推导存在问题，需要
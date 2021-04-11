<!--
 * @Author: Liu Weilong
 * @Date: 2021-04-08 20:11:49
<<<<<<< HEAD
 * @LastEditors: Liu Weilong
 * @LastEditTime: 2021-04-11 09:24:00
=======
 * @LastEditors: Liu Weilong 
 * @LastEditTime: 2021-04-09 18:21:47
>>>>>>> 3cb2ceffe630db243019b1e320c312308fa307e0
 * @Description: 
-->
### 梗概
1. rot 外参标定
2. imu gyro bias 标定
3. 机器人学中的状态估计，旋转误差状态分析
4. SO3 imu 预积分模块

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
   误差状态分析<font color = "Red">见3.</font>
   
   主体内容:

   imu的gyro预积分部分
   2.a 公式递推
   $$
   X_k+1 = f_k(X_k,b_k); 
   \\
   \begin{aligned}
      J^{X_{k+2}}_{b_k} &=J^{f_{k+1}}_{X_{k+1}}( J^{f_k}_{b_k}(b_k-\hat{b_k}))+ J^{f_{k+1}}_{b_{k+1}}(b_{k}-\hat{b_{k}})\\
      &=J^{X_{k+2}}_{X_{k+1}}( J^{X_{k+1}}_{b_k}(b_k-\hat{b_k}))+ J^{X_{k+2}}_{b_{k+1}}(b_{k}-\hat{b_{k}})
      \\
      &=( J^{X_{k+2}}_{b_k}(b_k-\hat{b_k}))+ J^{X_{k+2}}_{b_{k+1}}(b_{k}-\hat{b_{k}})      
   \end{aligned}
   $$
   具体推导<font color = "Red">见 32. vins_related/origin/VINS_MONO/Theory.md </font>
   $$
      In(\prod exp(\omega_i + b + n_i))
      = In(\prod exp(\omega_i + \hat{b} + n_i)) + J_{b}(b-\hat{b})
   $$

   然后，组建最小二乘单次求解即可得到b。(VINS的一种近似求解) 这里使用的是 Cholesky 的求解方式(Ax = b A是正定(方阵，对称+ determiant>0))
   
   实际上，应该是进行反复迭代更新 exp 的。

3. 机器人学中的状态估计，旋转误差状态分析
   P227
   $$
   nominal:\\
<<<<<<< HEAD
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

4. 预积分模块
=======
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
>>>>>>> 3cb2ceffe630db243019b1e320c312308fa307e0

<!--
 * @Author: Liu Weilong
 * @Date: 2021-02-04 07:35:18
 * @LastEditors: Liu Weilong
 * @LastEditTime: 2021-02-04 08:13:53
 * @Description: 
-->
### 线性系统速记 小手册
1. 定常系统的通解
   $$
   \begin{aligned}
    &\dot{x} = Ax + Bu\\
    & x = e^{At}x(0)+\int^{t}_0 e^{A(t-\tau)}Bu(\tau)d\tau
    \end{aligned}
    
    \\
    e^{At} = I+A+\frac{1}{2}A^2+\frac{1}{3!}A^3 ...+\frac{1}{n!}A^{n}...
   \\
   \begin{aligned}
    &y = Cx + Du\\
    &y = C[e^{At}x(0)+\int^{t}_0 e^{A(t-\tau)}Bu(\tau)d\tau]+Du
    \end{aligned}
     
   $$
   $e^{At}$ 可以通过CH 公式写成解析解
2. 
   
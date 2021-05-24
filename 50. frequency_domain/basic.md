<!--
 * @Author: Liu Weilong
 * @Date: 2021-05-24 19:30:14
 * @LastEditors: Liu Weilong
 * @LastEditTime: 2021-05-24 21:54:02
 * @Description: 
-->
Some Basic Conception in Frequency Analysis

### 主要内容如下:
1. Fourier 变换的一般作用
2. Fourier 变换的组成
3. Fourier 变换的正交基
4. Fourier 如何使用复数来估计实函数
5. Discrete Fourier 变换
6. Z 变换和 Discrete Fourier 变换之间的关系

-----

1. Fourier 变换的一般作用:
   
   函数拟合，主要思想就是用多个sin 或者 cos(sin 和 cos 是一样的，只差一个相位)来对函数进行拟合。 为什么可以拟合和拟合的精度，不是这里能够讨论得了的。
   
   但是，可以记住一个结论，能够拟合的函数有哪些特征？

2. Fourier 变化的组成:
   
   有了上面的概念之后，那么假设一个可以拟合的函数，就可以写成
   $$
    f(x) = \sum a_i sin(2\pi f_ix+\theta_i)
   $$
   在加上三角函数的一直基础性质:
   $$
    sin(\theta_1+\theta_2) = sin(\theta_1)cos(\theta_2)+cos(\theta_1)sin(\theta_2)
   $$
   之后，那个可以拟合的函数就可以写成
   $$
    \begin{aligned}
        f(x) &= \sum a_isin(2\pi f_ix+\theta_i)
        \\
        & =\sum [\underbrace{a_i cos(\theta_i)}_{= A_i}sin(2\pi f_ix)+ \underbrace{a_i sin(\theta_i)}_{=B_i}cos(2\pi f_ix)] 
        \\
        & = \sum [A_isin(2\pi f_ix)+ B_icos(2\pi f_ix)] 
    \end{aligned}
   $$
   这里为了让函数的上下幅度加入常数补偿

   $$
   f(x) = a_0 + \sum [A_isin(2\pi f_ix)+ B_icos(2\pi f_ix)] 
   $$

3. Fourier 的正交基:

   下面，开始引入Fourier的正交基的概念，并进一步推导公式成
   $$
   \begin{aligned}
      f(x) &= a_0 + \sum [A_isin(2\pi f_ix)+ B_icos(2\pi f_ix)]
      \\
       & = a_0 + \sum^N_{n=1} [A_isin(2\pi fnx)+ B_icos(2\pi fnx)]
   \end{aligned}
   $$

   也就是进一步把 $\sum a_isin(\theta_i + 2\pi f_ix)$ 规范化为  $\sum^N_{n=1} b_i sin(\theta_i + 2\pi fnx)$ 的表示

   3.1. 周期函数的基

   为了规范化，就需要先对比向量空间的基。
   
   组成向量空间的基的向量之间存在一个关系。
   
   $$
   a_i ^T a_j = 0
   $$

   那么，定义函数之间的是否正交，就是把函数看作一个区间内无限多维的向量。
   
   那么函数正交就可以定义为
   $$
   \int^{a}_{b} f_1(x)f_2(x)dx = 0
   $$

   这个时候
   $$
   \int^{\pi}_{-\pi} cos(x)sin(x)
   = 0
   $$
   严格正交

   进一步引出的正交关系有
   ![](./pic/1.png)

   由此,我们可以得出一个结论。
   
   如果我们想要去拟合一个周期为T函数，那么我们只需要找到$\cfrac{nT}{2\pi}$
   



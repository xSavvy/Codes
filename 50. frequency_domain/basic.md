<!--
 * @Author: Liu Weilong
 * @Date: 2021-05-24 19:30:14
 * @LastEditors: Liu Weilong
 * @LastEditTime: 2021-05-24 19:56:01
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
   现在，我们引入一个新的结论，让函数拟合从space domain 转向 frequency domain
   $$
    
   $$
   





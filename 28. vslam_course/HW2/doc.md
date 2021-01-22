<!--
 * @Author: Liu Weilong
 * @Date: 2021-01-16 22:12:11
 * @LastEditors: Liu Weilong 
 * @LastEditTime: 2021-01-22 17:58:55
 * @Description: 
-->
### 1. 熟悉 Eigen 矩阵运算
1. 在什么条件下，x 有解且唯⼀?<br>
   A为列满秩<br>
2. ⾼斯消元法的原理是什么?<br> 
   一种求逆的手段   $\rightarrow{LDU}$ 分解 <br>
   把左边的矩阵通过行运算变为单位阵,左边矩阵的就会出现在右边<br>
   i.e.
   $$
        \left[
        \begin{array}{cc|c}
        1 & 2 &1&0\\
        4 & 5 &0&1
        \end{array}
        \right]
        \rightarrow
        \left[
        \begin{array}{cc|c}
        1 & 0 & 1 & 0\\
        0 & 1 & \frac{4}{3} & \frac{1}{-3}
        \end{array}
        \right]
   $$
3. QR分解的原理?<br>
   
<!--
 * @Author: Liu Weilong
 * @Date: 2021-02-08 17:37:13
 * @LastEditors: Liu Weilong
 * @LastEditTime: 2021-02-08 18:15:08
 * @Description: 
-->
### Element of Quaternion 来自 indirect KF 目前还不知道是JPL 还是 Hamintion 的表示
1. 基本的定义\
a.1. Quaternion 定义\
$$
    q = q_4 + q_1i+q_2j+q_3k
\\
    q= \left[
        \begin{matrix}
            \pmb{q}\\
            q_4
        \end{matrix}
        \right]
        =\left[
        \begin{matrix}
            \pmb{k}\sin(\theta/2)\\
            \cos(\theta/2)
        \end{matrix}
        \right]
$$
a.2. Quaternion 性质\
 $$
    |q| = \sqrt{q^Tq} = \sqrt{|q|^2+q_4^2} =1
 $$
2. Quaternion 乘法 (类比SO3 的乘法)\

$$
\begin{aligned}
    q\otimes p &= (q_4 + q_1i+q_2j+q_3k)(p_4 + p_1i+p_2j+p_3k)
    \\
    &= L(q)p
    \\
    &=
    \left[
        \begin{matrix}
            q_4I-\pmb{q}×&& \pmb{q}\\
            -\pmb{q}^T&& q_4
        \end{matrix}
    \right]   
     \left[
        \begin{matrix}
           \pmb{p}\\
             p_4
        \end{matrix}
    \right]
    \\
    &= R(p)q
    \\
    &=
    \left[
        \begin{matrix}
            q_4I-\pmb{q}×&& \pmb{q}\\
            -\pmb{q}^T&& q_4
        \end{matrix}
    \right]   
     \left[
        \begin{matrix}
           \pmb{p}\\
             p_4
        \end{matrix}
    \right]
\end{aligned}
$$

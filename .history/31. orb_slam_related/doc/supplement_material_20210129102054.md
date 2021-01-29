<!--
 * @Author: Liu Weilong
 * @Date: 2021-01-29 09:58:50
 * @LastEditors: Liu Weilong 
 * @LastEditTime: 2021-01-29 10:20:54
 * @FilePath: /3rd-test-learning/31. orb_slam_related/doc/supplement_material.md
 * @Description: 
 * 
-->
### EPnP(四个控制点)
<font color = "Red"> 目的：从3D-2D 匹配关系里面得到Transform</font>
基础1：
$$
    p_i^w = \sum_{j=1}^{4}\alpha_{ij}c_j^{w}\\
    \sum_{j=1}^{4}\alpha_{ij} = 1
$$
存在四个控制点 可以通过$\alpha_{ji}$ 组合成任意的$p^w$<br>
基础2：
$$
    p_i^c = \left[
        \begin{matrix}
            R & t
        \end{matrix}
    \right]
    \left[
        \begin{matrix}
           p_i^w \\1
        \end{matrix}
    \right]
$$
从基础1我们可以得到一个关系
$$
    \begin{aligned}
    p_i^c &= \left[
        \begin{matrix}
            R & t
        \end{matrix}
    \right]
    \left[
        \begin{matrix}
           p_i^w \\1
        \end{matrix}
    \right]
    =\left[
        \begin{matrix}
            R  & t
        \end{matrix}
    \right]
        \left[
        \begin{matrix}
           \sum_{j=1}^{4}\alpha_{ij}c_j^{w} \\
           \sum_{j=1}^{4}\alpha_{ij}
        \end{matrix}
    \right]
    \\
    &=\sum_{j=1}^{4}\alpha_{ij}(Rc_j^{w}+t)
    \\
    &=\sum_{j=1}^{4}\alpha_{ij}c_j^{c}
    \end{aligned}
$$
可见$\alpha$关系从world 坐标系带到了camera坐标系

-----
正文开始：<br>
1. 找到控制点$c_j^{w}$
2. 找到$\alpha_{ij}$
3. 算出控制点$c_j^{c}$
4. 求解Transform
<!--
 * @Author: Liu Weilong
 * @Date: 2021-01-29 09:58:50
 * @LastEditors: Liu Weilong 
 * @LastEditTime: 2021-01-29 10:09:40
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
        \begin{aligned}
            R & t
        \end{aligned}
    \right]
    \left[
        \begin{aligned}
           p_i^w \\1
        \end{aligned}
    \right]
$$
从基础1我们可以得到一个关系
$$
    \begin{aligned}
    p_i^c = \left[
        \begin{aligned}
            R & t
        \end{aligned}
    \right]
    \left[
        \begin{aligned}
           p_i^w \\1
        \end{aligned}
    \right]
    =\left[
        \begin{aligned}
            R & t
        \end{aligned}
    \right]
        \left[
        \begin{aligned}
           \sum_{j=1}^{4}\alpha_{ij}c_j^{w} \\
           \sum_{j=1}^{4}\alpha_{ij}
        \end{aligned}
    \right]
    \end{aligned}
$$
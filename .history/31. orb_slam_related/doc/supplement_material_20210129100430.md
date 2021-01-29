<!--
 * @Author: Liu Weilong
 * @Date: 2021-01-29 09:58:50
 * @LastEditors: Liu Weilong 
 * @LastEditTime: 2021-01-29 10:04:27
 * @FilePath: /3rd-test-learning/31. orb_slam_related/doc/supplement_material.md
 * @Description: 
 * 
-->
### EPnP(四个控制点)
<font color = "Red"> 目的：从3D-2D 匹配关系里面得到Transform</font>
基础1：
$$
    p_i^w = \frac{1}{n}\sum_{j=1}^{4}\alpha_{ij}c_j^{w}\\
    \sum_{j=1}^{4}\alpha_{ij} = 1
$$
存在四个控制点 可以通过$\alpha_{ji}$ 组合成任意的$p^w$<br>
基础2：


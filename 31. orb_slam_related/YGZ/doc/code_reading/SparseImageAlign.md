<!--
 * @Author: Liu Weilong
 * @Date: 2021-02-02 17:22:53
 * @LastEditors: Liu Weilong 
 * @LastEditTime: 2021-02-02 17:36:33
 * @FilePath: /3rd-test-learning/31. orb_slam_related/YGZ/doc/code_reading/SparseImageAlign.md
 * @Description主要
-->
### 主要完成直接法的匹配
用于帧间匹配
1. precomputeReferencePatches
2. computeResiduals

------

Inverse Compositional LK 原理见 Supplement Material\
双线性插值：https://zh.wikipedia.org/wiki/%E5%8F%8C%E7%BA%BF%E6%80%A7%E6%8F%92%E5%80%BC\


------
1.a. precomputeReferencePatches 用于提前计算Jacobian\
a.1. 对每一个点进行\
       计算出优化变换的Jacobian求导(在template内部多次使用)\
       双线性插值出每一个template 的数值\
       
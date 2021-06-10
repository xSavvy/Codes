<!--
 * @Author: Liu Weilong
 * @Date: 2021-05-11 16:04:34
 * @LastEditors: Liu Weilong
 * @LastEditTime: 2021-06-10 21:24:18
 * @FilePath: /Codes/47. basalt/code_reading/Schur_unwarp_solve.md
 * @Description: 
-->
### 梗概
1. 概述一下Schur 的拆装求解的过程 (引自刘浩敏 BundleAdjustment 讲解)

   
----
1. BASALT 视觉特征rel 的写法就是
   $$
      res = obs_t - T_t^hp_h
      \\
      T_t^h = (T_w^t)^{-1}T_w^h
   $$

   然后第一段求导的时候
   $$
      J^{res}_{p_h} = \cfrac{\partial res}{\partial p_h}
      \\
      J^{res}_{T_t^h} = \cfrac{\partial res}{\partial T_t^h}
   $$
   
   然后进行第二段求导

   $$
      J^{res}_{T_w^h} = J^{res}_{T_t^h}J^{T_t^h}_{T_w^h}
      \\
      J^{res}_{T_w^t} = J^{res}_{T_t^h}J^{T_t^h}_{T_w^t}
   $$
   
   这样就满足了一个landmark 两个相机的观测模型

2. 这里我们参照 刘浩敏 BA 的讲解

   对Schur 的组成进行展开 j 代表点的序号，i 代表camera 的序号

   $$
      S_{i1i2} = \sum_j W_{i1j}V_j^{-1}W_{i2j}^T
      \\
      V_j = J^{res}_{p_h}
      \\
      W_{i1j} = J^{res}_{T_w^h} = J^{res}_{T_t^h}J^{T_t^h}_{T_w^h}
      \\
      W_{i2j} = J^{res}_{T_w^h} = J^{res}_{T_t^h}J^{T_t^h}_{T_w^h}
   $$

   res 是变化的，但是存在两个相机多个共视点的情况，所以
   $$
   J^{T_t^h}_{T_w^h},J^{T_t^h}_{T_w^t} 
   $$
   可以重复利用 不需要多次计算
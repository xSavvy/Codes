<!--
 * @Author: Liu Weilong
 * @Date: 2021-03-09 15:45:27
 * @LastEditors: Liu Weilong 
 * @LastEditTime: 2021-03-09 16:41:26
 * @FilePath: /3rd-test-learning/31. orb_slam_related/pl-slam/theory.md
 * @Description: 
-->
### 主要内容
1. line_project
2. line_optimization
3. match

======


1. line_project
   使用两点投影进行线的投影
2. line_optimization
   
   2.a. PoseOptimzation:思路就是对端点(start\end)进行几何误差上的构建
   $$
         e_s = 
         \pi(Tp_{s}) - 
         \left[
             \begin{matrix}
                 u_{sobs}\\
                 v_{sobs}
             \end{matrix}
             \right]
             \\
         e_e = 
         \pi(Tp_{e}) - 
         \left[
             \begin{matrix}
                 u_{eobs}\\
                 v_{eobs}
             \end{matrix}
             \right]
   $$

   2.b. LBA 对于线的处理和 PoseOptimzation 相同

3. match matchNNR 一个 KNN 最近邻查找
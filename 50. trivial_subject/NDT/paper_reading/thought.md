<!--
 * @Author: Liu Weilong
 * @Date: 2021-06-02 09:43:52
 * @LastEditors: Liu Weilong
 * @LastEditTime: 2021-06-05 21:33:56
 * @Description: 
-->

NDT 存在的问题:
a. cell size 难以选取的问题 -> 所以出现多层的NDT[5][6]
b. cell size 导致出现分布分割计算的问题 -> 所以出现内部先聚类的NDT [7][8]
c. cell 导致的不连续性  插值解决 [1][9]
d. 速度的问题采用 d2d_NDT[4]


NDT的最佳运行环境是什么？
1. 所有的信息都没有被栅格分割，或者说信息都在中心处
2. cell 大小合适 让信息没有出现混合情况
3. 匹配前后地图能够相似度高，也就是不会出现各种遮挡的或者动态物体的情况。
4. 提供了很好的匹配初值(保证在最优匹配附近、和局部最优的问题)
5. 优化连续性的问题

1 2 4 存在耦合的问题

从这几个方面出发的话:
1. NDT分割需要进一步改善



目前发现了一个问题，就是关于NDT 内部参数的问题 外点比例$\pi$ 和$c_1,c_2$ 不应该是固定值，
如果是固定值，就让所有Voxel的Residual处于了一个相同上下限的区间内，失去了对于方差差异性的对比
所以感觉对于定位来说，应该先使用EM 算法把每一个Voxel  的 c_1 c_2 \pi 计算出来，然后再进行NDT算法。
就会让一些比较好的线拥有更大的权重。

对于建图的任务，就可以使用 SVO 里面的变分推断，进行更新。
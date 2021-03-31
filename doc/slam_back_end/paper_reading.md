<!--
 * @Author: Liu Weilong
 * @Date: 2021-03-31 15:37:19
 * @LastEditors: Liu Weilong 
 * @LastEditTime: 2021-03-31 15:56:01
 * @FilePath: /3rd-test-learning/doc/slam_back_end/paper_reading.md
 * @Description: 
-->
1. Nonlinear Graph Sparsification for SLAM:
   相关阅读: 利用 sparse nature 11 15 17 
   当多次，边缘化之后信息矩阵变得dense，需要使用sparse enforce method 16 3 23 13 
   Margine 过程基于高斯假设，会引入误差，因为次优的线性化点

   SEIF 21 -> 8 -> 23 They also noted that the
    optimization need only be carried out on the Markov blanket of
    the node to marginalize
    马尔科夫毯

   16 用信息矩阵决定 margin 掉哪一个-> 

   摘要：
   a. 通过找一些set mean 和 covariance 来最小化KL散度，以此来对问题进行近似
   b. 好处: b.1. 最小化问题是凸的，也就是说有最有解 b.2. 框架对于所有nonlinear 函数通用 b.3. 保留矩阵的块结构
           b.4. 在一些情况下 存在解析解

   

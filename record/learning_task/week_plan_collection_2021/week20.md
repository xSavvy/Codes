<!--
 * @Author: Liu Weilong
 * @Date: 2021-05-09 22:00:08
 * @LastEditors: Liu Weilong
 * @LastEditTime: 2021-05-23 17:06:05
 * @Description: 
-->

### main task

序号|任务|状态|排序和备注
---|---|---|---
1.  |VINS 初始化部分 跟着课程一起重新读一下,写一下 -> 实现自己的前端||
2.  |实现自己的前端  -> DSO 代码阅读||
3.  |实现自己的前端 -> 用VINS + ORB做一个单线程测试平台 ||
4.  |实现自己的前端 -> BASALT 代码阅读 SO3预积分|基本完成|前端基本已经看完了、对比VINS的预积分也看完了、的确加强了理解 的确重力是在预积分之外进行的
5.  |实现自己的前端 -> BASALT 整体阅读||2
5.  |实现自己的前端 -> S-MSCKF(open-VINS) 整体阅读||
6.  |实现自己的前端 -> SVO-EDGLET 算法的模块链接||主要是为了打通 Depth Filter 和 reprojector 之间的关系
7.  |GF 系列分析 ||
8.  |实现自己的优化器-> 熟悉BA 分块构建和稀疏求解的过程||
9.  |实现自己的优化器->g2o ceres 核心代码阅读||
10. |实现自己的优化器->Liu Haomin 视频 ||
11. |实现自己的优化器->ICE-BA 代码阅读||数据流打通， 准备串数据流、太难读了，暂停一下
12. |实现自己的优化器->Schur 补拆分编写||需要观测模型
13. |实现自己的前端 -> Schimit EKF尝试||
14. |S-MSCKF 代码阅读-> 实现自己的前端||
15. |四元数 四阶隆格库塔||
16. |+ self_confusion ||写完之后SLAM结束
17. |cs231n||
18. |杂项-> VINS 预积分的问题 || 重新阅读了VINS的预积分，之前的问题解决了，之前自己编写的预积分方差出现问题的分析，已经得到了。但是还没有进行测试
19. |杂项-> VINS 四自由度和零空间的问题|完成| 基本想明白了，似乎还会有rotation averaging translation averagin 有关
20. |杂项-> D-LG-EKF 原理解析 -- 论文|完成|笔记基本整理完，又一次更新了自己对于EKF 的理解，下一步就是进行算法验证
21. |杂项-> D-LG-EKF 原理解析 -- A micro theory in lie group|暂停|暂时不需要
22. |杂项-> EKF 三种优化的验证|暂停| 大概知道有三种方法，有什么样的好处就可以了
23. |杂项-> PoseGraph 奇怪的优化测试|完成| 需要pose_graph 数据集 slambook/pose_graph<br> 结果基本一致，但是原因未知，优化方向的确是相同的
24. |杂项-> ESKF 正确性验证||1 之前不正确的原因，除了错误的更新之外，应该还存在一个 错误使用BCH的原因
25. |杂项-> BASALT OC 零空间限制||1
26. |杂项-> ORB Spinning tree 维护 笔记更新||
27. |杂项-> Partial Filter原理||
28. |杂项-> 四元数 代码测试||1 
29. |tzp-> DT 三角化||


2021.5.19<br>

晚上的时间，越来越少。

需要挤压时间去学习了。

周末计划：

2021.5.23<br>
需要思考一下，之后的方向的问题了，快速得进行学习才能一直拥有竞争力。
今年还是踏踏实实打好基础吧





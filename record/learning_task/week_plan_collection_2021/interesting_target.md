<!--
 * @Author: Liu Weilong
 * @Date: 2021-01-29 16:41:49
 * @LastEditors: Liu Weilong
 * @LastEditTime: 2021-06-21 08:35:58
 * @FilePath: /Codes/record/learning_task/week_plan_collection_2021/interesting_target.md
 * @Description: 
-->
### 有趣的内容
序号|内容|状态|备注
---|---|---|---
1. |WM下的 VPs|完成| 1和11 进行合并 垂直线特征改善的问题，最后可以变为VPs的全局旋转定位问题
2. |深度滤波|基本完成|原版本是使用变分推断(MAP)->无法理解<br>概率机器人的传感器模型EM算法拟合(MLE)->可以理解            
3. |Inverse Compositional光流+运动先验|完成|理清逻辑之后，基本理解了
4. |RANSAC各种几何校验 GRIC <br>L1 范数 outlier 去除||
5. |SOFT_SLAM 的 Blob 跟踪||
6. |VINS on wheel 带出的 observability 分析。<br>零空间操作 FEJ OC DSO|1/2完成|这部分的推导还是比较硬核的，但是感觉处理问题还是需要PWCS+SVD，因为这种分析，只是针对某集中特定的运动。<br>还没有整理可使用的类。
8. |旋转平均 平移平均 三维重建的概念||
9.  |BlockMatching||
10. |Good Featrue系列||
11. |Parallel Bundle Adjustment ||
12. |根据房间layout 进行室内定位||https://arxiv.org/pdf/1905.12571.pdf
13. |ESKF的问题||Super SLAM 激光和视觉融合真的很有趣啊
14. |深度学习||
15. |后端矩阵求解大测试!!||
16. |LSD 和 DSO 的传感器误差分析    ||
17. |概率、信息论、凸优化、线性代数(基础补全:大项目)||
18. |PC、NFR 等手法||
19. |BASALT 代码阅读|暂停|就剩下一个NFR <br>

20. 前端
   1.a. 深度学习的Feature (误匹配、匹配的好)
   1.b. 40帧/s
   1.c. 
20. 后端
   1.a. 
<!--
 * @Author: Liu Weilong
 * @Date: 2021-01-28 08:56:06
 * @LastEditors: Liu Weilong 
 * @LastEditTime: 2021-01-29 13:46:54
 * @FilePath: /3rd-test-learning/31. orb_slam_related/doc/doc_sketch.md
 * @Description: 
-->
### 代码框架整理内部
1. 只看理论和实现方式，而不是代码

### 框架
1. 特征提取                ORB_extract_and_match.md
2. Odometry Matching      ORB_tracking.md  + ORB_extract_and_match.md
3. 特征管理                ORB的特征管理分散在 Tracking 和 Mapping当中，有些混乱
4. Mapping Matching       ORB_mapping.md + ORB_extract_and_match.md
5. 地图维护                ORB2 并没有这个部分
6. 回环检测                ORB_DBoW.md + ORB_loopClosing.md(待完成)<br>
7. 工具类                  
8. Supplement Material (基础补全) supplement_material.md<br>

### remain theory problem
1. EPnP           完成
2. Optimizer
3. g2o边缘化实现
4. 双目的特征提取
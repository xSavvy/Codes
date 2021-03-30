<!--
 * @Author: Liu Weilong
 * @Date: 2021-03-29 08:58:06
 * @LastEditors: Liu Weilong 
 * @LastEditTime: 2021-03-30 09:28:43
 * @FilePath: /3rd-test-learning/record/work_task/week13.md
 * @Description: 
-->
### main task
序号|任务|状态|排序
---|---|---|---
1.  |Vanishing Point||
2.  |Vertical Line||2 地面情况下的进一步加速
3.  |VO设备搭建||
4.  |pl-svo代码阅读、pl-slam代码阅读||1主要问题是方差和去outlier
5.  |3.29 加班申请编写|

### 简记
1. 从evo -r rot_part 找到旋转误差是的导致整体误差最大的问题
2. 发现旋转的问题是转角场景下，特征少，并且特征有高度的相似性导致的，就算是先特征也没有办法让这种事情不发生。
3. ORB跑的时候，加大关键帧的插入速度很大程度上加剧了旋转，因为特征少，特征重复，所导致的旋转漂移。比如旋转场景下。
4. FLD边长检测过大，导致出现一些内容检查不到
5. TrackLocalMap 会对于一些情况有更好的适应性，主要还是这个原因
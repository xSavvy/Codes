<!--
 * @Author: Liu Weilong
 * @Date: 2021-01-29 14:01:39
 * @LastEditors: Liu Weilong 
 * @LastEditTime: 2021-01-29 15:22:30
 * @FilePath: /3rd-test-learning/31. orb_slam_related/doc/ORB_loppclosing.md
 * @Description: 
-->
### ORB LoopClosing
内部来自 LoopClosing.h 和 LoopClosing.cc

1. DetectLoop
2. ComputeSim3
3. CorrectLoop
   
-----
Sim3 群的优化见 Supplement Material
Sim3 的几何校验见 Supplement Material

-----

1.a. DetectLoop\
a.1. 从CurrentFrame的共视帧得到最小得分
a.2. 最小得分作为阈值,进行LoopClosure帧的搜索，具体操作基本和 Tracking Relocalization 相同-> ORB_tracking.md:2.a.1
a.3. 连续性检测 代码实现的有点懵
     for_each CandidateKF
        通过共视关系，形成一个新的ConsistencyGroup(这个之后叫new Group)
        for_each mConsistencyGroup(这个之后叫old Group)
            new Group 和 Old Group 进行count，查看是否含有相同KF
            if(有)
                new Group 加入vConsistencyGroup_new
                并且连续计数+1
            if(连续计数>th)
                当前KF加入 mvpEnoughConsistentCandidates
        
        if(和old Groups没有任何关系)
            new Group 加入vConsistencyGroup_new
            连续计数置1

2.a. ComputeSim3 进行几何校验 和 scale 恢复\
a.1. SearchSearchByBoW<br>
     对每一个CanidiateKF
     与 Current KF Sim3Solver 几何校验，找Inliner<br>
     OptimizeSim3 进行优化，Inliner 足够跳出<br>
a.2. 对于最佳匹配 Candidate KF 的共视帧
     整和所有的地图点
     对关键帧再做一次 SearchByProjection

            

   
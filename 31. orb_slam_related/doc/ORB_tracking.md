<!--
 * @Author: Liu Weilong
 * @Date: 2021-01-28 11:14:38
 * @LastEditors: Liu Weilong 
 * @LastEditTime: 2021-01-29 15:15:34
 * @FilePath: /3rd-test-learning/31. orb_slam_related/doc/ORB_tracking.md
 * @Description: 
-->

### ORB_tracker 
内容来自 Tracking.cc Tracking.h 
1. TrackWithMotionModel
2. TrackReferenceKeyFrame
3. TrackLocalMap
4. Relocalization
5. NeedNewKeyFrame

-----
EPnP 为了几何校验 得到Inliner 具体见Supplement Material


-----

1.a. TrackWithMotionModel<br> 
a.1. UpdateLastFrame 准备位姿、准备临时的MapPoint,<br>
     也就是把LastFrame内部之前有深度但是不是MapPoint的点三角化之后，创建成MapPoint，但是并不加入Map<br>
a.2. SearchByProjection <br>
a.3. PoseOptimization<br> 
a.4. 丢掉outlier<br>

1.b. TrackWithLocalMap<br>
b.1. UpdateLocalMap 汇集所有的observation related 的Keyframe 和这次Keyframe的临近Keyframe 到LocalMap 里面<br>
                    汇集所有的LocalMap中Keyframe 中的MapPoints<br>
b.2. SearchLocalPoints 使用inFrustum 进行点筛选、根据距离更新PredictedLevel、使用SearchByProjection进行匹配<br>
b.3. PoseOptimization<br> 

1.c. TrackReferenceKeyFrame<br>
c.1. SearchByBoW<br>
c.2. PoseOptimization<br>
c.3. 丢掉outlier<br>

2.a. Relocalization<br>
a.1. DetectLoopCandidates\
     寻找Candidates<br>
     计算当前帧词袋向量<br>
     寻找分享词袋的所有关键帧<br>
     计算关键帧和当前帧的分数<br>
     计算每个关键帧前10个最佳共视帧的累加分数 -> AccBestCore<br>
     返回 得分 > 0.75*AccBestCore的关键帧<br>
a.2. 对每一个关键<br>
     SearchSearchByBoW<br>
     pnpsolver 初次计算，找Inliner<br>
     PoseOptimization 进行优化<br>
     nGood 不足，SearchByProjection 再次匹配，PoseOptimization 再次优化<br>
     nGood 足够，直接跳出循环并返回<br>

5.a. NeedNewKeyFrame
a.1. 距离上一次插入关键帧是否已经经过了足够多的帧   c1a
a.2. 是否LocalMapping 已经空闲                 c2a
a.3. track weak 也和CurrentFrame的特征深度(thDepth 在这里使用)分布有关 c3a
a.4. 未完待续
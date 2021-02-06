<!--
 * @Author: Liu Weilong
 * @Date: 2021-02-04 09:45:10
 * @LastEditors: Liu Weilong 
 * @LastEditTime: 2021-02-04 14:24:57
 * @FilePath: /3rd-test-learning/31. orb_slam_related/YGZ/doc/code_reading/feature_manager.md
 * @Description: 
-->
### Cache机制
1. 添加机制
a.1. 在Cache 内部进行搜索，找不到足够多的点的时候,进行原版本ORB 的SearchLocalMap
     然后把追踪到的点放入Cache当中。
a.2. 在生成KeyFrame的时候，把所有新生成的MapPoint 加入到Cache
2. 删除机制
a.1. 在TrackLocalMapDirect 里面， 如果发现跟踪不上了，就进行删除.但是这个一定程度上会影响到LocalMapping 内部 依靠 Found 和 Visible 进行判断的函数

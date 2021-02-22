<!--
 * @Author: Liu Weilong
 * @Date: 2021-02-04 09:45:10
 * @LastEditors: Liu Weilong 
 * @LastEditTime: 2021-02-22 14:19:34
 * @FilePath: /3rd-test-learning/31. orb_slam_related/YGZ/doc/code_reading/feature_manager.md
 * @Description: 
-->
### Cache机制
1. 添加机制
a.1. 在Cache 内部进行搜索，找不到足够多的点的时候,进行原版本ORB 的SearchLocalMap<br>
     然后把追踪到的点放入Cache当中。<br>
a.2. 在生成KeyFrame的时候，把所有新生成的MapPoint 加入到Cache<br>
2. 删除机制
a.1. 在TrackLocalMapDirect 里面， 如果发现跟踪不上了，就进行删除.但是这个一定程度上会影响到LocalMapping 内部 依靠 Found 和 Visible 进行判断的函数
2021.2.22 补充<br>
最后发现YGZ只是添加了 Found,Visible添加并没有管如何使用，但是最终Mapping结果并没有收到影响，所以猜测，是因为MapPointCulling 里面的冗余设计起了效果。

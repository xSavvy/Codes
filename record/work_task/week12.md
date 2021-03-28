<!--
 * @Author: Liu Weilong
 * @Date: 2021-03-23 09:51:02
 * @LastEditors: Liu Weilong
 * @LastEditTime: 2021-03-23 21:21:23
 * @FilePath: /Plan/work_task/week12.md
 * @Description: 
-->
### main task

序号|任务|状态|排序
---|---|---|---
1.  |Vanishing Point|完成了一半的内容|1
2.  |PL-SLAM 搬运|完成了一大半|2
3.  |VO测试环境||

序号|自任务名|状态|备注
----|----|----|--
1.  |Vanishing-Pipeline搭建||
2.  |PL-SLAM 搬运-线特征check|完成|之前的问题是线特征之间存在误匹配，所以导致的问题
3.  |PL-SLAM 搬运-内部匹配调整|完成|Stereo Matching、左右匹配参数(Disparity 最大最小的检查、方向差值)、新旧匹配的参数(位置深度>0、端点pixel夹角检查)、固定方差
4.  |PL-SLAM 搬运-线特征跟踪测试|完成|a. OldNew 存在旋转匹配 b. 旋转过快的时候有些线没有匹配上。c. 存在同一根线多次检测的问题 b. 少线的问题<br> 最后的原因是有一个变换取反了的情况。过滤的方法只有两个: a. 判断深度是否大于0 b. 还有就是投影到pixel 面上的时候，对观测进行夹角判断。c. 双目 
5.  |PL-SLAM 搬运-线外点排除的问题||
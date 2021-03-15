<!--
 * @Author: Liu Weilong
 * @Date: 2021-03-13 18:52:51
 * @LastEditors: Liu Weilong 
 * @LastEditTime: 2021-03-15 11:56:58
 * @Description: 
-->
### main task

序号|任务|状态|排序
---|---|---|---
1.  |Vanishing Point|完成了一半的内容|1
2.  |PL-SLAM 搬运||2
3.  |客户端测试||3


序号|自任务名|状态|备注
----|----|----|--
1. |Vertical-多帧匹配测试|半完成|如何确定描述子匹配的阈值还没有确认
2. |Vertical-KLT光流+SAD/NCC匹配测试|半完成|a. ZNCC 的检测 StructVIO使用过<br>b. KLT光流追踪的感觉还可以 SAD+NCC测试还没有做
3. |Vertical-Plucker 优化参数测试|完成|PL-VIO的那一版的确是可以收敛的
4. |Vertical-Plucker-self 优化检查||learning targets的一个目标，不知道为什么我个人的优化没有办法收敛
5. |Vertical-L1参数匹配||
6. |Vertical-PLSLAM理论学习| 完成|
7. |Vertical-PLSLAM优化修改|完成|之前的版本理解存在问题，需要进行修改。<br>在优化测试的过程中发现，使用几何误差对于两个端点进行PLSLAM线误差项优化，会出现端点滑动的情况，也就是端点还是在线上，但是已经不是原来的点了。虽然运算速度依旧是Plucker 参数化的两倍以上，但是不知道是福是祸。
8. |Vertical-FLD 提取速度计算|完成|1/4 lsd 的速度
9. |综合-论文阅读||struct SLAM structVIO
10. |Veritcal-LSD、FLD的调参加速||
11. |Vertical-FLD和LBD的适配|半完成| 从PLSLAM 找到了类似的适配
12. |Vertical-测试EDLines|完成 |和fld 一个速度，但是质量不如fld|
13. |Edgelet-运行测试||
14. |Vanishing-Pipeline搭建||
<!--
 * @Author: Liu Weilong
 * @Date: 2021-01-18 09:06:14
 * @LastEditors: Liu Weilong 
 * @LastEditTime: 2021-01-18 09:07:06
 * @FilePath: /3rd-test-learning/work_record/work_task/week4.md
 * @Description: 
-->

主要任务如下：
1. 修改出有回环的ORB         11    
2. ORB工程重构            属于有待商榷的项目
   |__ TrackLocalMap 改造
       |__ 引入PoseTree 让匹配加速 (近处小回环？)
       |__ 速度模型改成加速度模型
   |__ 后端LBA优化逻辑
3. 准备光流紧融合            12
   |__ S-MSCKF 代码阅读
   |__ BASALT  代码阅读
   |__ YGZ-ORB 代码阅读
   |__ VINS on Wheel 可观性分析
4. 准备加入线特征            12
   |__ Struct VIO 内容学习
       |__ 曼哈顿、亚特兰大
       |__ 线、面特征参数化
       |__ PL-VIO 代码阅读
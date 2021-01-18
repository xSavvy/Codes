<!--
 * @Author: Liu Weilong
 * @Date: 2021-01-12 09:35:20
 * @LastEditors: Liu Weilong 
 * @LastEditTime: 2021-01-16 09:43:59
 * @FilePath: /3rd-test-learning/work_record/work_task/week3.md
 * @Description: 
-->



主要任务如下：
1. ORBSLAM 添加地面约束   11
   |__ DataCollector编写     完成  用于得到Tcw内容
   |__ 添加到原版本当中        完成
   |__ 多种地面约束尝试(论文)   完成   
   |__ 融合外参进行地面约束     完成
2. 交付一个视觉版本        12  完成   
3. 使用git 和 设置.gitignore  来方式反复编译 完成         
4. ORB工程重构            属于有待商榷的项目
   |__ TrackLocalMap 改造
       |__ 引入PoseTree 让匹配加速 (近处小回环？)
       |__ 速度模型改成加速度模型
   |__ 后端LBA优化逻辑
5. 准备光流紧融合            12
   |__ S-MSCKF 代码阅读
   |__ BASALT  代码阅读
   |__ YGZ-ORB 代码阅读
   |__ VINS on Wheel 可观性分析
6. 准备加入线特征            12
   |__ Struct VIO 内容学习
       |__ 曼哈顿、亚特兰大
       |__ 线、面特征参数化
       |__ PL-VIO 代码阅读

2021.1.14<br>
矫正之后的数据，fx也需要使用矫正之后的fx‘
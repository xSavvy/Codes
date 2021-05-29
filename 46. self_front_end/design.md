<!--
 * @Author: Liu Weilong
 * @Date: 2021-05-07 14:27:26
 * @LastEditors: Liu Weilong
 * @LastEditTime: 2021-05-29 11:30:56
 * @FilePath: /Codes/46. self_front_end/design.md
 * @Description: 
-->
### BASALT 原理部分的填充
1. nullspace 检测
2. NFR
3. 后端组成逻辑



### 目标--深度修改basalt
1. 单线程化
2. 更换初始化
3. 添加SVO 的localMap 跟踪扩大前端匹配
4. 添加特征描述子 module 方便用于重定位
5. 前端进一步对畸变模型进行描述
6. 后端进行SVO概率分布管理
7. 添加 光度标定 options
8. 后端更换成ICE-BA
9. 重定位添加
10. imu 辅助的动态环境克服
11. 添加特征描述子的定位环节
12. 添加多种feature的module

### 目标--better BASALT
1. 添加语义信息
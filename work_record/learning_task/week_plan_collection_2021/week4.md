<!--
 * @Author: Liu Weilong
 * @Date: 2021-01-18 09:03:45
 * @LastEditors: Liu Weilong
 * @LastEditTime: 2021-01-20 07:34:49
 * @FilePath: /3rd-test-learning/work_record/learning_task/week_plan_collection_2021/week4.md
 * @Description: 
-->


### week4
a. 不看porn<br>
b. 记录时间使用<br>

11:
   a. front_end_self(Camera) 的建立 可以持续两个周
        |__ Displayer                完成
            |__ coding
            |__ testing
        |__ DataLoader               完成
            |__ coding
            |__ testing
        |__ 相机模型搭建               完成
        |__ 编写对极几何\Pnp等基础
            |__ 搭建仿真环境           完成
            |__ 搭建Pangolin显示环境   完成
            |__ 对极约束               
            |__ PnP ICP                    需要参考  an invitation to 3d
        |__ 光流基础pipeline+光流opencv pipeline   合并为编写 inverse compositional KLT 合并到VINS内部 
                                                 学习VINS 的框架 做IMU 四阶龙格库塔的预测  混合到 IMU 检测    
        |__ 到TrackLocalMap为止       
    b. YGZ-ORB TrackLocalMapDirect 学习  
        |__ 需要光流的前置知识             完成 虽然是比较肤浅的 数学上还是有些难度的
12:
    a. ESKF编码+测试
    b. VINS Covar获取\特征和帧见管理 学习 
        |__ Covar获取 + 边缘化     完成
        |__ 特征管理
        |__ 帧管理      
    c. EKF 概率、插值 on SO3 包括双目的概率例子
    d. 多传感器作业
    e. SVO.py 进行python + opencv 学习
    f. BASALT 代码论文阅读
    g. 深度估计方面的请教 + SVO 深度滤波
    h. 学习python


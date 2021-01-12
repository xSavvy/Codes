

### Week3  Control Week
主要思想: <br>
a. 这个周,想办法去做正确的事<br>
b. 统计这个过程中,没有完成的原因,心理的变化. 只记录大段的时间<br>

计划:<br>
11:
   a. front_end_self(Camera) 的建立 可以持续两个周
        |__ Displayer                完成
            |__ coding
            |__ testing
        |__ DataLoader               完成
            |__ coding
            |__ testing
        |__ 相机模型搭建               完成
        |__ 光流opencv pipeline
        |__ 编写对极几何\Pnp等基础
        |__ 光流基础pipeline                
        |__ 到TrackLocalMap为止
    b. YGZ-ORB TrackLocalMap 学习 
        |__ 需要光流的前置知识    
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

三个主要目标
a. 早睡早起
b. 不看B站
c. 锻炼身体

2021.1.11<br>
观测：<br>
部分bug的产生是因为有多个地方的代码需要进行修改，<br>
但是修改的时候，忘记修改了一部分的地方导致的<br>
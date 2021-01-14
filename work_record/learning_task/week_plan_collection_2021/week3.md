<!--
 * @Author: Liu Weilong
 * @Date: 2021-01-10 21:25:03
<<<<<<< HEAD
 * @LastEditors: Liu Weilong
 * @LastEditTime: 2021-01-14 20:47:43
=======
 * @LastEditors: Liu Weilong 
 * @LastEditTime: 2021-01-13 18:17:44
>>>>>>> 656f7c07f4b58501a649972f51c279e4636f93d6
 * @Description: 
-->


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
            |__ 搭建仿真环境
            |__ 搭建Pangolin显示环境
            |__ 对极约束
            |__ PnP ICP
        |__ 光流基础pipeline                
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

三个主要目标
a. 早睡早起
b. 不看B站
c. 锻炼身体

2021.1.11<br>
观测：<br>
部分bug的产生是因为有多个地方的代码需要进行修改，<br>
但是修改的时候，忘记修改了一部分的地方导致的<br>
a. 在不如意的时候喜欢乱调参
b. 刚刚下定决心,就迎来了情绪上的低谷,以前的为都是在这里放弃的,这次坚决不要
书魔的飞轮:
a. 要不断的大量阅读,在脑内进行验证
b. 建立知识之间的联系
c. 捷偶学习和工作
d. 不要自满,自己一段时间内能学会的,别人也可以

2021.1.12<br>
其他:<br>
其实黑盒对于工程师的拿来思想来讲, 是不是深度学习真的不会有太多的影响<br>
就像是深度学习和Inverse Composition 都是看不懂的东西<br>
还是需要加强自己的数学基础啊<br>

2021.1.13<br>
是时候考虑一下,跳槽的项目了<br>
目前是更倾向于 点线VIO 

2021.1.13<br>
今天着实是认识到了数学的重要性，需要好好补一下了

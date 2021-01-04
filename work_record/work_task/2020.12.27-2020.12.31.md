<!--
 * @Author: Liu Weilong
 * @Date: 2020-12-29 09:19:24
 * @LastEditors: Liu Weilong 
 * @LastEditTime: 2021-01-04 11:30:01
 * @FilePath: /3rd-test-learning/work_record/work_task/2020.12.27-2020.12.31.md
 * @Description: 
-->

主要任务如下：
1. ORBSLAM 添加地面约束
         
2020.12.27-30
主要任务是参考 optimization.cc 添加地面约束
    |__ g2o basic CurveFitting   完成
    |__ g2o GBA                  完成 跟着slambook2 看完了一遍 感觉和Basic 没有太多区别
                                      不过SO3 可以自动求导是真的没有想到  
                                      而且可以自己进行边缘化 真的很方便啊 
                                      但是存在优化过程相对已经固定 BlockSolverTrait 无法添加多种不同的CostFunction
                                      如果是这样的话那么g2o 可能就没有ceres 那么好用了
                                      只是ceres需要写一个边缘化的库
    |__ ORB3 g2o 用例             完成 
                                      因为遇到了无法添加多个Cosfunction 的问题 这里将一版固定的BlockSolverTrait 换成了 BlockSolverX
                                      就可以进行优化了  但还是感觉 Ceres 好用啊
    |__ powell function 编写      完成  使用 BaseUnaryEdge
                                       使用 BaseMultiEdge 的方法还在摸索                                 
    |__ optimzation.cc           完成 
    |__ GroundStateConstraint编写 完成
                                      目前的问题是如何添加 最快的方法就是直接做做一个类似 PoseGraph的依赖
                                      之后全部修改成了SO3＋R3的表示方式，但是无法通过，需要进行debug
                                      之前发现有三处编码的时候的bug 
                                      最后发现是因为Mono约束在Stereo PoseOptimization 中也会使用才会导致出现问题
    |__ PoseOptimzation 改写  EdgeStereo改写 完成
                             EdgeMono 改写  完成
                                      后来发现如果只是使用TrackLocalMap而不去解决LBA的话，
                                      就只是更新了机器人位姿，而没有更新地图点的位姿，这是非常不行的，整体跑起来轨迹会整个偏掉。
                                      所以需要在是LBA中添加，LBA需要从SE3换成SO3+R3
    |__ LBA SE3 到SO3+R3          完成
感悟：
1. 如果已经有别人实现过的算法，并且原理自己也比较清晰了何必还要自己再写一遍呢？
   只要在这个基础上，知道什么样的场景会更加合适使用就可以了。
   a. 计算平台 b. 实际应用环境

12.31
1. 再次测试 origin origin+info150 的translation 和 rotation
2. 测试 添加地面约束之后的效果 应该考虑到hard-constraint 和 soft-constraint 的问题

总结：
1. 之前在版本编译上花费了大量的时间，似乎每一次换一个表示方式就要对代码重新进行编译，
   这是非常可不取的
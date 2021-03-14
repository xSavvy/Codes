<!--
 * @Author: Liu Weilong
 * @Date: 2021-03-06 21:07:34
 * @LastEditors: Liu Weilong
 * @LastEditTime: 2021-03-14 12:34:36
 * @Description: 
-->
### 2.1 Bundle Adjustment
1. 为何说 Bundle Adjustment is slow 是不对的？
   
   因为没有利用稀疏
2. BA 中有哪些需要注意参数化的地⽅？ Pose 和 Point 各有哪些参数化⽅式？有何优缺点
  
    Pose 有四元数+平移 旋转矩阵+平移 SO3+平移 SE3<br>
  Point 齐次方程 <br>
  SE3 的稳定性更高 <br>
  旋转矩阵的优化更加复杂，而且带有其他约束<br>
  
3. 本⽂写于 2000 年，但是⽂中提到的很多内容在后⾯⼗⼏年的研究中得到了印证。你能看到哪些⽅向在后续⼯作中有所体现？请举例说明




### 2.2 BAL
![](./pic/1.png)
红色是优化后 绿色是优化前


### 3.1 Direct BA
1. 如何描述任意⼀点投影在任意⼀图像中形成的 error？
   $$
    \underset{W}{\sum}(I(p_i)-I(\pi(KTp)))
   $$
2. 每个 error 关联⼏个优化变量?
   
   优化 Pose(6维) Point(3维) 两个变量
3. error 关于各变量的雅可⽐是什么？
   $$
    \cfrac{\partial I}{\partial \xi} = \left[
        \begin{matrix}
            I_x\\
            I_y
        \end{matrix}
        \right]
        \left[
        \begin{matrix}
            f_x/z&0&\cfrac{-f_xx}{z^2}\\
            0&f_y/z&\cfrac{-f_yy}{z^2}
        \end{matrix}
        \right]
        \left[
        \begin{matrix}
            I\in R^{3×3}&[p×]
        \end{matrix}
        \right]
   $$
   $$
    \cfrac{\partial I}{\partial p} = \left[
        \begin{matrix}
            I_x\\
            I_y
        \end{matrix}
        \right]
        \left[
        \begin{matrix}
            f_x/z&0&\cfrac{-f_xx}{z^2}\\
            0&f_y/z&\cfrac{-f_yy}{z^2}
        \end{matrix}
        \right]
        R
   $$
### 3.2 实现
1. 能否不要以 [𝑥,𝑦,𝑧]𝑇 的形式参数化每个点？
   
   可以，可以用逆深度模型进行参数化
2. 取 4x4 的 patch 好吗？取更大的 patch 好还是取小⼀点的 patch 好？
   













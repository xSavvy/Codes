<!--
 * @Author: Liu Weilong
 * @Date: 2021-01-04 09:16:13
 * @LastEditors: Liu Weilong 
 * @LastEditTime: 2021-02-04 16:47:59
 * @FilePath: /3rd-test-learning/31. orb_slam_related/YGZ/doc/Theory.md
 * @Description: 
-->

### ===== 2021.1.12 添加 =====
经过学习光流之后，发现这里实际上是 Inverse Compositional 的直接法<br>
所以才会有各种各样提前算好的Jacobian<br>
具体公式如下：<br>
$$
    \underset{p}{argmin}\sum[I(W(x;p))-T(W(x;\Delta{p}))]^{2}
    \\
    W(x;p) =\exp(p)x
$$
进行更更新的时候
$$
    \begin{aligned}

    W(x;p)&\leftarrow{W(x;p)\circ{W(x;\Delta{p})^{-1}}}  
    \\
    & = W(W(x;\Delta{p})^{-1};p)  
    \\   
    &=\exp(p)\exp(-\Delta{p})x
    \\
    &=\exp(p_{new})x
    
    \end{aligned}
$$

$\cfrac{\partial{T}}{\partial{W}}$ 具体实现还是需要参考YGZ-ORB

Warp 要求是半群<br>
这个Compositional真的是神奇，也不知道是哪里的概念\



### <font color = "Red">SparseImageAlign 原理二次挖掘</font>
这个是用在帧间匹配，LastFrame 和 CurFrame。\
LastFrame 带有MapPoint CurFrame 只有一张图\

$$
    \underset{p}{argmin}\sum[I(W(x;p))-T(W(x;\Delta{p}))]^{2}
    \\
    W(x;p) =\pi{(\exp(p)x)}
$$
1. 计算 Template 的雅克比，猜测这里没有使用Affine的原因是帧件匹配变化较小，所以没有必要
$$
    T(x) = \left[
        \begin{matrix}
        u_{ref}+offset_x\\
        v_{ref}+offset_y
        \end{matrix}
        \right]\\
    offset_x,offset_y \in[-GridSize,+GridSize]
$$
$$
    \cfrac{\partial{T}}{\partial{\Delta{p}}}=\cfrac{\partial{T}}{\partial{W}}\cfrac{\partial{W}}{\partial{\Delta{p}}} = R^{1×2}R^{2×6}
$$
2. 计算 Residual,这里应该是同样的小运动假设\
   把Ref 的MapPoint 投影到Cur图像上\
   所以直接3×3 顺序对应算Residual\
3. solve 和一般优化方法一致  H Jres
4. 更新
   $$
    \begin{aligned}
    W(x;p)&\leftarrow{W(x;p)\circ{W(x;\Delta{p})^{-1}}}  
    \\
    & = W(W(x;\Delta{p})^{-1};p)  
    \\   
    &=\exp(p)\exp(-\Delta{p})x
    \\
    &=\exp(p_{new})x
    \end{aligned}
$$

### <font color="Red">Align2D 原理挖掘</font>
和SparseImageAlign的区别
1. 远距离的帧间需要Affine
2. 为了克服自动曝光，添加另外一个参数m来减少图像亮度平均差值
3. 没有使用直接法 存疑

$$
\begin{aligned}
    &I_cur(W(x;p))-I_ref(W(x;p))+m
    \\
    &W(x;p)=
    \left[
    \begin{matrix}
        u+p_x\\
        v+p_y
    \end{matrix}
    \right]
\end{aligned}
$$

tips: 关于代码中的Jacobian的问题 SparseImageAlign 负号组合进了 J
Align2D 的 J_I 负号没有组合进去 所以最后更新Warp 的时候是直接加而不是减
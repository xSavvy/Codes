<!--
 * @Author: Liu Weilong
 * @Date: 2021-01-04 09:16:13
 * @LastEditors: Liu Weilong 
 * @LastEditTime: 2021-02-23 18:06:57
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

<font color = "Red">2021.2.23 更新</font><br>
在阅读论文 光流20年的时候大概知道了，
真正的公式推导应该是
$$
    \underset{T}{\sum} I(W(W(x;\Delta{p});p))-T(x)
\\
\downarrow y=W(x;\Delta p)
\\
\underset{W(T;\Delta p)}{\sum} I(W(y;p)) - T(W^{-1}(y;\Delta p))
\\
\downarrow \Delta p \rightarrow 0, W(x;\Delta p) = x
\\
\underset{T}{\sum} I(W(y;p)) - T(W^{-1}(y;\Delta p)) 
$$
至于为什么差了一个符号，还可以在直接法当中使用？
因为存在
$$
    W^{-1}(x;\Delta p) = W(x;-\Delta p)
$$
这个值$\Delta p$可以在更新的时候换一个正负号就可以补上。<br>
所以可以写成如下的形式

$$
    \underset{p}{argmin}\sum[I(W(x;p))-T(W(x;\Delta{p}))]^{2}
    \\
    W(x;p) =\pi{(\exp(p)x)}
$$


### <font color="Red">Align2D 原理挖掘</font>
和SparseImageAlign的区别
1. 远距离的帧间需要Affine
2. 为了克服自动曝光，添加另外一个参数m来减少图像亮度平均差值
3. 没有使用直接法 存疑

$$
\begin{aligned}
    &I_{cur}(W(x;p))-I_{ref}(W(x;p))+m
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
做的时候似乎都是在和金字塔有关。具体实现有些忘记了<br>


大概知道维和感是从哪里来的了<br>
SparseImageAlign 是围绕灰度的图像误差项
Align2D 最后的优化是围绕着2d-3d的几何误差项
Align2D 图像匹配过程还是为了找到匹配的2d像素位置 而不是 对应的灰度
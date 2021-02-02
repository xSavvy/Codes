<!--
 * @Author: Liu Weilong
 * @Date: 2021-01-04 09:16:13
 * @LastEditors: Liu Weilong 
 * @LastEditTime: 2021-02-02 17:21:42
 * @FilePath: /3rd-test-learning/31. orb_slam_related/YGZ/doc/Theory.md
 * @Description: 
-->

## 目标
1. 研究实际中的直接法是如何实现的     完成
2. 学习TrackLocalMap的直接法实现
3. 学习Cache的实现

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
这个Compositional真的是神奇，也不知道是哪里的概念

<font Color="Green">================</font>

### 2021.2.2 添加 Why Inverse Compositional LK work？
具体见Supplement Material 的简单例子，具体证明，并看不懂


### SparseImageAligned 实现
1. Pre


### TrackLocalMapDirect 逻辑和实现
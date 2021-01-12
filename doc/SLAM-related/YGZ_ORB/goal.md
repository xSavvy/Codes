<!--
 * @Author: Liu Weilong
 * @Date: 2021-01-04 09:16:13
 * @LastEditors: Liu Weilong 
 * @LastEditTime: 2021-01-12 16:43:03
 * @FilePath: /3rd-test-learning/doc/SLAM-related/YGZ_ORB/goal.md
 * @Description: 
-->

## 目标
1. 研究实际中的直接法是如何实现的     完成
2. 学习TrackLocalMap的直接法实现
3. 学习Cache的实现


### 直接法的实现
和slambook中的直接法投影方向<br>
slambook里面，<br>$I_1 = I_{pre}$
$I_2 = I_{cur}$ <br>
这里的逻辑 是固定 $I_{pre}$ ，在 $I_{cur}$上搜索相似的灰度
$$
    \begin{aligned}
    &\underset{T}{\operatorname{argmin}} (I_1(u_1,v_1)-I_2(\cfrac{DKT^2_1p_1}{z_2}))\\
    = &\underset{\delta{T}}{\operatorname{argmin}}(I_1(u_1,v_1)\\&-I_2(\cfrac{DKT^2_1p_1}{z_2}))-\cfrac{\partial{I_2}}{\partial{u,v}}\cfrac{\partial{u,v}}{\partial{x_2,y_2,z_2}}\cfrac{\partial{x_2,y_2,z_2}}{\partial{\xi}}\delta{\xi})\\
    \end{aligned}
$$

YGZ 里面, 反了过来,一个比较奇怪的顺序。
固定$I_{cur}$ 反向寻找$I_{pre}$ <br>
并且中间会做双边滤波，来做到亚像素级<br>
$$
    \begin{aligned}
    &\underset{T}{\operatorname{argmin}} (I_{cur}(\cfrac{DKp_{cur}}{z_{cur}})-I_{pre}(\cfrac{DKT^{cur}_{pre}p_{cur}}{z_{cur}}))\\
    \end{aligned}
$$
这样反向，应该是之后给TrackLocalMapDirect也提供了方便<br>
实现方法和之前基本一直，都是多层金字塔。<br>
唯一的不同是添加了双边滤波进行亚像素级的匹配.<br>

<font Color="Green">===== 2021.1.12 添加 =====</font><br>
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

<font Color="Green">================</font><br>

### TrackLocalMapDirect 逻辑和实现

## 目标
1. 研究实际中的直接法是如何实现的
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

### TrackLocalMapDirect 逻辑和实现
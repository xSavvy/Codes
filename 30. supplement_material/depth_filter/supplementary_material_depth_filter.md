<!--
 * @Author: Liu Weilong
 * @Date: 2021-02-25 13:30:00
 * @LastEditors: Liu Weilong 
 * @LastEditTime: 2021-02-25 14:22:29
 * @FilePath: /3rd-test-learning/30. supplement_material/depth_filter/supplementary_material_depth_filter.md
 * @Description: 
-->
### 问题理解
输入：多次对于同一个KeyPoint 的深度观测<br>
输出：哪些观测是好的观测？真实深度是多少？好观测的概率$\pi$？()<br>

最后建模出来的内容就是：
$$
    \underset{Y,\hat{d},\pi}{argmax}[p(Y,\hat{d},\pi|X) ]
    \\
    Y = [y_1,y_2,y_3...]
    \\
    X = [x_1,x_2,x_3...]
    \\
    p(\hat{d},\pi) = p(\hat{d})p(\pi)
    \\
    p(\hat{d}) \sim N,p(\pi) \sim N
$$

Y 代表观测是不是好，X代表观测到的深度<br>
真实深度和inliner概率相互独立
### 问题的求解过程
1. Bayesian 构造过程
$$
\begin{aligned}

    p(Y,\hat{d},\pi|X) &\propto p(X|\hat{d},Y,\pi)p(Y|\pi)p(\hat{d})p(\pi)
    \\
    & = \prod [p(x_i|\hat{d},y_i,\pi)p(y_i|\pi)]p(\hat{d})p(\pi)
\end{aligned}
$$
2. 各部分概率分布的构造<br>

2.a. $p(y_i|\pi)$<br>
$$
    \begin{aligned}
        p(y_i|\pi) = \pi^{y_i}(1-\pi)^{1-y_i}
    \end{aligned}
$$
是一个Bernouli的分布<br>

2.b. $p(x_i|\hat{d},y_i,\pi)p(y_i|\pi)$<br>
$$
    p(x_i|\hat{d},y_i,\pi)p(y_i|\pi) = N(x_i|\hat{d},\sigma^2)^{y_i}U(x_i)^{1-y_i}
$$
是一个由高斯和均匀分布组成的分布

到这里，基本上基于Beysian 就可以开始进行计算了，但是在实际情况中，这个过程往往是在不断迭代的，而不是像现在的假设一样，一次性都作为输入。

### 找到可以迭代的近似形式
1. 参数后验近似










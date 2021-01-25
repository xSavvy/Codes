<!--
 * @Author: Liu Weilong
 * @Date: 2021-01-25 13:19:02
 * @LastEditors: Liu Weilong 
 * @LastEditTime: 2021-01-25 18:09:11
 * @FilePath: /3rd-test-learning/30. supplement_material/solution_of_linear_equation/doc.md
 * @Description: 
-->
reference:https://zhuanlan.zhihu.com/p/54943042 LU分解<br>

1. LU 分解<br>
   条件：<br>
   a. 方阵 b. 可逆 c.消元过程中没有0主元出现<br>
   作用：<br>
   加速 $Ax=b$计算<br>
   $$
    Ax=b\\
    LUx=b\\
    Ly=b\\
    Ux=y
   $$
   对比求逆的解法<br>
   ![](./picture/1.png)
   变种：<br>
   $PA = LU$ 克服 c  条件 0主元的情况，需要对A进行一次换行 然后重新计算<br>
   
2. Cholesky分解<br>
   条件:<br>
   a. 正定 b. 对称<br>
   作用:<br>
   加速$Ax=b$计算<br>
   $$
   Ax=b\\
   LL^T=b\\
   Ly=b\\
   L^Tx=y
   $$
   时间复杂度:<br>
   ![](./picture/3.png)
   $O(\frac{1}{3}n^3)$


3. QR 分解<br>
   条件：<br>
   
   